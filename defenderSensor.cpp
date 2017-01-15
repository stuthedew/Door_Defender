#include "defenderSensor.h"

namespace doorDefender {

Sensor::Sensor(const int triggerPin, const int echoPin, const int trigOffset) : _triggerPin(triggerPin), _echoPin(echoPin), _trigOffset(trigOffset){

}

void Sensor::begin( void ){
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

int Sensor::getDistance(){
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    unsigned long ToF = pulseIn(_echoPin, HIGH, _timeoutVal);
    if(ToF > 0){
    return(_microSecToCM(ToF));
}
else{
    return -1;
}
}

int Sensor::calibrate(){
    int minVal = 400;
    int maxVal = 0;
    int runningSum = 0;

for(int i = 0; i < 18; i++ ){
    delay(200);
    int val = getDistance();
    if(val == -1){ // sensor Timeout. Restart sample.
        i--;
        continue;
    }
    runningSum += val;
    minVal = min(val, minVal);
    maxVal = max(val, maxVal);

}
    runningSum -= minVal;
    runningSum -= maxVal;
    int averageVal = (runningSum + 8 ) >> 4; //Add 8 (16/2) to round correctly and divide by 16 using bitshift.

    _calVal = averageVal;
    return _calVal;

}

bool Sensor::checkTrigger(){
    delay(100);
    int dist = getDistance();
    if(dist != -1 && dist < (_calVal - _trigOffset)){
        return true;
    }
    else{
        return false;
    }
}

long Sensor::_microSecToCM(long mSec){
    return mSec / 29 >> 1;
}

}
