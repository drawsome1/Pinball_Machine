void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A8,INPUT);
  pinMode(53,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(39,OUTPUT);
  digitalWrite(53,LOW);
  digitalWrite(51,LOW);
  digitalWrite(49,LOW);
  digitalWrite(47,LOW);
  digitalWrite(45,LOW);
  digitalWrite(43,LOW);
  digitalWrite(41,LOW);
  digitalWrite(39,LOW);
  

  //set's a timmer that runs every 976 ms
  OCR0A = 0;
  TIMSK0 |= _BV(OCIE0A);

}

//global 
int number = 0;

//timmer interrupt that will execute every 976ms
SIGNAL(TIMER0_COMPA_vect) 
{
  static int timeIntv = 800;
  timeIntv--;
  if( timeIntv == 0 )
  {
    //number++;
    timeIntv = 800;
  }
  displayNumber();
  
}

//main loop
void loop() {
  //sideLoop();
  //number++;
  
  if(analogRead(A8) < 511){
    //ball passed
    //increment i
    number += 10;
    //delay 
    delay(1000);
  }
  
}


void displayNumber(){
  static int i;
  i = i%4;

    switch(i)
    {
      case 0:
        digitalWrite(47,HIGH);
        digitalWrite(49,LOW);
        digitalWrite(51,LOW);
        digitalWrite(53,LOW);
        //delay(1);
        break;
      case 1:
        digitalWrite(47,LOW);
        digitalWrite(49,HIGH);
        digitalWrite(51,LOW);
        digitalWrite(53,LOW);
        //delay(1);
        break;
      case 2:
        digitalWrite(47,LOW);
        digitalWrite(49,LOW);
        digitalWrite(51,HIGH);
        digitalWrite(53,LOW);
        //delay(1);
        break;
      case 3:
        digitalWrite(47,LOW);
        digitalWrite(49,LOW);
        digitalWrite(51,LOW);
        digitalWrite(53,HIGH);
        //delay(1);
        break;
    }
    
    digitalWrite(43,LOW);
    shiftOut(45,41,LSBFIRST,~toShiftReg(numToDisplay(number,i)));
    digitalWrite(43,HIGH);
    i++;
}

/*displays one digit of the number 
 * 
 * int fullNum - full number ie 9999
 * int counter - the digit that will be displayed
 *  ie. counter = 3 (far left) will be displayed
 */
int numToDisplay(int fullNum, int counter){
  int digit;
  int temp = fullNum;
  if( counter == 0 )
  {
    digit = fullNum % 10;
  }
  else{
    for( int i = 0; i < counter; i++)
    {
      temp = temp / 10;
      digit = temp % 10;
    }
  }
  return digit;
}

/*
 * converts the digit into the corresponding segments
 * NOTE: this is backwards so in numberDisplay we use ~
 */
byte toShiftReg(int digit)
{
  byte num;
  switch(digit)
  {
    case 0:
      num = B11111100;
      break;
    case 1:
      num = B01100000;
      break;
    case 2:
      num = B11011010;
      break;
    case 3:
      num = B11110010;
      break;
    case 4:
      num = B01100110;
      break;
    case 5:
      num = B10110110;
      break;
    case 6:
      num = B10111110;
      break;
    case 7:
      num = B11100000;
      break;
    case 8:
      num = B11111110;
      break;
    case 9:
      num = B11100110;
      break;
  }
  return num;
}

