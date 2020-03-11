#include <SoftwareSerial.h>
#define RX 10
#define TX 11
SoftwareSerial esp8266(RX,TX);


int PulseSensorPurplePin = 0; // analog pin 0
int LED13 = 13;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  esp8266.begin(115200);
  esp8266.println("AT");
//  esp8266.println("AT+CWMODE=1");
//  esp8266.println("AT+CWJAP=\"amu\",\"amuamuamu\"");
}
void loop() {

  Signal = analogRead(PulseSensorPurplePin);

//   Serial.println(Signal);
//  esp8266.println("AT");

   if(Signal > Threshold){
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);
   }


delay(10);


}
