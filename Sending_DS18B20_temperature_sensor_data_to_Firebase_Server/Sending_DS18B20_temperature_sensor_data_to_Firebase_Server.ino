
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>                 // esp32 library
#include <FirebaseESP32.h>            // firebase library
#define ONE_WIRE_BUS 4 //DS18B20 konek ke Pin 4


#define FIREBASE_HOST "ds18b20-530b3-default-rtdb.firebaseio.com"
#define WIFI_SSID "Teacup" // Change the name of your WIFI
#define WIFI_PASSWORD "abcde66" // Change the password of your WIFI
#define FIREBASE_Authorization_key "4NhmhhnPqkdS5MhVvaRUli2b7f0xkuEdXLGuB7zZ" //Found at the project settings/service account/database secrets


FirebaseData firebaseData1;
FirebaseData firebaseData2;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);                                                    

 

void setup() {
  Serial.begin(115200);
  delay(500);               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                               // Will print local IP address
   sensor.begin();
   Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);

}

 
void loop() {
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
  delay(4000);
   
  if (Firebase.ready()) 
  {

 
 Firebase.setString(firebaseData1,"/DS18B20/Celcius", fireCelcius);                                  //setup path and send readings
 Firebase.setString(firebaseData2, "/DS18B20/Fahrenheit", fireFahrenheit);                                //setup path and send readings
 delay(200);
 


}

}
