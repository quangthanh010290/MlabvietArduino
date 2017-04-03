//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iotdev-6b58b.firebaseio.com"
#define FIREBASE_AUTH "5zg8yd7bazlRj0heqBZvrduyyjykvshtRPCbjlYh"
#define WIFI_SSID "AutonomousSale"
#define WIFI_PASSWORD "autonomous123"
String chipId = "123";
byte mac[6];
bool l1 = false;
bool l2 = false;
bool l3 = false;
bool firstTime = true;
void wifiSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("MAC: "); 
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);  
}
void firebaseSetup(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
    if (Firebase.failed() == true) {
    Serial.print("Setup Error: ");
    Serial.println(Firebase.error());
  }   
  else{
    Serial.println("Setup OK: ");
    }
}
void setup() {
  Serial.begin(9600);
  wifiSetup();
  firebaseSetup();
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.print("Chip ID ");
  Serial.println(ESP.getChipId());
}
void getFirebaseData(){  
  FirebaseObject obj = Firebase.get("123/states");
  if (Firebase.failed() == true) {
    Serial.print("Reading Error: ");
    Serial.println(Firebase.error());
  }
  else{
    bool led1 = obj.getBool("001");
    if (firstTime == true){
      firstTime = false;
      l1 = led1;
      digitalWrite(LED_BUILTIN,!l1);
      Serial.print("Led1:");
    }
    else{
      if (l1 != led1){
        Serial.print("Led1:");
        Serial.println(led1);
        l1 = led1;   
        digitalWrite(LED_BUILTIN,!l1);         
      }
    }
    }
 
}

void loop() {
  getFirebaseData();

//  delay(500);
}
