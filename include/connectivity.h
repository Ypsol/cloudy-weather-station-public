#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H
#include "esp_wifi.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include "creditentials.h" //WIFI_PASSWORD AND WIFI_SSID
#include "sensor.h"
#include "fan.h"
#define WIFI_TIMEOUT 15

#define EMERGENCY_SSID "Cloudy"
#define EMERGENCY_PASSWORD "CloudyTheBest"

class Connectivity{
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
    bool emergency_mode;

    Connectivity(void);
    bool connect(void);
    bool reconnect(void);
    void disconnect(void);
    bool startServer(void);
    bool sendData(sensorData data);
    void testMode(void);
    void deinit(void);
    void setFan(Fan* fan); // Link the Fan instance so the web server can read/set its speed
};

#endif