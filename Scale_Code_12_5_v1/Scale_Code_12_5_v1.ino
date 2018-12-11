//library includes
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "Mfrc522.h"
#include <SPI.h>
//input and output pins
#define DTin 17 //Data pin  for weight sensor
#define SCKout 19 //clock pin for weight sensor

//channel setup
#define weightChannel 0
#define IDChannel 1

//cayenne settings
char ssid[] =       "*****"; //   put your wifi network id here
char password[] =   "*****"; // put your wifi password here
char server[] =     "mqtt.mydevices.com"; // keep this for Cayenne
char MQTTuser[] =   "*****"; // copy and paste from your Cayenne device info
char MQTTpass[] =   "*****"; // copy and paste from your Cayenne device info
char MQTTclient[] = "*****"; // copy and paste from your Cayenne device info

//important variables
float weight = 0;

//interrupt flags
bool RFID = false;
//things that need to happen
void callback(char* topic, byte* payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  //initialize connection to cayenne
  initialWiFiConnection();
  reconnectMQTT();
  subscribeAll();
  delay(100);
  //initialize the pins for reading the weight
  initWeight(DTin, SCKout); 
  delay(1000);
  tareScale(DTin,SCKout);
  RFIDinit();

}

void loop() {
  if ( WiFi.status() != WL_CONNECTED) {
    connectToWiFi();                //use this fcn for 2nd and subsequent connections
  }

  if (!client.connected()) {
    reconnectMQTT();                // Reconnect MQTT if disconnected
    subscribeAll();
  }

  if (digitalRead(DTin) == 0) {
    readRFIDTag();
    
    weight = readWeight(DTin, SCKout);
    
    Serial.print("The weight is: ");
    Serial.println(weight);
    //Serial.println(digitalRead(DTin));
    delay(100);

    publishWeight(weight,weightChannel);
    delay(1000);
  }
  
}

void subscribeAll()
{
  channelSubscribe(weightChannel);
  
}
void callback(char* topic, byte* payload, unsigned int length) {

}
