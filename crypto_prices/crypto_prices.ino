#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h> 
#include <Arduino_JSON.h>

const char* ssid = "";
const char* password = "";

String api_key = "";
const char* url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?symbol=SOL,USDC&convert=MXN";
const char* fngurl = "https://api.alternative.me/fng/";
//String url = "https://pro-api.coinmarketcap.com/v1/cryptocurrency/quotes/latest?id=5426";

unsigned long lastTime = 0;
unsigned long timerDelay = 300000; // 5minutes in millis
//unsigned long timerDelay = 500;

String result;
String fngresult;
String resultArr[4]; //data: sol price in usd, sol price in mxn, usdc in mxn, Greed Index

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("Whats good!!");
  
  lcd.setCursor(5,1);   //Move cursor to character 2 on line 1
  lcd.print("Connecting...");
}

void loop() {
  
 //Send an HTTP POST request every 5 minutes
  if ((millis() - lastTime) > timerDelay) {
   
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      result = httpGETRequest(url);
      fngresult = httpGETRequest(fngurl);
      JSONVar myObject = JSON.parse(result);
      JSONVar fngMyObject = JSON.parse(fngresult);

      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      resultArr[0] = JSON.stringify(myObject["data"]["SOL"]["quote"]["MXN"]["price"]);
      resultArr[1] = JSON.stringify(myObject["data"]["USDC"]["quote"]["MXN"]["price"]);
      resultArr[2] = JSON.stringify(fngMyObject["data"][0]["value"]);
      resultArr[3] = JSON.stringify(fngMyObject["data"][0]["value_classification"]);
      
      Serial.print("$SOL = ");
      Serial.println(resultArr[0]);
      Serial.print("$USDC = ");
      Serial.println(resultArr[1]);
      Serial.print(resultArr[3]);
      Serial.println(resultArr[2]);

      lcd.setCursor(0,0);
      lcd.print("$SOL=");
      lcd.setCursor(5,0);
      lcd.print(resultArr[0]);
      
      lcd.setCursor(0,1);
      lcd.print("$USDC=");
      lcd.setCursor(6,1);
      lcd.print(resultArr[1]);

      lcd.setCursor(12,0);
      lcd.print("FGIX");
      
      lcd.setCursor(12,1);
      lcd.print(resultArr[2]);


    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-CMC_PRO_API_KEY",api_key);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}"; 

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
