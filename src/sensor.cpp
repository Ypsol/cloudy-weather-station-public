#include "sensor.h"


Sensor::Sensor(uint8_t sdaPin, uint8_t sclPin)
{
    this->sda = sdaPin;
    this->scl = sclPin;
};

bool Sensor::init(void)
{
    if (!Wire.begin(this->sda, this->scl)){
        return false;
    }
    delay(200);
    Serial.printf("[Sensor] Initialization (sda=%d, scl=%d)\n", this->sda, this->scl);
    // ENS160 Init
    ens160.begin();
    Serial.print("[Sensor] ENS160 : ");
    Serial.println(ens160.available() ? "Success!" : "Failed!");
    if (ens160.available())
    {
        // Print ENS160 versions
        Serial.print("\tRev: ");
        Serial.print(ens160.getMajorRev());
        Serial.print(".");
        Serial.print(ens160.getMinorRev());
        Serial.print(".");
        Serial.println(ens160.getBuild());
        Serial.print("\tStandard mode ");
        Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
    }
    else
        return false;

    delay(200);
    // AHT20 Init
    Serial.print("[Sensor] AHT21 : ");
    if (!aht.begin())
    {
        Serial.println("failed! Check wiring.");
        return false;
    }
    Serial.println("Sucess!");
    return true;
};

sensorData Sensor::getDatas(void)
{
    return this->datas;
};

void Sensor::printDatas(void){
    Serial.println("----- MEASURES -----");
    Serial.printf("\tTempérature: %.2f°C\n", this->datas.temperature);
    Serial.printf("\tHumidité : %.2f %\n", this->datas.humidity);
    Serial.printf("\tTVOC : %.d ppb\n", this->datas.TVOC);
    Serial.printf("\tAQI : %d\n", this->datas.AQI);
    Serial.printf("\teC02 : %d ppm\n", this->datas.eC02);
    Serial.println("--------------------");
}

bool Sensor::runSensor(void)
{
    uint8_t flagCount = 0;
    sensors_event_t hum, temp; 
    if (!aht.getEvent(&hum, &temp)){ 
        Serial.println("[Sensor] Failed to read AHT21 data.");
        flagCount++;
    } 
    this->datas.temperature = temp.temperature;
    this->datas.humidity = hum.relative_humidity;

    if (ens160.available())
    {
        ens160.set_envdata( temp.temperature, temp.relative_humidity);
        ens160.measure(true);
        ens160.measureRaw(true);
        this->datas.AQI = ens160.getAQI();
        this->datas.TVOC = ens160.getTVOC();
        this->datas.eC02 = ens160.geteCO2();
    }
    else{
        Serial.println("[Sensor] Failed to read ENS160 data.");
        flagCount++;
    }
    Serial.println("[Sensor] Measures performed.");

    if (flagCount != 2) return true;
    else{
        return false;
    }
}

void Sensor::deinit(void){
    ens160.setMode(ENS160_OPMODE_DEP_SLEEP);
    Wire.end();
};