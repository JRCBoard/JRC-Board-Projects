#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <LiquidCrystal.h>
#include <DHT.h>
DHT dht(23, DHT11);
LiquidCrystal lcd(4, 17, 16, 15, 14, 05);
AsyncWebServer server(80);

float temp, humidity;
uint32_t timer, timer2;
String html;
const int button = 26, led = 13;
bool state = 0;


const char* ssid = "NAF Tech_WiFi";
const char* password = "N@f Tech";

const char index_html[] PROGMEM = R"rawliteral(
  <html> 
  <head> 
    <title>
      JRC Board
    </title> 
    <meta http-equiv='refresh' content='2'>
    <content=\"width=device-width, initial-scale=1\">
    <style>
      html { 
        font-family: Helvetica;
        fone-size: 200; 
        display: inline-block; 
        margin: 0px auto; 
        text-align: center;
      }
      .background {
        background-image: url("https://t4.ftcdn.net/jpg/04/61/23/23/360_F_461232389_XCYvca9n9P437nm3FrCsEIapG4SrhufP.jpg");
        background-size: auto;
      }
    </style>
  </head>

  <body>
    <div class="background">
      <br>
      <h1>
        JRC Board Temperature and Humidity Server
      </h1>
      <br>
      <h2>
        <span>Temperature:</span> 
        <span id="temperature">%TEMPERATURE%</span>
        <span class="units">&deg;C</span>
      </h2>
      <h2>
        <span>Humidity</span>
        <span id="humidity">%HUMIDITY%</span>
        <span class="units">&percnt;</span>
      </h2> 
      <a href="https://jrcboard.com">
        <img src="https://new.jrcboard.com/wp-content/uploads/2023/04/Jrc-Landiscape-logo.png"
          style="
            object-fit: scale-down;
            width: 300px;
            height: 100px;
         "/>
      </a>
    </div>
  </body>
  </html>
  
  )rawliteral";

String processor(const String& var) {
  if (var == "TEMPERATURE") {
    return String(temp);
  } else if (var == "HUMIDITY") {
    return String(humidity);
  }
  return String();
}


void display() {
  if (!state) {
    lcd.setCursor(0, 0);
    lcd.print("TEMP: " + String(temp) + char(223) + "C    ");
    lcd.setCursor(0, 1);
    lcd.print("HUMID: " + String(humidity) + "%    ");
  } else {
    if (millis() - timer2 > 5000) {
      lcd.setCursor(0, 0);
      (WiFi.status() == WL_CONNECTED) ? lcd.print(" WiFi Connected ") : lcd.print("WiFi Unavailable");
      lcd.setCursor(0, 1);
      lcd.print(WiFi.localIP());
      timer2 = millis();
    }
  }
}

void reading() {
  if (millis() - timer > 5000) {
    temp = dht.readTemperature();
    humidity = dht.readHumidity();
    Serial.println(WiFi.localIP());
    timer = millis();
  }
}

bool push() {
  uint32_t t = 0;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    digitalWrite(13, 1);
    while (!digitalRead(button)) {
      delay(20);
      t += 20;
    }
    digitalWrite(13, 0);
    if (t) return 1;
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  lcd.begin(16, 2);
  dht.begin();
  // WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);
  // WiFi.softAP("JRC Board", "robotics");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  server.begin();
}

void loop() {
  display();
  reading();
  if (push()) state = !state;
}