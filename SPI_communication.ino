#include <ESP8266WiFi.h>//Upload library
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//WiFiClient client;

const char* ssid = "nodemcu"; //Enter your wifi name
const char* password = "sanjay"; //Enter your wifi password
IPAddress local_ip(192,168,0,100);
IPAddress gateway(192,168,0,100);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);
int enable = 5 ;
int enable1 = 4 ;
int enable2 = 14 ;
char HTML[] = "<html><body><button onClick=\"window.location.href='/ON'\">Table1</button><br><button onClick=\"window.location.href='/ONN'\">Table2</button><br><button onClick=\"window.location.href='/OF'\">Table3</button><br><button onClick=\"window.location.href='/OFF'\">Table4</button></body></html>" ;

void t3(){
  digitalWrite(enable , HIGH);
   digitalWrite(enable1 , HIGH);
    digitalWrite(enable2 , HIGH);
}
void t2(){
 digitalWrite(enable , LOW); 
  digitalWrite(enable1 , HIGH);
   digitalWrite(enable2 , HIGH);
}
void t4(){
 digitalWrite(enable , LOW); 
  digitalWrite(enable1 ,LOW);
   digitalWrite(enable2 , HIGH);
}
void t1(){
 digitalWrite(enable , HIGH); 
  digitalWrite(enable1 ,LOW);
   digitalWrite(enable2 , HIGH);
}
void handleRoot() {
  server.send(200, "text/html", HTML);
} 
void setup()
{
 Serial.begin(9600);
 WiFi.softAP(ssid, password);
 WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  server.on("/",handleRoot);
  server.on("/ON",t1);
   server.on("/ONN",t2);
    server.on("/OF",t3);
  server.on("/OFF",t4);
 
  pinMode(enable, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
 
  server.begin();
}

void loop(){
server.handleClient();   
}
