#include <TFT_eSPI.h>
#include <SPI.h>

const int humedadSuelo = 4;
int valorHumedad;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(humedadSuelo, INPUT);
  tft.init();
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  valorHumedad = analogRead(humedadSuelo);

  Serial.print("Humedad del suelo: ");
  Serial.print(valorHumedad);
  Serial.print(" %\n");

  tft.drawString("Humedad: ", 10,55,4);
  tft.drawString(String(valorHumedad), 10,90,4);
}
