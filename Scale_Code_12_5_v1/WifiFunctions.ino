// The functions of initial wifi connection and subsequent connections have been separated
// to solve an issue with failing to reconnect.  This was applied for MSP430 / CC3100 boosterpack
// pair, and also works with CC3200 launchpad.

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void initialWiFiConnection() {
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid);
  // Connect to WPA/WPA2 network.
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  printWifiStatus();
}



void connectToWiFi() {
  sl_Start(0, 0, 0);

  delay(100);
  sl_WlanPolicySet(SL_POLICY_CONNECTION , SL_CONNECTION_POLICY(1, 1, 0, 0, 0), 0, 0);

  int NameLen = strlen(ssid);
  SlSecParams_t SecParams = {0};
  SecParams.Type = SL_SEC_TYPE_WPA;
  SecParams.Key = (signed char *)password;
  SecParams.KeyLen = strlen(password);

  int iRet = sl_WlanConnect((signed char *)ssid, NameLen, NULL, &SecParams, NULL);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid);
  // Connect to WPA/WPA2 network.
  //  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  // We are connected and have an IP address.
  // Print the WiFi status.
  printWifiStatus();
}

void disconnectFromWiFi() {
  Serial.print("Disconnecting from WiFi....");
  sl_WlanPolicySet(SL_POLICY_CONNECTION , SL_CONNECTION_POLICY(0, 0, 0, 0, 0), 0, 0);
  delay(500);
  sl_WlanDisconnect();

  while (WiFi.status() == WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  sl_Stop(0);

  Serial.println("Disconnected");
}
