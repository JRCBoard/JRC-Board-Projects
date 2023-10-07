#include "ndcs_esp32.h"
#include <bits/stdc++.h>
// #include <nlohmann/json.hpp>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "addons/TokenHelper.h"
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

using namespace std;

char* WIFI_SSID;
char* WIFI_PASSWORD;
char* USER_EMAIL;
char* USER_PASSWORD;
char* DEVICE_ID;

#define FIREBASE_HOST "connect-jrc-iot.firebaseio.com"
#define API_KEY "AIzaSyBKK46Pt3QXzfecY-g10NlxYOTAZ_zXE5k"
#define RTDBURL "https://connect-jrc-iot-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define DATA_PATH "/d3tnjeA7JSAKVHNuOmRg/input/13"

FirebaseAuth auth;
FirebaseConfig config;

vector<int> gpio_pins = { 18, 19, 23, 26, 5, 13, 14, 15, 16, 17, 4, 2, 0 };

// Firebase

void init_firebase() {
  config.api_key = API_KEY;
  config.database_url = RTDBURL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
}

void wificonnection_init() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected");
}

void getOutputData() {
  FirebaseData firebaseData;
  FirebaseJson json;
  string path = "";
  string dev_id = DEVICE_ID;
  path = "/" + dev_id + "/output";

  if (Firebase.getJSON(firebaseData, path, &json)) {
    FirebaseJsonData result;

    for (int i : gpio_pins) {
      path = to_string(i);

      json.get(result, path);
      // Serial.println(result.to<String>());
      if (result.success) {
        json.get(result, path + "/datatype");
        if (result.to<String>() == "bool") {
          json.get(result, path + "/state");
          digitalWrite(i, result.to<bool>());
          Serial.println(String(i) + " " + String(result.to<bool>()));
        }
      }
    }
  } else {
    Serial.println("Failed to retrieve data from Firebase:");
    return;
  }
}

void getInputData() {
  FirebaseData firebaseData;
  FirebaseJson json;

  string path = "";
  string dev_id = DEVICE_ID;

  path = "/" + dev_id + "/input/";


  for (int i : gpio_pins) {
    string pinpath = to_string(i);
    pinpath += "/state";
    json.set(pinpath, to_string(digitalRead(i)));
  }

  String jsonData;
  json.toString(jsonData);

  // Send the JSON data to Firebase
  if (Firebase.updateNode(firebaseData, path, json)) Serial.println("pushed");
  else Serial.println(firebaseData.errorReason());
  Serial.println(jsonData);
}

void task1(void* parameter) {
  while (1) {
    if (Firebase.ready()) {
      getOutputData();
    } else {
      Serial.println("Firebase is'nt ready yet");
    }
    delay(10);
  }
}

void NDCS::begin(char* ssid, char* w_pass, char* email, char* u_pass, char* device_id) {
  WIFI_SSID = ssid;
  WIFI_PASSWORD = w_pass;
  USER_EMAIL = email;
  USER_PASSWORD = u_pass;
  DEVICE_ID = device_id;

  wificonnection_init();
  init_firebase();
  xTaskCreatePinnedToCore(task1, "Task 1", 10000, NULL, 1, &task1Handle, 1);
  //  xTaskCreatePinnedToCore(task2, "Task 2", 10000, NULL, 1, &task2Handle, 1);
}

void NDCS::send(int pin, char* data) {
  FirebaseData firebaseData;
  FirebaseJson json;

  string path = "";
  string dev_id = DEVICE_ID;

  path = "/" + dev_id + "/vpins/V" + to_string(pin);

  json.set("/state", data);
  if (Firebase.updateNode(firebaseData, path, json)) Serial.println("data pushed");
  else Serial.println(firebaseData.errorReason());
}
void NDCS::send(int pin, int data) {
  FirebaseData firebaseData;
  FirebaseJson json;
  string strdata = to_string(data);
  string path = "";
  string dev_id = DEVICE_ID;

  path = "/" + dev_id + "/vpins/V" + to_string(pin);

  json.set("/state", strdata);
  if (Firebase.updateNode(firebaseData, path, json)) Serial.println("data pushed");
  else Serial.println(firebaseData.errorReason());
}
void NDCS::send(int pin, float data) {
  FirebaseData firebaseData;
  FirebaseJson json;
  string strdata = to_string(data);
  string path = "";
  string dev_id = DEVICE_ID;

  path = "/" + dev_id + "/vpins/V" + to_string(pin);

  json.set("/state", strdata);
  if (Firebase.updateNode(firebaseData, path, json)) Serial.println("data pushed");
  else Serial.println(firebaseData.errorReason());
}

int NDCS::receive(int pin) {
  FirebaseData firebaseData;
  FirebaseJson json;

  string path = "";
  string dev_id = DEVICE_ID;

  path = "/" + dev_id + "/vpins/V" + to_string(pin);

  if (Firebase.getJSON(firebaseData, path, &json)) {
    FirebaseJsonData result;
    json.get(result, "/state");
    return result.to<int>();
  } else {
    Serial.println(firebaseData.errorReason());
    return 0;
  }
}

// void NDCS::loop() {
//   if (Firebase.ready()) {
//     getOutputs();
//     getInputs();
//   } else {
//     Serial.println("Firebase is'nt ready yet");
//   }
// }
