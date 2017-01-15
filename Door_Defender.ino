
#include "defenderLED.h"
#include "defenderSensor.h"
#include "defenderGun.h"

using namespace doorDefender;

const int ledPin = 4;

//Ping sensor pins
const int triggerPin = 5;
const int echoPin = 5;

const int gunPin = 9;

const int ledIntensity = 30;
Led led(ledPin);

Sensor sensor(triggerPin, echoPin, 8); // Trigger and Echo Pin and minimum trigger delta distance (cm).

const int shotLength_ms = 500;  // Time squirtgun is on in ms
Gun gun(gunPin, shotLength_ms);

const int sampleDelay = 750;
const int coolDownDelay = 5000;

void setup(){
    led.begin();
    sensor.begin();
    gun.begin();

    led.on(BLUE, ledIntensity);
    sensor.calibrate();         // get baseline distance to wall.
    led.on(GREEN, ledIntensity);

    delay(1000);

    led.off();
}

void loop(){    //  Poll sensor. Fire Squirt gun if triggerd two times in a row.

    if(sensor.checkTrigger()){          // see if distance has dropped (e.g. a cat is in front of the sensor)
        led.on(YELLOW, ledIntensity);   // Warn that sensor was triggered

        delay(sampleDelay);

        if(sensor.checkTrigger()){      // Trigged second time in a row. FIRE!
            led.on(RED, ledIntensity);
            gun.shoot();

            led.off();

            delay(coolDownDelay);

            led.on(BLUE, ledIntensity);
            sensor.calibrate(); // Recalibrate in case sensor was moved.
            led.on(GREEN, ledIntensity);

            delay(sampleDelay);

        }
            led.off();
    }

    delay(sampleDelay);
}
