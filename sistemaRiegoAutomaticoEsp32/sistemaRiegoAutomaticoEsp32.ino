/* AUTHOR: @biccs */

#define BLYNK_TEMPLATE_ID "TMPL2IuVI48-o"
#define BLYNK_TEMPLATE_NAME "PLANTA"
#define BLYNK_AUTH_TOKEN "ijVRWSFguVQnQZ6Y2OnQ0uVH5IImIvnZ"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>

#include <WiFi.h>
#include "time.h"
#include "sntp.h"

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

const char* ssid = "Totalplay-D2AA";
const char* password = "D2AA7A05qNdQq3H2";

const char* ntpServer1 = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int dayLightOffset_sec = -25200; //GMT-7

const int targetHour = 9;     // 9 am
const int targetMinute = 0;   // 30 minutes
const int targetSecond = 0;


void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

int relay = 13;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin GIOP27 as an output.
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");

  configTime(gmtOffset_sec, dayLightOffset_sec, ntpServer1);
  printLocalTime();

  //WiFi.disconnect(true);
 // WiFi.mode(WIFI_OFF);

  Blynk.begin(auth, ssid, password);

  pinMode(relay, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Blynk.run();
  // printLocalTime();

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    int currentHour = timeinfo.tm_hour;
    int currentMinute = timeinfo.tm_min;
    int currentSecond = timeinfo.tm_sec;

    int remainingTimeSeconds = (targetHour - currentHour) * 3600 + (targetMinute - currentMinute) * 60 + (targetSecond - currentSecond);
    if (remainingTimeSeconds < 0) {
      remainingTimeSeconds = ( 86400 - abs(remainingTimeSeconds) );
    }
    int hours = remainingTimeSeconds / 3600;
    int minutes = (remainingTimeSeconds % 3600) / 60;
    int seconds = remainingTimeSeconds % 60;

    Serial.print("Time left until next irrigation: ");
    Serial.print(hours);
    Serial.print(" hours, ");
    Serial.print(minutes);
    Serial.print(" minutes, ");
    Serial.print(seconds);
    Serial.println(" seconds");

    Blynk.virtualWrite(V0, hours);
    Blynk.virtualWrite(V1, minutes);
    Blynk.virtualWrite(V2, seconds);
    //   Check if it's time to irrigate
    if (currentHour == targetHour && currentMinute == targetMinute && currentSecond == targetSecond) {
      digitalWrite(relay, HIGH); // turn on pump for 2 seconds
      Serial.println("Current Flowing");
      delay(8000);
      digitalWrite(relay, LOW);  // turn off pump for 5 seconds
      Serial.println("Current Stopped Flowing");
      delay(5000);
    }
  } else {
    Serial.println("No time available (yet)");
     Blynk.virtualWrite(V0, 5);
    Blynk.virtualWrite(V1, 5);
    Blynk.virtualWrite(V2, 5);
  }
  delay(1000);
  //  printLocalTime();
  //  digitalWrite(relay, HIGH); // turn on pump 2 seconds
  //  Serial.println("Current Flowing");
  //  delay(2000);
  //  digitalWrite(relay, LOW);  // turn off pump 5 seconds
  //  Serial.println("Current not Flowing");
  //  delay(5000);
}
