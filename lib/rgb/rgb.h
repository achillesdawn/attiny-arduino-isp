#include "inttypes.h"




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

    void set_from_random(long r);

    void dim(float factor) ;

    RGB interpolate(RGB target, float factor) ;
};