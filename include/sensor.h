#ifndef SENSOR_H
#define SENSOR_H
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include "ScioSense_ENS160.h"

#define SDA_PIN 3
#define SCL_PIN 4

typedef struct _sensorData{
    float temperature;
    float humidity;
    uint8_t AQI;
    uint16_t TVOC;
    uint16_t eC02;
}sensorData;

class Sensor{
private:
    Adafruit_AHTX0 aht;
    uint8_t sda;
    uint8_t scl;
    ScioSense_ENS160 ens160{ENS160_I2CADDR_1};

    sensorData datas;

public:
    Sensor(uint8_t sdaPin, uint8_t sclPin);
    bool init();
    void deinit();
    sensorData getDatas();
    bool runSensor();
    void printDatas();
};

#endif