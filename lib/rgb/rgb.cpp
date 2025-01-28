
#include "rgb.h"
#include <inttypes.h>

uint8_t lerp(uint8_t start, uint8_t end, float t) {
    return start + (end - start) * t;
}

void RGB::set_from_random(long r) {
    this->red = (uint8_t)r;
    this->green = (uint8_t)(r >> 8);
    this->blue = (uint8_t)(r >> 16);
}

void RGB::dim(float factor) {
    this->red = uint8_t((float)red * factor);
    this->green = uint8_t((float)green * factor);
    this->blue = uint8_t((float)blue * factor);
}

RGB RGB::interpolate(RGB target, float factor) {
    uint8_t r = lerp(red, target.red, factor);
    uint8_t g = lerp(green, target.green, factor);
    uint8_t b = lerp(blue, target.blue, factor);

    return RGB(r, g, b);
}