#include <LiquidCrystal.h>
//Pines de conexión
LiquidCrystal lcd(22,23,5,18,19,21);
 
void setup() {
  // Inicializar LCD
  lcd.begin(16, 2); //Dimensión del LCD
}
 
void loop() {
  lcd.setCursor(0, 0); //Posición línea 1 del LCD (Col, fil)
  lcd.print("e/acc"); 
  lcd.setCursor(0, 1); //Posición línea 2 del LCD
  lcd.print("we are so back!");

//Comandos útiles
//https://www.arduino.cc/reference/en/libraries/liquidcrystal/ 
//lcd.scrollDisplayLeft();
//lcd.scrollDisplayRight();
//lcd.rightToLeft();
//lcd.blink();

  delay(1000);
}
