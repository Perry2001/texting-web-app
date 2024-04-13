#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include "connection.h"



FirebaseData firebaseData;
String prevPhoneNumber = "";
String prevMessage = "";     

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  connectToWiFi();
  connectToFirebase();

  delay(2000);
}

void loop() {
  // Fetch message and number from Firebase
  String phoneNumber;
  String message;

  if (Firebase.getString(firebaseData, "/contact/number")) {
    if (firebaseData.dataType() == "string") {
      phoneNumber = firebaseData.stringData();
    }
  }

  if (Firebase.getString(firebaseData, "/contact/message")) {
    if (firebaseData.dataType() == "string") {
      message = firebaseData.stringData();
    }
  }

  // Check if phone number or message has changed
  if (phoneNumber != prevPhoneNumber || message != prevMessage) {
    // Concatenate phone number and message with a comma
    String dataToSend = phoneNumber + "," + message;
    sendToArduino(dataToSend);

    // Update previous values
    prevPhoneNumber = phoneNumber;
    prevMessage = message;
  }

  delay(5000); // Adjust delay as needed
}

void sendToArduino(String data) {
  Serial.println(data); // Sending data to Arduino
}
