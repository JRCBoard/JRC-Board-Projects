#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>
#include <DHT.h>
DHT dht(23, DHT11);
LiquidCrystal lcd(4, 17, 16, 15, 14, 05);
WebServer server(80);

float temp, humidity;
uint32_t timer;
String html;

const char* ssid = "NAF Tech_WiFi";
const char* password = "N@f Tech";
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void sendData() {
  html = "<html><head><title>JRC Board</title>"; 
  html += "<content=\"width=device-width, initial-scale=1\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style></head>";

  html += "<body><h1>JRC Board Temperature and Humidity Server</h1><br>";  //Header of the webserver
  html += "<h2>Temperature: " + String(temp) + " &deg;C</h2>";         //print temparature value
  html += "<h2>Humidity: " + String(humidity) + " %</h2>";                 //print humidity value
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  dht.begin();
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("STA Failed to configure");
  // }
  WiFi.begin(ssid, password);
  server.on("/", sendData);
  server.begin();
}

void loop() {
  display();
  reading();
  server.handleClient();
}
