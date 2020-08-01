
// include LCD library
#include <LiquidCrystal.h>

// define pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set LCD rows & columns
  lcd.begin(16, 2);
  
  // print hello world
  lcd.print("Hello World!");
}

void loop() {
}
