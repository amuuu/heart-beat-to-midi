/////////////////////////////
#include <SoftwareSerial.h>
/////////////////////////////

/////////////////////////
/***** FOR ESP8266 *****/
#define RX 10 
#define TX 11
SoftwareSerial esp(RX,TX);
String ssid = "amu";
String passwd = "amuamuamu";
String data;
String server = "yourServer";
String uri = "yourURI";
/***********************/
/////////////////////////

///////////////////////////////////
///////////////////////////////////
/***** FOR HEART BEAT SENSOR *****/
int pulseSensorPurplePin = 0; // analog pin 0
int LED13 = 13;
int signal; // holds the incoming raw data. Signal value can range from 0-1024
int threshold = 550;  // Determine which Signal to "count as a beat", and which to ingore.
/*********************************/
///////////////////////////////////

///////////////////////////////
/***** GENERAL VARIABLES *****/
int timerCounter = 0;
/*****************************/
///////////////////////////////

///////////////////////////////////
void setup() {
  pinMode(LED13,OUTPUT);  // Blink the heart beat
  esp.begin(115200);  // Serial connection for ESP8266 baud rate
  Serial.begin(9600); // Normal serial connection baud rate

  resetESP();
  connectWifi();
  esp.println("Waiting 5 seconds to start");
  delay(5000);
  esp.println("Alright, let's go");
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void loop() {

  signal = readHeartBeats();
  Serial.println(signal);
  handleLEDs(signal);

  timerCounter++;
  if (timerCounter % 50) { // Every 500 milliseconds send the new data to server
    //httpPost(signal);  
  }
  
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
  Serial.println("Changing at+cwmode");
  String setup_cmd = "AT+CWMODE=3"; 
  esp.println(setup_cmd);
  delay(1000);

  Serial.println("Connecting to wifi");
  String connect_cmd = "AT+CWJAP=\""+ssid+"\",\""+passwd+"\"";
  esp.println(connect_cmd);
  delay(4000);
  if(esp.find("OK")) {
    Serial.println("Connected to wifi successfully!");
  }
  else {
    connectWifi();
    Serial.println("Cannot connect to wifi");
  }  
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int readHeartBeats() {  
  return analogRead(pulseSensorPurplePin);
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void handleLEDs(int signal) {
  if(signal > threshold){
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);
   }
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void httpPost(int data) {
  String data_str = String(data, HEX);
  
  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
  
  if( esp.find("OK")) {
    Serial.println("TCP connection ready");
  }
  delay(1000);
  
  String postRequest =
         "POST " + uri + " HTTP/1.0\r\n" +
         "Host: " + server + "\r\n" +
         "Accept: *" + "/" + "*\r\n" +
         "Content-Length: " + data_str.length() + "\r\n" +  
         "Content-Type: application/x-www-form-urlencoded\r\n" +
         "\r\n" + data_str;
  
  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
  
  esp.print(sendCmd);
  esp.println(postRequest.length());
  
  delay(500);
  
  if(esp.find(">")) {
    Serial.println("Sending..");
    esp.print(postRequest);
    
    if(esp.find("SEND OK")) {
      Serial.println("Packet sent");
      
      while (esp.available()) {
        String tmpResp = esp.readString();
        Serial.println(tmpResp);
      }
      
      // close the connection
      esp.println("AT+CIPCLOSE");
    }
  }
}
