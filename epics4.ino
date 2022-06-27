#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(D7, D8); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
WiFiClient espClient ;
PubSubClient client(espClient);
const char* ssid = "vu0607";
const char* password = "06072000";
const char* mqttServer = "nangluong.iotmind.vn";
const int mqttPort = 16766;
const char* mqttUser = "mind";
const char* mqttPassword = "123";
const char* status = "0";
String payload;
char buffCorrectTime[10];
char buffWrongTime[10];
#define trig1 D2
#define echo1 D3
#define trig2 D5
#define echo2 D6
#define nutnhan D4
#define ledxanh D0
#define leddo D1
double x = 0;
int k = 0;
float correctTime ;
float wrongTime ;
float realtime = 0.0;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.println("Connecting to wifi " );
    }
  Serial.println("Connected to wifi network");
  client.setServer(mqttServer, mqttPort);
  while(!client.connected()) {
    Serial.print(" connecting to mqtt ");
    if ( client.connect("esp8266server", mqttUser, mqttPassword )) {
      Serial.println("connected");
      }
    else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
      }  
    }
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(nutnhan, INPUT_PULLUP);
  pinMode(ledxanh, OUTPUT);
  pinMode(leddo, OUTPUT);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {
    while (true) {
      delay(0);
    }
  }
  myDFPlayer.volume(30);

}

void loop()
{
  x = KC2() / KC1() ;
  if (digitalRead(nutnhan) == 0) {
    k = 1 - k;
    delay(5);
    while (digitalRead(nutnhan) == 0) {}
    delay(5);
  }           
  if ( k == 1) {
      realtime ++ ;
    while ( KC1() > 70 ) {
      realtime++; 
      digitalWrite(ledxanh, 0);
      digitalWrite(leddo, 0);
      client.publish( "5MIT001/data" , "{\"status\": 2 }" ) ;
      delay(1000); 
      }
    if  (x > 1.2) {
      digitalWrite(ledxanh, 1);
      digitalWrite(leddo, 0);
      client.publish( "5MIT001/data" , "{\"status\": 0 }" ) ;
      correctTime = correctTime + 1.0 ;
    }
    else {
      digitalWrite(ledxanh, 0);
      digitalWrite(leddo, 1);
      client.publish( "5MIT001/data" , "{\"status\": 1 }" ) ;
      wrongTime = wrongTime + 1.0 ;
    }
    
    if ( wrongTime == 10) {
      myDFPlayer.play(1); delay(4000);
    }
    if ( realtime ==  20) {
      myDFPlayer.play(2); delay(4000);
    }
   
    if ( realtime >=60 ) {
  payload += "{\"correctTime\": ";
  dtostrf(correctTime, 4, 6, buffCorrectTime);
  payload += buffCorrectTime;
  dtostrf(wrongTime, 4, 6, buffWrongTime);
  payload += ", \"wrongTime\": ";
  payload += buffWrongTime;
  payload += ", \"status\": ";
  payload += status;
  payload += "}";  
  client.publish("5MIT001/data", payload.c_str() );
    realtime = 0;
    correctTime = 0;
    wrongTime = 0;
    } 
  }


  if ( k == 0) {
      while ( KC1() > 70) {
      client.publish( "5MIT001/data" , "{\"status\": 2 }" ) ;
      digitalWrite(ledxanh, 0);
      digitalWrite(leddo, 0); 
      delay(1000); 
      }
    
    if (x > 1.2   ) {
      digitalWrite(ledxanh, 1);
      digitalWrite(leddo, 0);
      client.publish( "5MIT001/data" , "{\"status\": 0 }" ) ;
    }
    else {
      digitalWrite(ledxanh, 0);
      digitalWrite(leddo, 1);
      client.publish( "5MIT001/data" , "{\"status\": 1 }" ) ;
    }
  }


  
  delay(990);
}
int KC1() {
  unsigned long duration;
  int x1;

  digitalWrite(trig1, 1);
  delayMicroseconds(5);
  digitalWrite(trig1, 0);
  duration = pulseIn(echo1, HIGH);
  x1 = (duration / 2 / 29.412);
  return x1;
}
int KC2() {
  unsigned long duration;
  int x2;

  digitalWrite(trig2, 1);
  delayMicroseconds(5);
  digitalWrite(trig2, 0);
  duration = pulseIn(echo2, HIGH);
  x2 = (duration / 2 / 29.412);
  return x2;
}  
