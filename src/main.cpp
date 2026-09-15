#include <Arduino.h>
#include <ArduinoOTA.h>
#include "connectivity.h"
#include "sensor.h"
#include "led.h"
#include "fan.h"

#define TIMEOUT 10
#define MEASURES_DELAY 60

sensorData datas;
Fan fan(FAN_PIN);
Sensor sensor(SDA_PIN, SCL_PIN);
Led led;
Connectivity connectivity;

void setup()
{
  Serial.begin(115200);
  Serial.println("---- Cloudy Weather Station ----");
  Serial.println("\tRev : V1.0");
  Serial.println("\tBy Ypsol");

  led.init();
  fan.init();
  fan.off();

  if (!sensor.init())
  {
    Serial.println("[ERROR] Sensor failed to initialize, restarting...");
    led.error(3);
    delay(3000);
    ESP.restart();
  }

  connectivity.setFan(&fan);

  if (!connectivity.connect())
  {
    led.error(1);
    Serial.println("[ERROR] WiFi failed, passing...");
  }
  else{
    connectivity.startServer();
  }

  ArduinoOTA.setHostname("cloudy-station");
  ArduinoOTA.setPassword("mycloudyisbetter");
  ArduinoOTA.begin();

  led.on();
  fan.on();

  Serial.println("[INFO] Station successfully started!");
  Serial.println(ESP.getFlashChipSize());
}

void loop()
{
  EVERY_N_BSECONDS(MEASURES_DELAY)
  {
    if (!sensor.runSensor())
    {
      uint8_t count = 0;
      while (!sensor.runSensor() && count < TIMEOUT)
      {
        Serial.println("[ERROR] Measures can't be performed, retrying...");
        count++;
        delay(1000);
      }
      if (count >= TIMEOUT)
      {
        Serial.println("[ERROR] Timeout exceeded");
        led.error(4);
      }
    }
    else
    {
      sensorData datas = sensor.getDatas(); // Fill the sensorData structure with fresh data
      if (connectivity.thingspeak_activated) connectivity.sendData(datas);
      led.changeLevel(datas.AQI); // Change the led color according to AQI level
      sensor.printDatas();        // Optional, to debug
    }
  }


  EVERY_N_MILLISECONDS(15)
  {
    led.handleLeds();
    ArduinoOTA.handle();
  }

  vTaskDelay(pdMS_TO_TICKS(5));
}