#include <SoftwareSerial.h>


/////////////////////////
/***** FOR ESP8266 *****/
#define RX 10 
#define TX 11
SoftwareSerial esp(RX,TX);
int ssid = "amu";
int passwd = "amuamuamu";
String data;
String server = "yourServer";
String uri = "yourURI";
/***********************/
/////////////////////////

///////////////////////////////////
///////////////////////////////////
/***** FOR HEART BEAT SENSOR *****/
int PulseSensorPurplePin = 0; // analog pin 0
int LED13 = 13;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.
/*********************************/
///////////////////////////////////
///////////////////////////////////
void setup() {
  pinMode(LED13,OUTPUT);  // Blink the heart beat
  Serial.begin(9600); // Normal serial connection baud rate
  esp.begin(9600);  // Serial connection for ESP8266 baud rate

  resetESP();
  connectWifi();
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void loop() {

  int signal = readHeartBeats();
  
 //Serial.println(Signal);
  HandleLEDs(signal);


  delay(10);

}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void resetESP() {
  esp.println("AT+RST");
  delay(1000);
  if(esp.find("OK"))
    Serial.println("Module Reset");
    
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void connectWifi() {
  String setup_cmd = "AT+CWMODE=3"; 
  esp.println(setup_cmd);
  delay(1000);
  
  String connect_cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";
  esp.println(connect_cmd);
  delay(4000);
  if(esp.find("OK")) {
    Serial.println("Connected!");
  }
  else {
    connectWifi();
    Serial.println("Cannot connect to wifi");
  }  
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int readHeartBeats() {  
  return analogRead(PulseSensorPurplePin);
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void handleLEDs(int signal) {
  if(Signal > Threshold){
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);
   }
}
///////////////////////////////////////////////////////////////////////////
