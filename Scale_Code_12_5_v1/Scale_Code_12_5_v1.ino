#define DTin 17 //Data pin  for weight sensor
#define SCKout 19 //clock pin for weight sensor
long weight = 0;
void setup() {
  Serial.begin(115200);

  initWeight(DTin,SCKout);
  
  delay(1000);

}

void loop() {

  if (digitalRead(DTin) == 0) {
   Serial.println("The weight is: ");
   weight = readWeight(DTin,SCKout);
   Serial.println(weight);
   delay(1000);
  }
}



