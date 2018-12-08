#include "WeightFunctions.h"
#define DTin 17 //Data pin  for weight sensor
#define SCKout 19 //clock pin for weight sensor
double weight = 0;

void setup() {
  Serial.begin(115200);
  initWeight(DTin, SCKout);
  delay(1000);

}

void loop() {

  if (digitalRead(DTin) == 0) {
    
    weight = readWeight(DTin, SCKout);
    Serial.print("The weight is: ");
    Serial.println(weight);
    Serial.println(digitalRead(DTin));
    delay(1000);
  }
}
