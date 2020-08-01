#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Password.h>
#include <Servo.h>

//Servo
Servo myservo;
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
int temp = A1;              //new
int temps[5] = {24,25,26,27,28};
int newTmp = 0;
int r = 13;//buzzer
float tmp;
int led1 = 7;//heater
int led2 = 8;//cooler
int tmpI = 0;//temps array index

//Humidity
int humR;
int hum = 6;                //porte 0 nadarim!!!!!!!    //changed.
int humSet = 0;

//menu
int menuItem=0;

char *items[6];       //2 -> 6

//String items[6];
          
int selected = -1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(temp, INPUT);      //undefined temp: ghesmate temprature int temp = A1; ezafe beshe.
  pinMode(hum, INPUT);
  pinMode(r, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(9);

  items[0] = "display";     //new
  items[1] = "set temp";
  items[2] = "set humidity";
  items[3] = "set angle servo";
  items[4] = "change password";
  items[5] = "exit";
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
      if(selected == 0){
        displayStat(key);  
      }
      if(selected == 1){
        setTemps(key);
      }
      if(selected == 2){
        setHumidity(key);
      }
      if(selected == 3){
        //angle = 0;            //BUG: harvaght bekhaym adad bezanim angle 0 mishe.
        servoAngle(key);
      }
      if(selected == 4){
        changePassword(key);
      }
    }
    
  }



  //servo action
  //myservo.write(0); //in do khat baraye zamanie ke angle jadid set mishe
  //delay(3000);      //
  myservo.write(angle); 
  //delay(2500);      //delay nemikhad
  
  //temprature analyzing
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
  Serial.print("hum = ");
  Serial.println(humR);
  delay(500);
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
        menuItem = (menuItem+1)%6;     //be nazaram up o ke mizanim -1 beshe.
        lcd.clear();
        lcd.setCursor(0,0);            //lcd.clear() kafie.
        lcd.print(items[menuItem]); 
  }
  else if (inputKey == 'd'){
        menuItem = (menuItem-1)%6;     //be nazaram downo o ke mizanim +1 beshe.
        lcd.clear();
        lcd.setCursor(0,0);            //lcd.clear() kafie.
        lcd.print(items[menuItem]);  
  }
  else if (inputKey == 'n'){
    selected = menuItem;
    if(selected == 0){
        displayStat('-');  
    }
    if(selected == 1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("choose tmp");    //delay(500);lcd.clear();lcd.print("index:");lcd.print(tmpI);delay(500);lcd.clear();
        //new
        delay(1000);
        lcd.clear();
        lcd.print("index:");
        lcd.print(tmpI);
        delay(1000);
        lcd.clear();
        //end of new
        
    }
    if(selected == 2){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("choose mode");
    }
    if(selected == 3){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("enter angle");
        angle = 0;                  //new
    }
    if(selected == 4){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("enter new pass");
    }    
    if(selected == 5){
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

void setTemps(char inputKey){
      if (inputKey == 'u'){
        lcd.clear();
        lcd.setCursor(0,0);
        //tmpI++;                 //tmpI = (tmpI + 1) % 5 && baz be nazaram age up mizanim -- beshe.
        tmpI = (tmpI + 1) % 5;
        
        lcd.print("index:");
        lcd.print(tmpI);
        delay(500);
        lcd.clear();
      }
      else if (inputKey == 'd'){
        lcd.clear();
        lcd.setCursor(0,0);
        //tmpI--;               //tmpI = (tmpI - 1) % 5 && baz be nazaram age downo mizanim ++ beshe. 
        tmpI = (tmpI - 1) % 5;
        
        lcd.print("index:");
        lcd.print(tmpI);
        delay(500);
        lcd.clear(); 
      }
      else if (inputKey == 'n'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("setnewTmp:");
        lcd.setCursor(0,1);
        lcd.print(newTmp);  
        temps[tmpI] = newTmp;
        newTmp = 0;
        delay(1000);
        lcd.clear();
        selected = -1;
        lcd.setCursor(0,0);
        lcd.print(items[menuItem]); 
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
    lcd.print("Humidity:");
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
        lcd.print(" SET");
        delay(1000);
        lcd.clear();
        selected = -1;
        lcd.setCursor(0,0);
        lcd.print(items[menuItem]); 
    }
}


void servoAngle(char inputKey){
      if (inputKey == 'n'){
        lcd.setCursor(0,0);
        lcd.print("setAngle:");
        lcd.setCursor(0,1);
        lcd.print(angle);
        delay(1000);
        lcd.clear();
        selected = -1;
        lcd.print(items[menuItem]); 
      }
      else if (inputKey == 's'){
        lcd.setCursor(0,0);
        lcd.print("angle reset");
        angle = 0;
        delay(1000);
        lcd.clear();
      }
      else{
        lcd.clear();
        int digit = inputKey - '0';
        angle = (angle * 10) + digit;  
        lcd.setCursor(0,0);
        lcd.print("angle:");
        lcd.print(angle);
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
