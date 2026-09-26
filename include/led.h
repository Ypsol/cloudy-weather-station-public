#ifndef LED_H
#define LED_H

#include "FastLED.h"

#define LED_PIN 1
#define NUM_LEDS 11
#define LED_FADE_DELAY 10
#define LED_SLEEP_BRIGHTNESS 0 
#define LEDS_BRIGHTNESS 100

class Led {
private:
    CRGB leds[NUM_LEDS];
    uint8_t paletteIndex;
    CRGBPalette16 convertLevelToPalette(uint8_t level);

public:
    uint8_t level;
    uint8_t brightness;

    Led(void);
    void handleLeds(void);
    void init(void);
    void on();
    void off();
    void sleep();
    void fadeToPalette(CRGBPalette16 new_palette);
    void fadetoPalette(CRGBPalette16 new_palette) { fadeToPalette(new_palette); }
    void changeLevel(uint8_t lastLevel);
    void testMode();
    void error(uint8_t code);
};

#endif // LED_H