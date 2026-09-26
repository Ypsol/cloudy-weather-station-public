#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <Arduino.h>
#include "esp_wifi.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include "credentials.h"
#include "sensor.h"
#include "fan.h"

#define WIFI_TIMEOUT 15

class Connectivity {
private:
    AsyncWebServer server;
    const char* ssid;
    const char* password;
    const char* thingspeak;
    HTTPClient http;
    sensorData dataCopy;
    Fan* fan;

public:
    bool thingspeak_activated;

    Connectivity(void);
    bool connect(void);
    bool reconnect(void);
    void disconnect(void);
    bool startServer(void);
    void updateData(sensorData data);
    bool sendData(sensorData data);
    void deinit(void);
    void setFan(Fan* fan);
};

#endif // CONNECTIVITY_H