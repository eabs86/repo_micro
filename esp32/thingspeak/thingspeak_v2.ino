#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
unsigned long myChannelNumber = YOUR_THINGSPEAK_CHANNEL_NUMBER;
const char* myWriteAPIKey = "YOUR_THINGSPEAK_CHANNEL_API_KEY";

WiFiClient  client;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
}

void loop() {
  int analogValue = analogRead(ANALOG_PIN);
  int digitalValue = digitalRead(DIGITAL_PIN);

  ThingSpeak.setField(1, analogValue);
  ThingSpeak.setField(2, digitalValue);

  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(20000); // ThingSpeak update rate is 15 seconds
}
