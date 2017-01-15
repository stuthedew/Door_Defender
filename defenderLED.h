#pragma once

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

namespace doorDefender{
const int numPixels = 1; // Number of pixels (only using one)

typedef enum {
    RED=0,
    GREEN,
    BLUE,
    YELLOW
}pixel_color_e;

const uint8_t colors[][3] = {   {250, 0, 0},    //Red
                                {0, 250, 0},    //Green
                                {0, 0, 250},    //Blue
                                {255, 90, 0}   //Yellow
};


    class Led {
    public:
        Led(const int lPin);

        void
            begin( ),
            on(pixel_color_e c, uint8_t brightness),
            on(pixel_color_e c),
            off(),
            blink(pixel_color_e c, unsigned long blinkDelay),
            blink(pixel_color_e c, uint8_t brightness, unsigned long blinkDelay);

    private:
        const int _ledPin;

        Adafruit_NeoPixel
            _pixel;
    };

}
