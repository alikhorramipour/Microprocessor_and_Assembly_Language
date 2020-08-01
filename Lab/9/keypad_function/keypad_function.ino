#include <Keypad.h>
int mode = 0;
int i1 = 2;
int i2 = 3;
int i3 = 4;
int i4 = 5;
int i5 = 6;
int i6 = 7;
int i7 = 8;
int i8 = 9;
int i9 = 10;
const byte ROWS = 5; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'f','g','#','*'},
  {'1','2','3','u'},
  {'4','5','6','d'},
  {'7','8','9','s'},
  {'l','0','r','n'}
};
byte colPins[COLS] = {53, 51, 49, 47}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {37, 39, 41, 43, 45}; //connect to the row pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);
  pinMode(i5, OUTPUT);
  pinMode(i6, OUTPUT);
  pinMode(i7, OUTPUT);
  pinMode(i8, OUTPUT);
  pinMode(i9, OUTPUT);
  
}
  
void loop(){
  char key = keypad.getKey();
  if (key){
      Serial.print(key);
      if (key == 'f'){
         mode = 0;  
      }
      if (key == 'g'){
         mode = 1;  
      }
      if (key == '1'){
         if(mode == 0){
            digitalWrite(i1, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i1, LOW);
         }
      }
      if (key == '2'){
         if(mode == 0){
            digitalWrite(i2, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i2, LOW);
         }
      }
      if (key == '3'){
         if(mode == 0){
            digitalWrite(i3, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i3, LOW);
         }
      }
      if (key == '4'){
         if(mode == 0){
            digitalWrite(i4, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i4, LOW);
         }
      }
      if (key == '5'){
         if(mode == 0){
            digitalWrite(i5, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i5, LOW);
         }
      }
      if (key == '6'){
         if(mode == 0){
            digitalWrite(i6, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i6, LOW);
         }
      }
      if (key == '7'){
         if(mode == 0){
            digitalWrite(i7, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i7, LOW);
         }
      }
      if (key == '8'){
         if(mode == 0){
            digitalWrite(i8, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i8, LOW);
         }
      }
      if (key == '9'){
         if(mode == 0){
            digitalWrite(i9, HIGH);
         }
         else if(mode == 1){
            digitalWrite(i9, LOW);
         }
      }
  }
  
}
