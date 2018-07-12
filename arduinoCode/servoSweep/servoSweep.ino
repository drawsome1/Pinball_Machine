/*used to sweep the servo motor
 * 
 */
#include <Servo.h>

//servo object
Servo servo;  //can make up to 12 per boards

int servoPos = 0;
void setup() {
  // put your setup code here, to run once:
  servo.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  for( servoPos = 60; servoPos <= 120; servoPos++)
  {
    servo.write(servoPos);
//    if( servoPos >= 0 && servoPos < 45)
//    {
//      delay(9);
//    }
//    else if( servoPos > 135 && servoPos <= 180 )
//    {
//      delay(5);
//    }
//    else
//    {
//      if( servoPos == 90 )
//      {
//        delay(30);
//      }
//      delay(13);
//    }
  delay(10);
  }
  delay(10);

  for( servoPos = 120; servoPos >= 60; servoPos--)
  {
    servo.write(servoPos);
//    if( servoPos >= 0 && servoPos < 45)
//    {
//      delay(5);
//    }
//    else if( servoPos > 135 && servoPos <= 170 )
//    {
//      delay(5);
//    }
//    else
//    {
//      if( servoPos == 90 )
//      {
//        delay(30);
//      }
//      delay(13);
//    }
  delay(10);

  }
  delay(10);  
}

