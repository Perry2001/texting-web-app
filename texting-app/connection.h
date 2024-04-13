#ifndef FIREBASE_CONNECTION_H
#define FIREBASE_CONNECTION_H

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiManager.h> // Include the WiFiManager library



#define FIREBASE_HOST "https://texting-webapp-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "X93QVrFjsUHglzGFkyCAu7eS0FpLwABkpTi1SThT"




// Forward declaration
void saveConfigCallback();

void connectToWiFi() {
  // Create an instance of WiFiManager
  WiFiManager wifiManager;
  
  
  // Set callback functions to handle saving custom parameters
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // Try to connect to previously saved WiFi credentials
  if (!wifiManager.autoConnect("esp wifi setup")) {
    // Reset and try again
    ESP.reset();
    delay(5000);
  }


  wifiManager.setDebugOutput(false);
}


void connectToFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  
}

void saveConfigCallback() {
  // Called when WiFiManager enters configuration mode to save custom parameters
  Serial.println("Configuring WiFi...");
  // You can add custom logic here to save the WiFi credentials to EEPROM or any other storage
}




#endif