#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Password.h>
#include <Servo.h>

//Servo
Servo myservo;
int servoSet = 0;
int angle = 0;

//Password
Password password =Password("1234");
char tmp1[16];
char tmp2[16];
int passIndex = 0;
int entered = 0;//0 if still asking for password, 1 if entered the system

//LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Keypad
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

//temprature
int temp = A1;              
int temps[5] = {24,25,26,27,28};
int newTmp = 0;
int r = 13;//buzzer
float tmp;
int led1 = 7;//heater
int led2 = 8;//cooler
int tmpI = 0;//temps array index

//Humidity
int humR;
int hum = 6;                
int humSet = 0;
int humLED = 30;

//menu
int menuItem=0;
char *items[4];       
//String items[6]; 
int selected = -1;

//mode setting menu
int selectedMode = -1;
int mode = 0;

//mode items
int selectedModeItem = -1;
int modeItem = 0;
char *modeItems[3];

int setter[3] = {37.5,0,1};
int hatcher[3] = {37,1,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(temp, INPUT);      
  pinMode(hum, INPUT);
  pinMode(humLED, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(9);

  items[0] = "Display";    
  items[1] = "Mode setting";
  items[2] = "Change password";
  items[3] = "Exit";

  modeItems[0] = "Temperature";
  modeItems[0] = "Humidity";
  modeItems[0] = "Turner";
}

void loop() {
  // put your main code here, to run repeatedly:
  humR = digitalRead(hum);
  tmp = (analogRead(temp) / 3) - 5;
  
  char key = keypad.getKey();
  if (key){
    if(entered == 0){
      if(key != 'n'){
        password.append(key);
        lcd.print(key);  
      }
      else
        evaluatePassword();
    }
    else{
      if(selected == -1){
        menuList(key);  
      }
      else if(selected == 0){
        displayStat(key);  
      }
      else if(selected == 1 && selectedMode != -1 && selectedModeItem == 0){
        setTemps(key);
      }
      else if(selected == 1 && selectedMode != -1 && selectedModeItem == 1){
        setHumidity(key);
      }
      else if(selected == 1 && selectedMode != -1 && selectedModeItem == 2){
        setServo(key);
      }
      else if(selected == 1 && selectedMode != -1 && selectedModeItem == -1){
        modeList(key);
      }
      else if(selected == 1 && selectedMode == -1 && selectedModeItem == -1){  //mode setting
        modeSetting(key);
      }
      else if(selected == 2){
        changePassword(key);
      }
    }
  }


  if(mode == 0){
    if(tmp < setter[0] && tmp > (setter[0] - 10)){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }else if(tmp < (setter[0] - 10)){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(r, HIGH);
      Serial.println("bzzz");
    }
    myservo.write(45);
    delay(2000);
    myservo.write(0);
    delay(2000);
    myservo.write(45);
    delay(2000);
    myservo.write(90);
  }else if(mode == 1){
    if(tmp < hatcher[0] && tmp > (hatcher[0] - 10)){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
    }else if(tmp < (hatcher[0] - 10)){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(r, HIGH);
      Serial.println("bzzz");
    }
    
    if(humR == 0 && hatcher[1] == 1){
      digitalWrite(humLED, HIGH);
    }else{
      digitalWrite(humLED, LOW);
    }
    
  }


  

  
  
//  myservo.write(angle); 
//
//  //temprature analyzing
//  Serial.print("tmp");
//  Serial.println(tmp);
//  if (tmp <=temps[0]){
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, LOW);
//    digitalWrite(r, HIGH);
//    Serial.println("bzzz");
//  }
//  else if ((tmp <= temps[1]) && (tmp > temps[0])){
//    digitalWrite(led1, HIGH);
//    digitalWrite(led2, LOW);
//    digitalWrite(r, LOW);
//  }
//  else if ((tmp >= temps[3]) && (tmp <temps[4])){
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, HIGH);
//    digitalWrite(r, LOW);
//  }
//  else if (tmp >= temps[4]){
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, HIGH);
//    digitalWrite(r, HIGH);
//    Serial.print("bzzz");
//  }
//  else{
//    digitalWrite(led1, LOW);
//    digitalWrite(led2, LOW); 
//    digitalWrite(r, LOW);
//  }
//  Serial.print("hum = ");
//  Serial.println(humR);
//  delay(500);
}

