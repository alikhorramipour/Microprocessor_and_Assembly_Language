/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

//int potpin = A0;  // analog pin used to connect the potentiometer
//int val;    // variable to read the value from the analog pin

////int s1 = 6;
////int s2 = 7;
////int s3 = 8;
////int tmp1;
////int tmp2;
////int tmp3;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  ////pinMode(s1, INPUT);
  ////pinMode(s2, INPUT);
  ////pinMode(s3, INPUT);
}

void loop() {
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  ////tmp1 = digitalRead(s1);
  ////tmp2 = digitalRead(s2);
  ////tmp3 = digitalRead(s3);
  //val = map(val, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180)
  /*////
  if((tmp1 == HIGH) && (tmp2 == LOW) && (tmp3 == LOW)){
      myservo.write(0); 
  }
  else if((tmp1 == LOW) && (tmp2 == HIGH) && (tmp3 == LOW)){
      myservo.write(90); 
  }
  else if((tmp1 == LOW) && (tmp2 == LOW) && (tmp3 == HIGH)){
      myservo.write(180); 
  }                // sets the servo position according to the scaled value
  */
  myservo.write(0); 
  delay(3000);
  myservo.write(90); 
  delay(3000);
  myservo.write(180); 
  delay(3000);
}
