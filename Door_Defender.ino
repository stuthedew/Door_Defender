
#include "defenderLED.h"
#include "defenderSensor.h"
#include "defenderGun.h"

using namespace doorDefender;

Led led(4); //Led pin
Sensor sensor(5, 6, 8); // Trigger and Echo Pin and minimum trigger delta distance (cm).

const int shotLength_ms = 500;
Gun gun(9, shotLength_ms);

const int sampleDelay = 750;
const int coolDownDelay = 5000;


const int ledIntensity = 50;


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
        else{
            led.off();  // First sensor trigger likely error. Reset
        }
    }

    delay(sampleDelay);

}
