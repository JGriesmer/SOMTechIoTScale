#define CS 8
#define NRSTDP 5

Mfrc522 Mfrc522(CS, NRSTDP);

void RFIDinit() {
  Serial.println("Starting RFID reading\n");
  SPI.begin();
  digitalWrite(CS, LOW);                    // Initialize the card reader
  //pinMode(RED_LED, OUTPUT);                 // Blink LED if card detected
  Mfrc522.Init();
  //attachInterrupt(3, readRFIDTag, RISING);
  delay(1000);

}

long readRFIDTag() {
  unsigned char serNum[5];
  long returnID;
  unsigned char status;
  unsigned char str[MAX_LEN];

  status = Mfrc522.Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    Serial.print("Card detected: ");
    Serial.print(str[0], BIN);
    Serial.print(" , ");
    Serial.print(str[1], BIN);
    Serial.println("");
  }

  status = Mfrc522.Anticoll(str);
  memcpy(serNum, str, 5);
  if (status == MI_OK)
  {
    digitalWrite(RED_LED, HIGH);              // Card or tag detected!
    Serial.print("The card's number is: ");
    Serial.print(serNum[0]);
    Serial.print(" , ");
    Serial.print(serNum[1]);
    Serial.print(" , ");
    Serial.print(serNum[2]);
    Serial.print(" , ");
    Serial.print(serNum[3]);
    Serial.print(" , ");
    Serial.print(serNum[4]);
    Serial.println("");

    // Additional cards can be recognized by running the program and noting the 5 card specific numbers
    // and then adding an "else if" statement below.
    if (serNum[0] == 91 && serNum[1] == 139 && serNum[2] == 200 && serNum[3] == 115 && serNum[4] == 107)
    {
      Serial.println("Hello Scuttlebot!\n");
      returnID = 1;
    }
    else if (serNum[0] == 198 && serNum[1] == 227 && serNum[2] == 168 && serNum[3] == 26 && serNum[4] == 151)
    {
      Serial.println("Die Puny Human!\n");
      returnID = 2;
    }
    else
    {
      Serial.println("SPECTRE attempting entry!\n");
      returnID = 0;
    }
    delay(1000);
    digitalWrite(RED_LED, LOW);
  }
  else
    returnID = -1;
  Mfrc522.Halt();
  return returnID;
}


