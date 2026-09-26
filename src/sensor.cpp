#include "sensor.h"

Sensor::Sensor(uint8_t sdaPin, uint8_t sclPin)
{
    this->sda = sdaPin;
    this->scl = sclPin;
    this->data = {0};
}

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
    {
        return false;
    }

    delay(200);
    // AHT21 Init
    Serial.print("[Sensor] AHT21 : ");
    if (!aht.begin())
    {
        Serial.println("failed! Check wiring.");
        return false;
    }
    Serial.println("Success!");
    return true;
}

sensorData Sensor::getData(void)
{
    return this->data;
}

void Sensor::printData(void)
{
    Serial.println("----- MEASURES -----");
    Serial.printf("\tTempérature : %.2f°C\n", this->data.temperature);
    Serial.printf("\tHumidité    : %.2f %%\n", this->data.humidity);
    Serial.printf("\tTVOC        : %u ppb\n", this->data.TVOC);
    Serial.printf("\tAQI         : %u\n", this->data.AQI);
    Serial.printf("\teCO2        : %u ppm\n", this->data.eCO2);
    Serial.println("--------------------");
}

bool Sensor::runSensor(void)
{
    uint8_t flagCount = 0;
    sensors_event_t hum = {}, temp = {}; 
    if (!aht.getEvent(&hum, &temp))
    { 
        Serial.println("[Sensor] Failed to read AHT21 data.");
        flagCount++;
    } 
    else 
    {
        this->data.temperature = temp.temperature;
        this->data.humidity = hum.relative_humidity;
    }

    if (ens160.available())
    {
        if (flagCount == 0)
        {
            ens160.set_envdata(temp.temperature, temp.relative_humidity);
        }
        ens160.measure(true);
        ens160.measureRaw(true);
        this->data.AQI = ens160.getAQI();
        this->data.TVOC = ens160.getTVOC();
        this->data.eCO2 = ens160.geteCO2();
    }
    else
    {
        Serial.println("[Sensor] Failed to read ENS160 data.");
        flagCount++;
    }
    Serial.println("[Sensor] Measures performed.");

    return (flagCount < 2);
}

void Sensor::deinit(void)
{
    ens160.setMode(ENS160_OPMODE_DEP_SLEEP);
    Wire.end();
}