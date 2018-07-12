#include <Servo.h>

Servo servo1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  pinMode(12, OUTPUT);
  
  pinMode(A2, INPUT);     //input for servo
  pinMode(A1, INPUT);     //input for DC

  pinMode(3, INPUT);     //D3 input
  pinMode(4, OUTPUT);    //D4 output

  servo1.attach(A0);
}

void loop() {
  //////////////////////////Servo begin/////////////////
  //servo initialization
  int pot1;
  int angle1;

  // read pot1 value for servo
  pot1 = analogRead(A2);
  
  // set servo angle
  angle1 = 180.0 * pot1 / 1023;
  servo1.write(angle1);

//  Serial.println(angle1);
  //////////////////////////Servo end/////////////////


  //////////////////////////DC Motor begin/////////////
  //DC initialization
  int pot2;
  int pwm;
  
  pot2 = analogRead(A1);

  pwm = 255.0 * pot2/1023;

  analogWrite(12, pwm);

  //Serial.println(pwm);

  delay(20);

  //////////////////////////DC Motor end/////////////


  if( digitalRead(3) == LOW )
  {
    digitalWrite(4, HIGH);
  }
  else
  {
    digitalWrite(4, LOW);
  }

  Serial.println(digitalRead(3));
  
  delay(20);

  
  
}
