#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Redmi";
const char* password = "lavish98";
//WiFi.mode(WIFI_AP);
//WiFi.softAP("SKSingh_IoT","12345678");

WiFiServer server(80); 
int LED_PIN =16;
void setup() {


  
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP("gaurd_iot","87654321");
  server.begin();
  //Static ip, gateway, netmask
  WiFi.config(IPAddress(10,171,83,100), IPAddress(10,171,83,148), IPAddress(255,255,255,0));

  Serial.begin(9600);
  IPAddress HTTPS_ServerIP=WiFi.softAPIP();
  //Serial.print("Serial IP is: ");
  //Serial.println(HTTPS_ServerIP);

  pinMode (LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);

  //connect to wifi network
     Serial.println();
     Serial.println();
     Serial.print("Connecting to");
     Serial.println(ssid);

     WiFi.begin(ssid,password);

     while(WiFi.status()!=WL_CONNECTED){
      delay(500);
      Serial.print(".");
     }
     Serial.println("");
     Serial.println("WIFI Connected");

     //start the server
     server.begin();
     Serial.println("Server Started");

     //print IP address
     Serial.print("Use This url to connect");
     Serial.print("http://");
     Serial.print(WiFi.localIP());
     Serial.print("/");
     
}

void loop() {
    //server.handelClient();
    
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
