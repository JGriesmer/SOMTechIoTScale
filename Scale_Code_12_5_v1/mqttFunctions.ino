// These functions are for dealing with main MQTT functionality

void reconnectMQTT(void)
{
  String user =     String(MQTTuser); 
  String clientID = String(MQTTclient);
  Serial.println("Disconnected. Reconnecting....");
  char clientIDx[clientID.length()+1];
  char userx[user.length()+1];
  clientID.toCharArray(clientIDx,clientID.length()+1);
  user.toCharArray(userx,user.length()+1);
    if(!client.connect(clientIDx, userx, MQTTpass)) {
      Serial.println("Connection failed");
    } else {
      Serial.println("Connection success");
    }
}

void channelSubscribe(int channel)  //subscribe to a channel
{
  String user =     String(MQTTuser); 
  String clientID = String(MQTTclient); 
  String topic =  String("v1/" + user + "/things/" + clientID + "/cmd/" + channel);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);  
  if(client.subscribe(topicChar)) {
        Serial.print("Subscription successful for ch");
        Serial.println(channel);
  }
}

int getChannel(String myTopicString)  //parse the channel from the cmd topic
{
  int ind1 = myTopicString.indexOf('/');            //find location of first delimiter
  int ind2 = myTopicString.indexOf('/', ind1+1 );   //find location of second delimiter
  int ind3 = myTopicString.indexOf('/', ind2+1 );   //find location of third delimiter
  int ind4 = myTopicString.indexOf('/', ind3+1 );   //find location of fourth delimiter
  int ind5 = myTopicString.indexOf('/', ind4+1 );   //find location of fifth delimiter
  String myChan = myTopicString.substring(ind5+1,100);   //captures second data String
  Serial.println(myChan); 
  int chan = myChan.toInt();
  return(chan);
}  

float getValue(String payloadString, int length)  //parse the value from the cmd topic
{
  int ind1 = payloadString.indexOf(',');            //find location of first delimiter
  String cmdValue = payloadString.substring(ind1+1,length);   //captures second data String
  Serial.println(cmdValue); 
  float cmdValueF = cmdValue.toFloat();
  return(cmdValueF);
}  

String getValString(double floatVal) {
  char charVal[10];               //temporarily holds data from vals 
  String stringVal = "";             //data on buff is copied to this string
  dtostrf(floatVal, 6, 2, charVal);  //4 is mininum width, 4 is precision; float value is copied onto buff
  for(int i=0;i<sizeof(charVal);i++)
    {
       stringVal+=charVal[i];
    }
  return(stringVal);
}

