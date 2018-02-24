#include <ESP8266WiFi.h>

WiFiServer server(80); 
int LED_PIN =16;
void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("gaurd_iot","87654321");
  server.begin();


  Serial.begin(9600);
  IPAddress HTTPS_ServerIP=WiFi.softAPIP();
  Serial.print("Serial IP is: ");
  Serial.println(HTTPS_ServerIP);

  pinMode (LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly: 
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
    Serial.println("Somebody has connected :)");
    String request = client.readString();

    Serial.println(request);
    if (request.indexOf("/OFF") != -1)
    {
        digitalWrite (LED_PIN, HIGH);
     }else if(request.indexOf("/ON") != -1)
    {
        digitalWrite (LED_PIN, LOW);
     } 


     //Prepare the HTML Document to respond add button
     String s = "HTTP/1.1 200 OK\r\n";
     s+="Content-Type: text/html\r\n\r\n";
     s+="<!DOCTYPE HTML>\r\n<html>\r\n";
     s+="<br><button name=\"b1\" onclick=\"location.href='/ON'\">Turn LED ON</button>";
     s+="<br><br><br>";
     //s+="<br><input type\"submit\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
     s+="<br><button name=\"b1\" onclick=\"location.href='/OFF'\">Turn LED OFF</button>";
     s+="</html>\n";
     //Server the HTML document to browser
     client.flush();
     client.println(s);
     delay(1);
     Serial.println("Client disconnected");
    
}