boolean evaluatePassword(){
  if(password.evaluate()) {
          lcd.setCursor(0,1);
          lcd.print("ACCESS GRANTED");
          password.reset();
          delay(2000);
          lcd.clear();
          passIndex=0;  
          for(int j=0; j<16; j++){
              tmp1[j] = '\0';  
          }
          entered = 1; 
          lcd.setCursor(0,0);         //lcd.clear() kafie.
          lcd.print(items[menuItem]); 
   } 
   else {
          lcd.setCursor(0,1);
          lcd.print("ACCESS Denied"); 
          password.reset();
          delay(2000);
          lcd.clear();
          passIndex=0;
          for(int j=0; j<16; j++){
              tmp1[j] = '\0';  
          } 
   }
}

void menuList(char inputKey){
  if (inputKey == 'u'){
        menuItem = (menuItem - 1) % 4;     //be nazaram up o ke mizanim -1 beshe.
        lcd.clear();
        lcd.setCursor(0,0);            //lcd.clear() kafie.
        lcd.print(items[menuItem]); 
  }
  else if (inputKey == 'd'){
        menuItem = (menuItem + 1) % 4;     //be nazaram downo o ke mizanim +1 beshe.
        lcd.clear();
        lcd.setCursor(0,0);            //lcd.clear() kafie.
        lcd.print(items[menuItem]);  
  }
  else if (inputKey == 'n'){
    selected = menuItem;
    if(selected == 0){
        displayStat('-');  
    }
    if(selected == 1){      //mode setting
        if (mode == 0)
          lcd.print("Setter");
        else
          lcd.print("Hatcher");
    }
    if(selected == 2){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("enter new pass");
    }
    if(selected == 3){
        exitMenu();                  
    }
  }
}

void displayStat(char inputKey){
  if(inputKey == 's') {
    selected = -1;        //clear the lcd and lcd.print(items[menuItem])
    //new
    lcd.clear();
    lcd.print(items[menuItem]);
    //end of new
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("tmp,humid,angle:");
    lcd.setCursor(0,1);
    lcd.print(tmp);
    lcd.print(",");
    lcd.print(hum);
    lcd.print(",");
    lcd.print(angle);
    delay(1000); 
    lcd.clear();
  }
}

void modeSetting(char inputKey){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mode: ");
    if (inputKey == 'u'){
        mode = (mode + 1) % 2;
        if (mode == 0)
          lcd.print("Setter");
        else
          lcd.print("Hatcher");
    }
    else if (inputKey == 'd'){
        mode = (mode + 1) % 2; 
        if (mode == 0)
          lcd.print("Setter");
        else
          lcd.print("Hatcher");
    }
    else if (inputKey == 's'){
      lcd.clear();
      lcd.setCursor(0,0);
      selected = -1;
      lcd.print(items[menuItem]);
    }
    else if (inputKey == 'n'){
        selectedMode = mode;
        lcd.print("Selected");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(modeItems[modeItem]); 
    }
}

void modeList(char inputKey){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Item: ");
    if (inputKey == 'u'){
        modeItem = (modeItem - 1) % 3;
        lcd.print(modeItems[modeItem]);
    }
    else if (inputKey == 'd'){
        modeItem = (modeItem + 1) % 3; 
        lcd.print(modeItems[modeItem]);
    }
    else if (inputKey == 'n'){
        selectedModeItem = modeItem;
        lcd.print("Selected");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(modeItems[modeItem]); 
    }
}

