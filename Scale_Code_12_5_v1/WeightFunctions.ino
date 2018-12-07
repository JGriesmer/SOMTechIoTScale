//function to be run in setup to initialze the weight reading of the scale
void initWeight(int dataIn, int clk) {

  pinMode(dataIn, INPUT_PULLUP);
  //Serial.println(digitalRead(dataIn)); //for debugging data pin
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);
  //Serial.println(digitalRead(clk)); //for debugging clk pin

}

//function to read the weight, had to bit bang, shiftIn did not function properly and would drop bits of the end
long readWeight(int dataIn, int clk) {
  long value = 0 ;
  uint8_t filler = 0 ;
  bool data[24] = {0};
  //decrementing loop becuase the device shifts in the most signifigant bit first
  for (int i = 23; i >= 0; i--) {
    digitalWrite(clk, HIGH);
    delayMicroseconds(3);
    data[i] = (digitalRead(dataIn));
    Serial.print(data[i]);//debug
    digitalWrite(clk, LOW);
    delayMicroseconds(3);

  }
  Serial.println("");//debug
  digitalWrite(clk, HIGH);
  delayMicroseconds(3);
  digitalWrite(clk, LOW);
  Serial.println(value);

  Serial.print("DT: ");
  Serial.println(digitalRead(dataIn));

  value = ((data[23] << 23) | (data[22] << 22) | (data[21] << 21) | (data[20] << 20) | (data[19] << 19) | (data[18] << 18) | (data[17] << 17) | (data[16] << 16)
           | (data[15] << 15) | (data[14] << 14) | (data[13] << 13) | (data[12] << 12) | (data[11] << 11) | (data[10] << 10) | (data[9] << 9) | (data[8] << 8)
           | (data[7] << 7) | (data[6] << 6) | (data[5] << 5) | (data[4] << 4) |  (data[3] << 3)  | (data[2] << 2) | (data[1] << 1) | (data[0] << 0));
  /*
    //debugging stuff for value conversion
    Serial.print("The weight is: ");
    Serial.println(value);
    delay(1000);
  */
  return value;
}
