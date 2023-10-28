#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>

//const char* ssid = "";
//const char* password = "";

TFT_eSPI tft = TFT_eSPI();

void setup() {
  //  Serial.begin(115200);
  //  WiFi.begin(ssid, password);
  //  Serial.print("Connecting to WIFI");
  //
  //  while(WiFi.status() != WL_CONNECTED){
  //    Serial.print(".");
  //    delay(500);
  //    }
  //
  //  Serial.println("\nConnected to the WIFI network");
  //  Serial.print("IP address: ");
  //  Serial.print(WiFi.localIP());

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  tft.init();
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  tft.drawString("Inicia Scaneo!...", 10, 20, 4);
  int n = WiFi.scanNetworks();


  if (n == 0) {
    tft.fillScreen(TFT_BLACK);
    Serial.println("no networks found");
    tft.drawString("0 redes encontradas", 10, 40, 4);
  } else {
    tft.fillScreen(TFT_BLACK);
    Serial.print(n);
    Serial.println(" networks found");
    tft.drawString(String(n), 100, 40, 4);
    tft.drawString("redes encontradas", 10, 60, 4);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      tft.drawString(String(i + 1) + ": ", 10, 0 + (i * 40), 2);
      tft.drawString(String(WiFi.SSID(i)), 30, 0 + (i * 40), 2);
      if (WiFi.RSSI(i) < -90) {
        tft.setTextColor(TFT_DARKGREEN, TFT_RED);
        tft.drawString("La peor", 10, 20 + (i * 40), 2);
      } else if (WiFi.RSSI(i) < -80) {
        tft.setTextColor(TFT_PURPLE, TFT_YELLOW);
        tft.drawString("Mala signal", 10, 20 + (i * 40), 2);
      } else if (WiFi.RSSI(i) < -70) {
        tft.setTextColor(TFT_BLUE, TFT_ORANGE);
        tft.drawString("Okay signal", 10, 20 + (i * 40), 2);
      } else if (WiFi.RSSI(i) < -60) {
        tft.setTextColor(TFT_BLUE, TFT_GREENYELLOW);
        tft.drawString("Buena signal", 10, 20 + (i * 40), 2);
      } else if (WiFi.RSSI(i) < -30) {
        tft.setTextColor(TFT_PURPLE, TFT_GREEN);
        tft.drawString("Muy buena", 10, 20 + (i * 40), 2);
      } else if (WiFi.RSSI(i) > -30) {
        tft.setTextColor(TFT_PURPLE, TFT_DARKGREEN);
        tft.drawString("La mejor", 10, 20 + (i * 40), 2);
      }

      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString(" - ", 80, 20 + (i * 40), 2);
        tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
        tft.drawString("Red Publica", 100, 20 + (i * 40), 2);
      } else {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString(" - ", 80, 20 + (i * 40), 2);
        tft.setTextColor(TFT_WHITE, TFT_RED);
        tft.drawString(" - Red Privada", 100, 20 + (i * 40), 2);
      }
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      delay(10);
    }
  }
  Serial.println("");
  //  if ((WiFi.status() == WL_CONNECTED)) {
  //    tft.drawString("Conexion Exitosa!", 10, 55, 4);
  //    tft.drawString(String(WiFi.status()), 10, 90, 4);
  //  } else {
  //    Serial.println("Connection Lost");
  //    tft.drawString("Conexion Perdida", 10, 55, 4);
  //    tft.drawString(String(WiFi.status()), 10, 90, 4);
  //  }

  delay(10000);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);
}
