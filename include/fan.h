#ifndef FAN_H
#define FAN_H

#include <Arduino.h>

#define FAN_PIN 10
#define FAN_SPEED_OFF 0
#define FAN_SPEED_VERY_LOW 10
#define FAN_SPEED_LOW 15
#define FAN_SPEED_MEDIUM 100
#define FAN_SPEED_HIGH 255
#define FAN_SPEED_LEVEL_COUNT 5

class Fan {
private:
    uint8_t pin;
    uint8_t currentLevel;
    static const uint8_t levels[FAN_SPEED_LEVEL_COUNT];

public:    
    Fan(uint8_t pin = FAN_PIN);
    void init(void);
    void on();
    void off();
    void deinit();
    void testMode();
    void setSpeedLevel(uint8_t level);
    uint8_t getSpeedLevel(void);
};

#endif // FAN_H