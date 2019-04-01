#//Arduino program to upload 3 sensor values to the
//Thingspeak server for the use of ML On Cere patients
include <SoftwareSerial.h>
#include<ESP8266WiFi.h>
#include "ThingSpeak.h"
SoftwareSerial s(D6,D5);
int data;
float stat;
WiFiClient Client;
const int trigPin = D1;
const int echoPin = D2;
int smokeA0 = A0;
int sensorThres = 400;
long duration;
int distance;


void setup() {
ThingSpeak.begin(Client);
WiFi.mode(WIFI_STA);  //to make a station
WiFi.begin("Vendatta","12345678i");
while(WiFi.status()!=WL_CONNECTED)  {
Serial.println("Connecting......");
delay(1000); }
Serial.println( WiFi.localIP() );
s.begin(9600);
pinMode(smokeA0, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
}
void loop() {
s.write("s");
if (s.available()>0)
{
data=s.read();
if(data>=200){
data-=200;}
else if(data >= 100){
data-=100;}
Serial.println(data);
ThingSpeak.writeField(745505,1,data,"UY8VUKZAF3819BV7");

}
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
ThingSpeak.writeField(745505,2,distance,"UY8VUKZAF3819BV7");
int analogSensor = analogRead(smokeA0);
Serial.print("Pin A0: ");
Serial.println(analogSensor);
ThingSpeak.writeField(745505,3,analogSensor,"UY8VUKZAF3819BV7");
}
