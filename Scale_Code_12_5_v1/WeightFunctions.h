double tare = 1.45
//function to be run in setup to initialze the weight reading of the scale
void initWeight(int dataIn, int clk) {

  pinMode(dataIn, INPUT_PULLUP);
  //Serial.println(digitalRead(dataIn)); //for debugging data pin
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);
  Serial.println(digitalRead(clk));
  Serial.println(digitalRead(dataIn));//for debugging clk pin

}

//function to read the weight, had to bit bang, shiftIn did not function properly and would drop bits of the end
//modifies the value that is input at value
double readWeight(int dataIn, int clk) {
  double kg;
  long value;
  uint8_t filler = B11111111;
  //decrementing loop becuase the device shifts in the most signifigant bit first
  //shift in bits
  for (int i = 23; i >= 0; i--) {
    digitalWrite(clk, HIGH);
    delayMicroseconds(30);
    Serial.print(digitalRead(dataIn));
    value |= (digitalRead(dataIn)) << i;
    //Serial.print(data[i]);//debug
    digitalWrite(clk, LOW);
    delayMicroseconds(30);

  }

  //sets gain to 128 so we can use the A channel on the device
  Serial.println("");//debug
  digitalWrite(clk, HIGH);
  delayMicroseconds(30);
  digitalWrite(clk, LOW);
  //makes sure dt went back to 0
  delay(1000); //debugging
  Serial.print("DT: ");
  Serial.println(digitalRead(dataIn));
  if (value && 0x800000) {
    value |= filler << 24;
  }

  Serial.print("The read value is: ");
  Serial.println(value);//debugging value before conversion

  //conversion code
  kg = ((value * (-.00005)) - (13.497)- (tare));
  return kg;
}
