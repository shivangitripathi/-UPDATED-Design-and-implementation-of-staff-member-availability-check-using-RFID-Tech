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

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "**********.firebaseio.com"	//(Edit) Firebase project name
#define FIREBASE_AUTH "****************************************"	//(Edit) Database secret key ( Settings>Project settings>Service accounts>Database secrets )
#define WIFI_SSID "********"	//(Edit) Name of wifi
#define WIFI_PASSWORD "********"	//(Edit) Wifi password

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          15         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int cnt=10;
String strID="";
String cid="8224111699";	//(Edit) RFID Card ID [We have used just 2 cards]
String cid1="12811622163";	//(Edit) RFID Card ID


void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

int n = 0;

void loop() {
  
// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  
  // set value
//   one=database.ref("User");
//  one.setString("Status", "Not Avail");
  //Firebase.User.setFloat("Status", 289);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(10);

    //while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  for (byte i = 0; i < mfrc522.uid.size; i++){
    strID +=mfrc522.uid.uidByte[i];

  }
  // update value
  if(strID==cid){
  
  Firebase.setString("A210/A1/Status", "avail");	//(Edit) Edit the first parameter according to your Firebase branch
  Serial.println(strID);
strID=""; 

  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  delay(10);}
else{
    Firebase.setString("A210/A1/Status", "not_avail");	//(Edit) Edit the first parameter according to your Firebase branch
    
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }

  delay(10);}





  if(strID==cid1){
  
  Firebase.setString("A210/A2/Status", "avail");	//(Edit) Edit the first parameter according to your Firebase branch
  Serial.println(strID); 
strID="";
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  delay(10);}
else{
    Firebase.setString("A210/A2/Status", "not_avail");	//(Edit) Edit the first parameter according to your Firebase branch
    
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }


  delay(10);}

  // get value 
  Serial.print("Status: ");
  Serial.println(Firebase.getString("A210/A1/Status"));	//(Edit) Edit the first parameter according to your Firebase branch
Serial.println(cnt);
 
  if(cnt==0){
    Serial.println("Reset..");
    ESP.restart();
  }
 
  cnt--;
  delay(50);
 }