void setTemps(char inputKey){
      if (inputKey == 'n'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("setnewTmp:");
        lcd.setCursor(0,1);
        lcd.print(newTmp);  
        
        if(selectedMode == 0){  //setter
          setter[0] = newTmp;
        }else if(selectedMode == 1){  //hatcher
          hatcher[0] = newTmp;
        }
        
        newTmp = 0;
        delay(1000);
        lcd.clear();
        selectedModeItem = -1;
        lcd.setCursor(0,0);
        lcd.print(modeItems[modeItem]); 
      }
      else if (inputKey == 's'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("newTmp reset");
        newTmp = 0;
        delay(1000);
        lcd.clear();
      }
      else{
        lcd.clear();
        int digit = inputKey - '0';
        newTmp = (newTmp * 10) + digit;
        lcd.setCursor(0,0);
        lcd.print("newTmp:");
        lcd.print(newTmp);
      }
}

void setHumidity(char inputKey){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity: ");
    if (inputKey == 'u'){
        humSet = (humSet+1)%2; // humSet = (humSet + 1) %2
        if (humSet == 0)
          lcd.print("Low");
        else
          lcd.print("High");
    }
    else if (inputKey == 'd'){
        humSet = (humSet+1)%2; // humSet = (humSet + 1) %2
        if (humSet == 0)
          lcd.print("Low");
        else
          lcd.print("High");
    }
    else if (inputKey == 'n'){
        lcd.print("SET");
         if(selectedMode == 0){  //setter
          setter[1] = humSet;
        }else if(selectedMode == 1){  //hatcher
          hatcher[1] = humSet;
        }
        delay(1000);
        lcd.clear();
        selectedModeItem = -1;
        lcd.setCursor(0,0);
        lcd.print(modeItems[modeItem]); 
    }
}

void setServo(char inputKey){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Servo: ");
    if (inputKey == 'u'){
        servoSet = (servoSet+1)%2; 
        if (servoSet == 0)
          lcd.print("Passive");
        else
          lcd.print("Active");
    }
    else if (inputKey == 'd'){
        servoSet = (servoSet+1)%2; // humSet = (humSet + 1) %2
        if (servoSet == 0)
          lcd.print("Passive");
        else
          lcd.print("Active");
    }
    else if (inputKey == 'n'){
        lcd.print("SET");
         if(selectedMode == 0){  //setter
          setter[2] = servoSet;
        }else if(selectedMode == 1){  //hatcher
          hatcher[2] = servoSet;
        }
        delay(1000);
        lcd.clear();
        selectedModeItem = -1;
        lcd.setCursor(0,0);
        lcd.print(modeItems[modeItem]); 
    }
}

void changePassword(char inputKey){      //changed
  if (inputKey == 'n'){
    lcd.setCursor(0,1);
    lcd.print("Changing Password"); 
    for(int j=0; j<16; j++){
          tmp2[j] = tmp1[j];  
    } 
    password.set(tmp2);
    password.reset();
    delay(2000);
    lcd.clear();
    passIndex=0;
    for(int j=0; j<16; j++){
          tmp1[j] = '\0';  
    } 
    selected = -1;
    lcd.setCursor(0,0);
    lcd.print(items[menuItem]); 
  }
  else if (inputKey == 's'){
        passIndex=0;  
        for(int j=0; j<16; j++){
            tmp1[j] = '\0';  
        }
        lcd.setCursor(0,0);
        lcd.print("reset input");
        delay(1000);
        lcd.clear();
  }
  else{
        lcd.clear();
        lcd.setCursor(0,0);
        tmp1[passIndex] = inputKey;
        passIndex++;
        for(int j=0; j<passIndex; j++){
            lcd.print(tmp1[j]);  
        }
  }   
}

void exitMenu(){
   lcd.clear(); 
   lcd.setCursor(0,0);
   lcd.print("Exiting");
   entered = 0;
   selected = -1;
   delay(2000);
   lcd.clear(); 
}
