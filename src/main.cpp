#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

uint8_t lerp(uint8_t start, uint8_t end, float t) {
    return start + (end - start) * t;
}

class RGB {
  public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) {
        this->red = r;
        this->green = g;
        this->blue = b;
    }

    void set_from_random(long r) {
        this->red = (uint8_t)r;
        this->green = (uint8_t)(r >> 8);
        this->blue = (uint8_t)(r >> 16);
    }

    void dim(float factor) {
        this->red = uint8_t((float)red * factor);
        this->green = uint8_t((float)green * factor);
        this->blue = uint8_t((float)blue * factor);
    }

    RGB interpolate(RGB target, float factor) {
        uint8_t r = lerp(red, target.red, factor);
        uint8_t g = lerp(green, target.green, factor);
        uint8_t b = lerp(blue, target.blue, factor);

        return RGB(r, g, b);
    }
};

RGB target = RGB();
RGB start = RGB(255, 0, 0);
RGB current = RGB();

const uint8_t TOTAL_LEDS = 10;
long r = 0;

Adafruit_NeoPixel strip(TOTAL_LEDS, 3, NEO_GRB + NEO_KHZ800);

void setup() {
    pinMode(1, OUTPUT);
    strip.begin();
}

void loop() {

    r = random();

    target.set_from_random(r);
    target.dim(0.5);

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
