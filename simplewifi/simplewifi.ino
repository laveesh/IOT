#include <ESP8266WiFi.h>

WiFiServer server(80); 
void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello_IoT","87654321");
  server.begin();


  Serial.begin(9600);
  IPAddress HTTPS_ServerIP=WiFi.softAPIP();
  Serial.print("Serial IP is: ");
  Serial.println(HTTPS_ServerIP);
}

void loop() {
  // put your main code here, to run repeatedly:

}
