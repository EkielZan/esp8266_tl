#include "TrafficLight.h"

int redPin = 16;
int yellowPin = 4;
int greenPin = 2;

TrafficLight tl(redPin, yellowPin, greenPin);

void setup() {
  Serial.begin(115200); 
  Serial.println("Hello Everyone");
  Serial.println("This is Traffic Light Control 0.1");
}

void loop() {
  tl.Stop();
  delay(5000); //5 seconds
  tl.Go();
  delay(5000); //7 seconds
  tl.Careful();
  delay(2000); //2 seconds
  Serial.println("TL Made a loop");
}
