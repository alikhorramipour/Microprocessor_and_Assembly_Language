#include <Keypad.h>
int  temp = A1;
int led1 = 8;
int led2 = 9;
int r = 12;
float tmp;

int temps[5] = {24,25,26,27,28};
int i = 0;
int newTmp = 0;
 

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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(temp, INPUT);
  pinMode(r, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key){
      Serial.print(key);
      if (key == 'u'){
        i++;
        Serial.println("index: ");
        Serial.println(i);
      }
      else if (key == 'd'){
        i--; 
        Serial.println("index: ");
        Serial.println(i); 
      }
      else if (key == 'n'){
        Serial.println("newTmp set as: ");
        Serial.println(newTmp);  
        temps[i] = newTmp;
        newTmp = 0;
      }
      else if (key == 's'){
        Serial.println("newTmp reset ");
        newTmp = 0;
      }
      else{
        int digit = key - '0';
        Serial.println("digit: ");
        Serial.println(digit);
        newTmp = (newTmp * 10) + digit;
        Serial.println("newTmp: ");
        Serial.println(newTmp);
      }
      
  }
  tmp = (analogRead(temp) / 3) - 5;
  Serial.print("tmp");
  Serial.println(tmp);
  if (tmp <=temps[0]){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(r, HIGH);
    Serial.println("bzzz");
  }
  else if ((tmp <= temps[1]) && (tmp > temps[0])){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(r, LOW);
  }
  else if ((tmp >= temps[3]) && (tmp <temps[4])){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(r, LOW);
  }
  else if (tmp >= temps[4]){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(r, HIGH);
    Serial.print("bzzz");
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW); 
    digitalWrite(r, LOW);
  }
  delay(500);
  
  
}
