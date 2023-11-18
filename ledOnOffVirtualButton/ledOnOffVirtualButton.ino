/*************************************************************

  This sketch shows how to read values from Virtual Pins

  App dashboard setup:
    Slider widget (0...100) on Virtual Pin V0
    Author: @biccs
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2jt2uy32z"
#define BLYNK_TEMPLATE_NAME         "LED ON OFF"
#define BLYNK_AUTH_TOKEN            "POD6Q44vI7mEdiC2pKKiTgqSGfnHgY8k"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

const int ledPin = D0;
WidgetLED led1(V0);

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V0
BLYNK_WRITE(V0)
{
  if (led1.getValue()) {
    led1.off();
    digitalWrite(ledPin, LOW);
    Serial.println("LED on V0: off");
  } else {
    led1.on();
    digitalWrite(ledPin, HIGH);
    Serial.println("LED on V0: on");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  Blynk.run();
}
