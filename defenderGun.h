#pragma once

#include "Arduino.h"

namespace doorDefender{

    class Gun {
    public:
        Gun( const int gunPin, unsigned long shootLength );

        void
            begin(),
            shoot( );

    private:
        const int
            _gunPin;

        unsigned long
            _shootLength;

    };

}
