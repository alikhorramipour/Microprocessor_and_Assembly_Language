int  temp = A1;
int led1 = 8;
int led2 = 9;
int hum = 10;
int r = 12;
float tmp;
int humR;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(temp, INPUT);
  pinMode(hum, INPUT);
  pinMode(r, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tmp = analogRead(temp) / 3;
  humR = digitalRead(hum);
  Serial.print("tmp");
  Serial.println(tmp);
  if (tmp <=24){
    analogWrite(r, 15);
    Serial.println("bzzz");
  }
  else if ((tmp <= 25) && (tmp > 24)){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    analogWrite(r, 0);
  }
  else if ((tmp >= 27) && (tmp <28)){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    analogWrite(r, 0);
  }
  else if (tmp >= 28){
    analogWrite(r, 15);
    Serial.print("bzzz");
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW); 
    analogWrite(r, 0); 
  }
  Serial.print("hum = ");
  Serial.println(humR);
  delay(500);
  
  
}
