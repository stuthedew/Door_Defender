#pragma once

#include "Arduino.h"

namespace doorDefender{

    class Sensor {
        const int _timeoutVal = 25000;
    public:
        Sensor(const int triggerPin, const int echoPin, const int trigOffset);

        void
            begin( void );

        int
            getDistance( void ),
            calibrate();

        bool
            checkTrigger();

    private:
        const int
            _triggerPin,
            _echoPin,
            _trigOffset;

        int
            _calVal;

        long
            _microSecToCM( long microseconds );
    };

}
