#include "defenderLED.h"

namespace doorDefender {

Led::Led(const int lPin) : _ledPin(lPin), _pixel(numPixels, _ledPin, NEO_GRB + NEO_KHZ800){
	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
    	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
    #endif
    	// End of trinket special code
}

void Led::begin( ){
    _pixel.begin(); // This initializes the NeoPixel library.
    off();
}

void Led::on(pixel_color_e c, uint8_t brightness){
    _pixel.setBrightness(brightness);
    _pixel.setPixelColor(0, _pixel.Color(colors[c][0], colors[c][1], colors[c][2]));
    _pixel.show();
}

void Led::on(pixel_color_e c){
    on(c, 255);
}

void Led::off(){
    _pixel.setBrightness(0);
    _pixel.show();
}

void Led::blink(pixel_color_e c, uint8_t brightness, unsigned long blinkDelay){
    on(c, brightness);
    delay(blinkDelay);
    off();
    delay(blinkDelay);
}

void Led::blink(pixel_color_e c, unsigned long blinkDelay){
    blink(c, 255, blinkDelay);
}

}
