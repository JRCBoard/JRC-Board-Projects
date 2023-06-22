#include <Arduino.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>

#define ONE_WIRE_BUS 4 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire); 


#include "time.h"

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "*****"
#define WIFI_PASSWORD "******"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBnKUifjcv3sK3gQ_-Fv8jB-ClMznI8rFU"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "sabitshahriarh@gmail.com"
#define USER_PASSWORD "123456789"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "ds18b20-530b3-default-rtdb.firebaseio.com"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String celciusPath = "/celcius";
String farenheitPath = "/farenheit";
String timePath = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;
FirebaseJson json;

const char* ntpServer = "pool.ntp.org";


float temperature;
float farenheit;


// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 10000;


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup(){
  Serial.begin(115200);

  
  initWiFi();
  sensor.begin();
  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";
}

void loop(){

  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //Get current timestamp
    timestamp = getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);
    

    parentPath= databasePath + "/" + String(timestamp);

    sensor.requestTemperatures();
  float c = sensor.getTempCByIndex(0);
  float f = sensor.getTempFByIndex(0);

  if (isnan(c) || isnan(f)) {                                                // Check if any reads failed.
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 
  Serial.print("Celcius: ");  Serial.print(c);
  String fireCelcius = String(c) + String("°C");                                         //convert integer humidity to string humidity
  Serial.print("°C  Fahrenheit: ");  Serial.print(f);  Serial.println(" F ");
  String fireFahrenheit = String(f) + String("F");                                                     //convert integer temperature to string temperature


    json.set(celciusPath.c_str(), String(fireCelcius));
    json.set(farenheitPath.c_str(), String(fireFahrenheit));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}
