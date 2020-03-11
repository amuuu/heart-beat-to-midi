#include "ESP8266WiFi.h"
 
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPass";
 
WiFiServer wifiServer(80);
//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {
  // For the heart beat sensor
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.

  // For the wifi module
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
  wifiServer.begin();

}

// The Main Loop Function
void loop() {
  WiFiClient client = wifiServer.available();
  if (client) {
 
    while (client.connected()) {
      while (client.available()>0) {   
        // Read the hear beat signal
        Signal = analogRead(PulseSensorPurplePin);
        Serial.println(Signal);
        if(Signal > Threshold)
          digitalWrite(LED13,HIGH);
        } else {
          digitalWrite(LED13,LOW);
        }
        delay(10);

        client.write(Signal);
//        Serial.write(c);
      }      
    }
    client.stop();
    Serial.println("Client disconnected");

delay(10);


}
