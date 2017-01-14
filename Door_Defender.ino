const int gunDelay = 500;
const int trigDelay = 1000;

const int gunPin = 2;
const int trigPin = 7;
const int readPin = 8;
const int ledPin = 13;

const int distBuffer = 5;

int calDistance;

void setup() {
  pinMode(gunPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(gunPin, HIGH);
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(readPin, INPUT);
  delay(5000);
  getDistance();
  delay(trigDelay);
  getDistance();
  delay(trigDelay);
  getDistance();
  delay(trigDelay);
  calDistance = getDistance();
  Serial.print(F("Cal Distance: \t"));
  Serial.println(calDistance);
  delay(trigDelay);

}

void loop() {
  long dist = getDistance();
  Serial.println(dist);
  if(triggered(dist)){
    delay(trigDelay);
    dist = getDistance();
    if(triggered(dist)){
      fire();
    }
  }
  Serial.println();
  delay(trigDelay);
 
}

void fire(){
  Serial.println(F("FIRE!!!!"));
  digitalWrite(gunPin, LOW);
  digitalWrite(ledPin, HIGH);
  delay(gunDelay);
  digitalWrite(gunPin, HIGH);
  digitalWrite(ledPin, LOW);
}
long duration;
int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(readPin, HIGH);
  return(microsecondsToCentimeters(duration));
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


bool triggered(int dist){
  if((distBuffer + dist) < calDistance || (dist) > 3000){
    Serial.println(F("TRIGGERED"));
    return true;
  }
  return false;
}

