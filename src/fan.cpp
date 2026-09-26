#include "fan.h"

const uint8_t Fan::levels[FAN_SPEED_LEVEL_COUNT] = {
    FAN_SPEED_OFF,
    FAN_SPEED_VERY_LOW,
    FAN_SPEED_LOW,
    FAN_SPEED_MEDIUM,
    FAN_SPEED_HIGH
};

Fan::Fan(uint8_t pin){
    this->pin = pin;
    this->currentLevel = 0;
}

void Fan::init(){
    ledcAttach(pin, 25000, 10);
    digitalWrite(pin, LOW);
    Serial.printf("[FAN] Initialized : Pin=%d\n", pin);
}

void Fan::on(void){
    ledcWrite(pin, FAN_SPEED_VERY_LOW);
    Serial.println("[INFO] Fan on");
}

void Fan::off(void){
    ledcWrite(pin, 0);
    digitalWrite(pin, LOW);
    Serial.println("[INFO] Fan off");
}

void Fan::deinit(void){
    ledcWrite(pin, 0);
    ledcDetach(pin);
    gpio_reset_pin((gpio_num_t)pin);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    Serial.printf("[FAN] Deinitialized : Pin=%d\n", pin);
}

void Fan::setSpeedLevel(uint8_t level){
    if (level >= FAN_SPEED_LEVEL_COUNT) level = FAN_SPEED_LEVEL_COUNT - 1;
    this->currentLevel = level;
    ledcWrite(pin, levels[level]);
    Serial.printf("[FAN] Speed level set to %d (PWM=%d)\n", level, levels[level]);
}

uint8_t Fan::getSpeedLevel(void){
    return this->currentLevel;
}

void Fan::testMode(void){
    while (true){
        ledcWrite(pin, FAN_SPEED_VERY_LOW);
        Serial.println(FAN_SPEED_VERY_LOW);
        delay(3000);
        ledcWrite(pin, FAN_SPEED_LOW);
        Serial.println(FAN_SPEED_LOW);
        delay(3000);
        ledcWrite(pin, FAN_SPEED_MEDIUM);
        Serial.println(FAN_SPEED_MEDIUM);
        delay(3000);
        ledcWrite(pin, FAN_SPEED_HIGH);
        Serial.println(FAN_SPEED_HIGH);
        delay(3000);
    }
}