int in1 = 15;
int in2 = 10;
int led = 8;
int tmp1 = digitalRead(in1);
int tmp2 = digitalRead(in2);
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tmp1 = digitalRead(in1);
  int tmp2 = digitalRead(in2);
  if ((tmp1 == LOW) && (tmp2 == LOW))
  {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  }
  if ((tmp1 == LOW) && (tmp2 == HIGH))
  {
    digitalWrite(led, LOW);
  }
  if ((tmp1 == HIGH) && (tmp2 == LOW))
  {
    digitalWrite(led, HIGH);
  }
  if ((tmp1 == HIGH) && (tmp2 == HIGH))
  {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}
