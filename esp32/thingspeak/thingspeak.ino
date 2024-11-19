

#include <WiFi.h>
#include "ThingSpeak.h"

#define ANALOG_PIN  5
#define DIGITAL_PIN 4

const char* ssid = "REPLACE_WITH_YOUR_SSID";   // your network SSID (name) 
const char* password = "REPLACE_WITH_YOUR_PASSWORD";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 12345;
const char * myWriteAPIKey = "XXXXXXXXXXXXXXXX";


unsigned long lastTime = 0;
unsigned long timerDelay = 30000;



void setup() {
  Serial.begin(115200);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  ThingSpeak.begin(client);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }


    int analogValue = analogRead(ANALOG_PIN);
    int digitalValue = digitalRead(DIGITAL_PIN);
    
    
    ThingSpeak.setField(1, analogValue);
    ThingSpeak.setField(2, digitalValue);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}