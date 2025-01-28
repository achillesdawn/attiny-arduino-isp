#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "rgb.h"


RGB target = RGB();
RGB start = RGB(255, 0, 0);
RGB current = RGB();

#define LED_DATA_PIN 3
#define TOTAL_LEDS 5

long r = 0;

Adafruit_NeoPixel strip(TOTAL_LEDS, LED_DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    pinMode(1, OUTPUT);
    strip.begin();
}

void loop() {

    r = random();

    target.set_from_random(r);
    // target.dim(0.5);

    for (uint8_t step = 0; step < 10; step++) {
        float factor = float(step) / 10.0;

        for (uint8_t i = 0; i < TOTAL_LEDS; i++) {

            current = start.interpolate(target, factor);

            strip.setPixelColor(
                i, strip.Color(current.red, current.green, current.blue)
            );
        }
        strip.show();
        delay(50);
    }

    start = target;
}
