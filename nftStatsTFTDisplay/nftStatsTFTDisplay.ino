#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }

  Serial.println("\nConnected to the WIFI network");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());


  
  tft.init();
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  if((WiFi.status() == WL_CONNECTED)){
    HTTPClient client;
    client.begin("https://api-mainnet.magiceden.dev/v2/collections/smb_barrel/stats");
    int httpCode = client.GET();
    if(httpCode > 0){
      String payload = client.getString();

      char json[500];
      payload.toCharArray(json, 500);

      StaticJsonDocument<200> doc;
      deserializeJson(doc, json);

      const char* symbol = doc["symbol"];
      float fp =  doc["floorPrice"];
      float fpFloat = fp / 1000000000;
      int listed = doc["listedCount"];

      tft.drawString(String(symbol), 10, 55, 4);
      tft.drawString("FP: "+ String(fpFloat), 10, 90, 4);
      tft.drawString("Total Listed: "+ String(listed), 10, 120, 4);

      client.end();
      } else {
        Serial.println("Error on HTTP request");
      }
    } else {
      Serial.println("Connection Lost");
    }
    delay(10000);
}
