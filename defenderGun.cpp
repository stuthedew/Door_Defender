#include "defenderGun.h"

namespace doorDefender {

Gun::Gun( const int gunPin, unsigned long shootLength) : _gunPin( gunPin ){  //Default I2C address
    _shootLength = shootLength;
}

void Gun::begin(){
    pinMode(_gunPin, OUTPUT);
    digitalWrite(_gunPin, LOW);
}

void Gun::shoot( ){

    digitalWrite(_gunPin, HIGH);
    delay(_shootLength);
    digitalWrite(_gunPin, LOW);

}
}
