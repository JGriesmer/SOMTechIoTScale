// The following functions are for responding to IOT client pushbuttons.  
// For example: When a light switch is pressed, a lamp flag goes high, and
// makeDisagree can be used to drive the relay trigger pin LOW for an active-low relay.

void makeDisagree(String value, int pin)  //useful for active low relay signals
{
  int myInt = value.toInt();
  if (myInt == 1){
    digitalWrite(pin,LOW);
  }
  else {
    digitalWrite(pin,HIGH);
  }
  
}

void makeAgree(String value, int pin)  //useful for active low relay signals
{
  int myInt = value.toInt();
  if (myInt == 1){
    digitalWrite(pin,HIGH);
  }
  else {
    digitalWrite(pin,LOW);
  }
}

void boolDisagree(bool flag, int pin)
{
    if (flag) digitalWrite(pin, LOW);
    else      digitalWrite(pin, HIGH);
    delay(10);  // delay after relay switch to avoid inductive spike
}

float readBatt(int pin) {
  int x = analogRead(pin); // pins that work on MSP430 Launchpad: 24,25,26,27,28,6,2, DON'T WORK: 23
  float maxVoltage = 3.30; // max scale of analog input
  float voltageDiv = 5.73; // voltage divider circuit
  float battVoltage = ((x)/4096.00*maxVoltage*voltageDiv);
  return(battVoltage);
}

