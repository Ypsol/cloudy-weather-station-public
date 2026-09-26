#include "led.h"

DEFINE_GRADIENT_PALETTE(bluePalette_gp){
    0, 20, 150, 255,
    255, 0, 0, 255};
CRGBPalette16 bluePalette = bluePalette_gp;

DEFINE_GRADIENT_PALETTE(greenPalette_gp){
    0, 20, 255, 150,
    255, 0, 255, 0};
CRGBPalette16 greenPalette = greenPalette_gp;

DEFINE_GRADIENT_PALETTE(yellowPalette_gp){
    0, 255, 255, 20,
    255, 255, 255, 0};
CRGBPalette16 yellowPalette = yellowPalette_gp;

DEFINE_GRADIENT_PALETTE(orangePalette_gp){
    0, 255, 150, 20,
    255, 255, 80, 0};
CRGBPalette16 orangePalette = orangePalette_gp;

DEFINE_GRADIENT_PALETTE(redPalette_gp){
    0, 255, 20, 20,
    255, 255, 0, 0};
CRGBPalette16 redPalette = redPalette_gp;

DEFINE_GRADIENT_PALETTE(whitePalette_gp){
    0, 30, 30, 30,
    255, 255, 255, 255};
CRGBPalette16 whitePalette = whitePalette_gp;

Led::Led()
{
    this->level = 0;
    this->brightness = 0;
    this->paletteIndex = 0;
}

void Led::init(void)
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(this->leds, NUM_LEDS);
    FastLED.setBrightness(LEDS_BRIGHTNESS);
    FastLED.setDither(0);
    Serial.println("[LED] Led initialized.");

    for (int i = 0; i < NUM_LEDS; i++)
    {
        FastLED.clear();
        leds[i] = CRGB::White;
        FastLED.show();
        delay(100);
    }
    FastLED.clear();
}

CRGBPalette16 Led::convertLevelToPalette(uint8_t level)
{
    switch (level)
    {
    case 1:
        return bluePalette;
    case 2:
        return greenPalette;
    case 3:
        return yellowPalette;
    case 4:
        return orangePalette;
    case 5:
        return redPalette;
    default:
        return whitePalette;
    }
}

void Led::on(void)
{
    fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, convertLevelToPalette(this->level), brightness, LINEARBLEND);

    for (uint8_t i = this->brightness; i < LEDS_BRIGHTNESS; i++)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(LED_FADE_DELAY);
    }
    this->brightness = LEDS_BRIGHTNESS;
}

void Led::off(void)
{
    for (uint8_t i = this->brightness; i > 0; i--)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(LED_FADE_DELAY);
    }
    this->brightness = 0;
}

void Led::sleep()
{
    for (uint8_t i = LEDS_BRIGHTNESS; i > LED_SLEEP_BRIGHTNESS; i--)
    {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(LED_FADE_DELAY);
    }
    this->brightness = LED_SLEEP_BRIGHTNESS;
}

void Led::fadeToPalette(CRGBPalette16 new_palette)
{
    CRGB old_strip[NUM_LEDS];
    for (int i = 0; i < NUM_LEDS; i++)
    {
        old_strip[i] = leds[i];
    }

    CRGB new_strip[NUM_LEDS];
    fill_palette(new_strip, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, new_palette, brightness, BLEND);

    for (int i = 0; i < 255; i++)
    {
        for (int led = 0; led < NUM_LEDS; led++)
        {
            leds[led] = blend(old_strip[led], new_strip[led], i);
        }
        delay(2);
        FastLED.show();
    }
}

void Led::changeLevel(uint8_t newLevel)
{
    if (newLevel == this->level)
    {
        return;
    }
    Serial.printf("[INFO] Changing level (%d->%d)\n", this->level, newLevel);

    CRGBPalette16 new_palette = convertLevelToPalette(newLevel);
    fadeToPalette(new_palette);
    this->level = newLevel;
}

void Led::error(uint8_t code)
{
    switch (code)
    {
    case 1: // WiFi Connection Error
        for (int cycle = 0; cycle < 2; cycle++)
        {
            // Fade in
            for (int b = 0; b < 255; b += 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::Magenta);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
            // Fade out
            for (int b = 255; b >= 0; b -= 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::Magenta);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
        }
        FastLED.setBrightness(this->brightness); // restore
        break;

    case 2: // Sensor Initialization Error
        for (int cycle = 0; cycle < 2; cycle++)
        {
            // Fade in
            for (int b = 0; b < 255; b += 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::Red);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
            // Fade out
            for (int b = 255; b >= 0; b -= 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::Red);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
        }
        FastLED.setBrightness(this->brightness); // restore
        break;

    case 3: // Sensor data refresh Error
    default:
        for (int cycle = 0; cycle < 2; cycle++)
        {
            // Fade in
            for (int b = 0; b < 255; b += 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::OrangeRed);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
            // Fade out
            for (int b = 255; b >= 0; b -= 5)
            {
                fill_solid(leds, NUM_LEDS, CRGB::OrangeRed);
                FastLED.setBrightness(b);
                FastLED.show();
                delay(5);
            }
        }
        FastLED.setBrightness(this->brightness);
        break;
    }
    CRGBPalette16 new_palette = convertLevelToPalette(this->level);
    fadeToPalette(new_palette);
}

void Led::handleLeds(void)
{
    this->paletteIndex = (paletteIndex + 1) % 255;

    CRGBPalette16 palette = convertLevelToPalette(this->level);
    fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, palette, brightness, BLEND);
    FastLED.show();
}

void Led::testMode()
{
    int newLevel = (this->level + 1) % 6;
    changeLevel(newLevel);
}
