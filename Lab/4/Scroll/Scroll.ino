/*

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>
int s1 = 8;
int s2 = 9;
int tmp1 = digitalRead(s1);
int tmp2 = digitalRead(s2);
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  tmp1 = digitalRead(s1);
  tmp2 = digitalRead(s2);
  if ((tmp1 == LOW)){
    lcd.scrollDisplayLeft();
    delay(500);
  }
  if ((tmp2 == LOW)){
    lcd.scrollDisplayRight();
    delay(500);
  }

}
