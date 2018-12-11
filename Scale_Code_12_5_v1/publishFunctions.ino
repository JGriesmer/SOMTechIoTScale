// These are customized functions that send payloads to Cayenne using
// the proper numerical format with the proper units to agree with the Cayenne API.

void publishBool(int boo, int channel)  //publish a boolean value
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("digital_sensor="+String(boo));
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void publishRSSI(float value, int channel) //publish an RSSI float value
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myRssi = String("rssi,dbm="+String(value));
  char cRssi[myRssi.length()+1];
  myRssi.toCharArray(cRssi,myRssi.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,cRssi);    
}

void publishProx(float distance, int channel) //publish a proximity value in centimeters
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myProx = String("prox,cm="+String(distance));
  char cProx[myProx.length()+1];
  myProx.toCharArray(cProx,myProx.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,cProx);
}


void publishTemp(float value, int channel)   //publish degrees Celsius
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myTempString = String("temp,c="+getValString(value));  //DPM UPDATE 12.05
  char myTempChar[myTempString.length()+1];
  myTempString.toCharArray(myTempChar,myTempString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myTempChar);
}

void publishFloat(float value, int channel)  //publish a float value
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = getValString(value);
  Serial.println(valueString);  //debugging effort
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void publishWeight(float value, int channel)  //publish a float value
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("weight,kg="+String(value));
  Serial.println(valueString);  //debugging effort
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void publishHum(float value, int channel)
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myHumString = String("rel_hum,p="+getValString(value));
  char myHumChar[myHumString.length()+1];
  myHumString.toCharArray(myHumChar,myHumString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myHumChar);
}

void publishLux(float value, int channel)
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myHumString = String("lum,lux="+getValString(value));
  char myHumChar[myHumString.length()+1];
  myHumString.toCharArray(myHumChar,myHumString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myHumChar);
}

void publishSoil_pH(float value, int channel)
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String mySoil_pHString = String("rel_hum,p="+getValString(value));
  char mySoil_pHChar[mySoil_pHString.length()+1];
  mySoil_pHString.toCharArray(mySoil_pHChar,mySoil_pHString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,mySoil_pHChar);
}

void publishCount(int value, int channel)  //publishes an integer value
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myCount = String("counter,Analog="+String(value));
  Serial.println(myCount);
  char myCountChar[myCount.length()+1];
  myCount.toCharArray(myCountChar,myCount.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myCountChar);
}

void publishVoltage(float value, int channel)
{
  String user = String(MQTTuser);
  String clientID = String(MQTTclient);
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("voltage,v="+String(value));
  Serial.println(valueString);
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}
