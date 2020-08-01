/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Password.h>
Password password =Password("1234");
//char password[] = {'1','2','3','4'};
//char* str = "0";
//char str[] = {};
char tmp[16];
char tmp2[16];
int i = 0;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {53, 51, 49, 47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {41, 43, 45}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}
  
void loop(){
  char key = keypad.getKey();
  if (key){
      lcd.print(key);
      if ((key != '*') && (key != '#')){
        /*
        int len = strlen(str);
        str[len] = key;
        str[len+1]='\0';
        */
        password.append(key);
        tmp[i] = key;
        i++;
      }
      else if (key == '*')  {
        if(password.evaluate()) {
          lcd.setCursor(0,1);
          lcd.print("ACCESS GRANTED");
          password.reset();
          delay(2000);
          lcd.clear();
          i=0;  
          for(int j=0; j<16; j++){
              tmp[j] = '\0';  
          } 
        } 
        else {
          lcd.setCursor(0,1);
          lcd.print("ACCESS Denied"); 
          password.reset();
          delay(2000);
          lcd.clear();
          i=0;
          for(int j=0; j<16; j++){
              tmp[j] = '\0';  
          } 
        }
      } 
      else {
        //Password p =Password(tmp);
        lcd.setCursor(0,1);
        lcd.print("Changing Password"); 
        for(int j=0; j<16; j++){
              tmp2[j] = tmp[j];  
        } 
        password.set(tmp2);
        password.reset();
        delay(2000);
        lcd.clear();
        i=0;
        for(int j=0; j<16; j++){
              tmp[j] = '\0';  
        } 
      }
  }
  
}

//char *appendchar(char *szString, size_t strsize, char c)
//{
//  size_t len = strlen(szString);
//  if((len+1) < strsize)
//  {
//    szString[len++] = c;
//    szString[len] = '\0';
//    return szString;
//  }
//  return NULL;
//}
