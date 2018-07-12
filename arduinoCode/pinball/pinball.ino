#define DEBUG 0
#include <Servo.h>

//servo Object
Servo servo;

// 7 Segment Display
#define DIGIT1_ON digitalWrite(pin_digit1,HIGH)
#define DIGIT1_OFF digitalWrite(pin_digit1,LOW)
#define DIGIT10_ON digitalWrite(pin_digit10,HIGH)
#define DIGIT10_OFF digitalWrite(pin_digit10,LOW)
#define DIGIT100_ON digitalWrite(pin_digit100,HIGH)
#define DIGIT100_OFF digitalWrite(pin_digit100,LOW)
#define DIGIT1000_ON digitalWrite(pin_digit1000,HIGH)
#define DIGIT1000_OFF digitalWrite(pin_digit1000,LOW)
#define DISPLAY_OFF {DIGIT1_OFF; DIGIT10_OFF; DIGIT100_OFF; DIGIT1000_OFF;}

// Kevin's Controller
#define LATCH_HI digitalWrite(pin_latch, HIGH)
#define LATCH_LO digitalWrite(pin_latch, LOW)
#define CLK_HI digitalWrite(pin_clk, HIGH)
#define CLK_LO digitalWrite(pin_clk, LOW)
#define CUR_BUTTON digitalRead(pin_din)

// Richard's Controller
#define LEFT_BUTTON digitalRead(pin_left)
#define START_BUTTON digitalRead(pin_start)
#define RIGHT_BUTTON digitalRead(pin_right)
#define CP1 digitalRead(pin_cp1)
#define CP2 digitalRead(pin_cp2)
#define CP3 digitalRead(pin_cp3)
#define CP4 digitalRead(pin_cp4)

//LED 
#define ALL_LEDS_OFF setLedPwmR(0); setLedPwmG(0); setLedPwmB(0)

// Sensors
#define EMITTER1_ON digitalWrite(pin_emitter1, HIGH)
#define EMITTER1_OFF digitalWrite(pin_emitter1, LOW)
#define EMITTER2_ON digitalWrite(pin_emitter2, HIGH)
#define EMITTER2_OFF digitalWrite(pin_emitter2, LOW)
#define READ_RECEIVER1 analogRead(pin_receiver1)
#define READ_RECEIVER2 analogRead(pin_receiver2)

// 7 Segment Display
const uint8_t pin_digit1000 = 47;
const uint8_t pin_digit100 = 45;
const uint8_t pin_digit10 = 43;
const uint8_t pin_digit1 = 41;
const uint8_t pin_ser = 39;
const uint8_t pin_rclk = 37;
const uint8_t pin_srclk = 35;

// Kevin's Controller
const uint8_t pin_latch = 53;
const uint8_t pin_clk = 51;
const uint8_t pin_din = 49;
const uint8_t button_a = 0b10000000;
const uint8_t button_b = 0b01000000;
const uint8_t button_select = 0b00100000;
const uint8_t button_start = 0b00010000;
const uint8_t button_up = 0b00001000;
const uint8_t button_down = 0b00000100;
const uint8_t button_left = 0b00000010;
const uint8_t button_right = 0b00000001;

//Richard's Controller
const uint8_t pin_right = 36;
const uint8_t pin_start = 34;
const uint8_t pin_left = 32;
const uint8_t pin_cp1 = 44;
const uint8_t pin_cp2 = 42;
const uint8_t pin_cp3 = 40;
const uint8_t pin_cp4 = 38;

// Servo/moving door
const uint8_t pin_servo = 11;

//LED 
const uint8_t pin_ledR = 8;
const uint8_t pin_ledG= 9;
const uint8_t pin_ledB = 10;


// Sensors and buzzer
const uint8_t pin_emitter1 = 50;
const uint8_t pin_emitter2 = 48;
const uint8_t pin_buzzer = 46;
const uint8_t pin_receiver1 = 54;
const uint8_t pin_receiver2 = 55;

// Flippers
const uint8_t pin_lflipper = 2;
const uint8_t pin_rflipper = 3;

// DC Motor
const uint8_t pin_dcmotor = 4;

// Shooter
const uint8_t pin_shooter = 7;

// Tilters
const uint8_t pin_ltilter = 5;
const uint8_t pin_rtilter = 6;

// Piezo Element
const uint8_t pElem = A2;
const uint8_t pCastle = A3;

// Declarations
void displayNumber(uint32_t number);
uint8_t digitToDisplay(uint32_t fullNum, uint8_t pos);
uint8_t toShiftReg(uint8_t digit);
void readButtons(void);
void printButtonStates(void);
void readSensors(void);
void printSensorVals(void);
void beep(uint32_t freq, uint32_t duration_ms);
void beepn(uint8_t num, uint32_t freq, uint32_t duration_ms);
bool isButtonTriggered(uint8_t button_mask);
bool isButtonPressed(uint8_t button_mask);
void setLeftFlipperPwm(uint8_t pwm);
void setRightFlipperPwm(uint8_t pwm);
void setDCMotorPwm(uint8_t pwm);
void setShooterPwm(uint8_t pwm);
void shoot(void);
void flipLeft(void);
void flipRight(void);
void setLeftTilterPwm(uint8_t pwm);
void setRightTilterPwm(uint8_t pwm);
void tiltLeft(void);
void tiltRight(void);
void startGame(void);
void stopGame(void);
void increaseScore(uint32_t num);
void setLedPwmR(uint32_t pwm);
void setLedPwmG(uint32_t pwm);
void setLedPwmB(uint32_t pwm);
void fadeR(uint32_t pwm);
void fadeG(uint32_t pwm);
void fadeB(uint32_t pwm);
void flashR(void);
void flashG(void);
void flashB(void);
void flash(uint8_t r, uint8_t g, uint8_t b);
void movingDoor(void);

// Settings
const uint8_t flipper_maxpwm = 80;
const uint32_t flipper_holdpwm = 10;
const uint8_t dcmotor_maxpwm = 10;
const uint8_t shooter_maxpwm = 90;
const uint8_t tilter_maxpwm = 100;
const uint8_t tilter_holdpwm = 20;
const uint32_t loop_period_us = 1000;
const uint32_t receiver1_threshold = 300;
const uint32_t receiver2_threshold = 300;
const uint32_t shooter_period_ms = 500;
const uint32_t shooter_onTime_ms = 200;
const uint32_t flipper_period_ms = 50;
const uint32_t flipper_onTime_ms = 100;
const uint32_t tilter_period_ms = 500;
const uint32_t tilter_onTime_ms = 200;
const uint32_t rampScoreInterval_ms = 50;

//const uint32_t castleScoreInterval_ms = 500;
const uint32_t piezoElementScoreInterval_ms = 500;
int pElementReader = 0;
int pCastleReader = 0;

const uint32_t timeInterval_ms = 3000;

const uint32_t servoInterval_ms = 30;
const uint32_t servoMaxAngle = 70;
const uint32_t servoMidAngle = 103;
const uint32_t resetGameInterval_ms = 2000;
const uint32_t maxLedPwmR = 30;   // 0 to 100
const uint32_t maxLedPwmG = 30;  // 0 to 100
const uint32_t maxLedPwmB = 30;  // 0 to 100
const uint32_t fadeInterval_ms = 50;
const uint32_t roundLostInterval_ms = 2000;

// Global variables
uint32_t score = 0;
uint8_t button_states = 0;
uint32_t receiver1_val = 0;
uint32_t receiver2_val = 0;
bool b_isGameOn = false;
bool b_isStartButtonPressed = false;
uint32_t ledPwmR = 0;
uint32_t ledPwmG = 0;
uint32_t ledPwmB = 0;
const int threshold = 800;
const int castleThresh = 1000;


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  /***** Pin IO config ******/
  // 7 Segment Display
  pinMode(pin_digit1,OUTPUT);
  pinMode(pin_digit10,OUTPUT);
  pinMode(pin_digit100,OUTPUT);
  pinMode(pin_digit1000,OUTPUT);
  pinMode(pin_ser,OUTPUT);
  pinMode(pin_rclk,OUTPUT);
  pinMode(pin_srclk,OUTPUT);
  // Kevin's Controller
  pinMode(pin_latch, OUTPUT);
  pinMode(pin_clk, OUTPUT);
  pinMode(pin_din, INPUT);
  // Richard's Controller
  pinMode(pin_left, INPUT);
  pinMode(pin_start,INPUT);
  pinMode(pin_right,INPUT);
  // Sensors and buzzer
  pinMode(pin_emitter1, OUTPUT);
  pinMode(pin_emitter2, OUTPUT);
  pinMode(pin_receiver1, INPUT);
  pinMode(pin_receiver2, INPUT);
  pinMode(pin_buzzer, OUTPUT);
  // Flippers
  pinMode(pin_lflipper, OUTPUT);
  pinMode(pin_rflipper, OUTPUT);
  // DC Motor
  pinMode(pin_dcmotor, OUTPUT);
  // Shooter
  pinMode(pin_shooter, OUTPUT);
  // Tilters
  pinMode(pin_ltilter, OUTPUT);
  pinMode(pin_rtilter, OUTPUT);
  // Servo
  servo.attach(pin_servo);
  // Copper Tape
  pinMode(pin_cp1, INPUT);
  pinMode(pin_cp2, INPUT);
  // LEDs
  pinMode(pin_ledR, OUTPUT);
  pinMode(pin_ledG, OUTPUT);
  pinMode(pin_ledB, OUTPUT);
  
  /***** Default states *****/
  // 7 Segment Display
  DISPLAY_OFF;
  // Kevin's Controller
  LATCH_LO;
  CLK_LO;
  // Sensors
  EMITTER1_ON;
  EMITTER2_ON;
  // Flippers
  setLeftFlipperPwm(0);
  setRightFlipperPwm(0);
  // DC Motor
  setDCMotorPwm(0);
  // Shooter
  setShooterPwm(0);
  // Tilters
  setLeftTilterPwm(0);
  setRightTilterPwm(0);
  // Servo
  servo.write(servoMidAngle);
  // LEDs
  ALL_LEDS_OFF;
  analogWrite(pin_ledR, maxLedPwmR);
  
//  // Timer 1 interrupt
//  OCR1A = 0;
//  TIMSK1 |= _BV(OCIE1A);
//
//  // Timer 3 interrupt
//  OCR3A = 0;
//  TIMSK3 |= _BV(OCIE3A);
//
//  // Timer 4 interrupt
//  OCR4A = 0;
//  TIMSK4 |= _BV(OCIE4A);

  // Beep when ready
  beep(1000, 200);

  delay(100);
}

//SIGNAL(TIMER3_COMPA_vect)
//{
//}
//
//SIGNAL(TIMER4_COMPA_vect)
//{
//}
//
//SIGNAL(TIMER1_COMPA_vect)
//{
//}


void loop()
{
  uint32_t startTime_us = micros();
  readButtons();

  // Start and stop the game
  if (isButtonTriggered(button_start) || isStartTriggered()) {
    // Stop game
    if (b_isGameOn) {
     stopGame();
    }
    // Start game
    else {
      startGame();
    }
  }
  
  // Game is on
  if (b_isGameOn) {

    if(score > 0){
      //increment score based on time
      static uint32_t lastScoreTime_ms = millis();
      if( millis() - lastScoreTime_ms > timeInterval_ms ){
        increaseScore(1);
        lastScoreTime_ms = millis();
      }
    }
    
    readSensors();
    displayNumber(score);
    movingDoor();

    if (isButtonTriggered(button_select)) {
      ; // do nothing
    }
    if (isButtonTriggered(button_down)) {
      ; // do nothing
    }

    //Increment score if the ramp makes connection
    rampScore();

    //Increment score if the ball hits inside the castle doorway
    castleScore();

    //Increment score if the piezo element is hit
    pElementScore();
  
    // Fire flipper when buttons are pressed
    flipLeft();
    flipRight();
  
    // Shoots when ball is detected or when button is pressed
    shoot();
  
    // Tilts when buttons are pressed
    tiltLeft();
    tiltRight();

    //Update LEDs
    fadeR(0);
    fadeG(maxLedPwmG);
    fadeB(0);
    
    
    //if (DEBUG) printButtonStates();
    //if (DEBUG) printSensorVals();
  
    //Serial.println(micros() - startTime_us);

    //round lost
    if(isRoundLost()){
      //display score so people can see it after they lose
      Serial.println(score);
      resetGame();
      flash(maxLedPwmR, maxLedPwmG, maxLedPwmB);
      beep(2000, 300);
    }
  }
  // Game is off
  else {
    fadeR(maxLedPwmR);
    fadeG(0);
    fadeB(0);
  }

//  Serial.println(micros() - startTime_us);
  
  while(micros() - startTime_us < loop_period_us);
}

/* Iterates over the 7 segment display to display one digit per call */
void displayNumber(uint32_t number)
{
  static uint8_t pos = 0;
  uint32_t num = number;

  if (num > 9999) {
    num = 9999;
  }
  pos = pos%4;

  switch(pos)
  {
    case 0:
      // 1s place
      DIGIT1_ON;
      DIGIT10_OFF;
      DIGIT100_OFF;
      DIGIT1000_OFF;
      break;
    case 1:
      // 10s place
      DIGIT1_OFF;
      DIGIT10_ON;
      DIGIT100_OFF;
      DIGIT1000_OFF;
      break;
    case 2:
      // 100s place
      DIGIT1_OFF;
      DIGIT10_OFF;
      DIGIT100_ON;
      DIGIT1000_OFF;
      break;
    case 3:
      // 1000s place
      DIGIT1_OFF;
      DIGIT10_OFF;
      DIGIT100_OFF;
      DIGIT1000_ON;
      break;
  }

  digitalWrite(pin_rclk,LOW);
  shiftOut(pin_ser, pin_srclk, LSBFIRST, toShiftReg(digitToDisplay(num, pos)));
  digitalWrite(pin_rclk,HIGH);
  pos++;
}

/* Displays one digit of the full number in the specified position
 * 
 * uint32_t fullNum - 4 digit number (ie 9999)
 * uint8_t pos - digit position (3 2 1 0) -> (1000s 100s 10s 1s)
 *  ie. counter = 3 (far left) will be displayed
 */
uint8_t digitToDisplay(uint32_t fullNum, uint8_t pos)
{
  uint8_t digit;
  uint32_t temp = fullNum;

  if(pos == 0)
  {
    digit = fullNum % 10;
  }
  else{
    for(uint8_t i = 0; i < pos; i++)
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
uint8_t toShiftReg(uint8_t digit)
{
  uint8_t num;
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
  return ~num;
}

/* Read button states 
 *  Buttons are active-low
 *  Negated so that 1 corresponds to pressed state.
 *  (MSB) A B SEL START UP DOWN LEFT RIGHT (LSB)
 */
void readButtons() {
  uint8_t buffer = 0;

  // Take a snapshot
  LATCH_HI;
  LATCH_LO;

  // Read button states into buffer
  buffer |= CUR_BUTTON << 7;
  for (uint8_t i = 0; i < 7; i++) {
    CLK_HI;
    CLK_LO;
    buffer |= CUR_BUTTON << 6-i;
  }
  CLK_HI;
  CLK_LO;
     
  button_states = ~buffer;
}

void printButtonStates() {
  Serial.println("A\tB\tSEL\tSTART\tUP\tDOWN\tLEFT\tRIGHT");
  for (uint8_t i = 0; i < 8; i++) {
     Serial.print((button_states >> 7-i & 1) == 1); 
     Serial.print("\t");
  }
  Serial.println();
}

void readSensors() {
  receiver1_val = READ_RECEIVER1;
  receiver2_val = READ_RECEIVER2;
}

void printSensorVals() {
    Serial.print("RE1 = ");
    Serial.print(receiver1_val);
    Serial.print(" | RE1 = ");
    Serial.print(receiver2_val);
    Serial.println();
}

void beep(uint32_t freq, uint32_t duration_ms) {
  tone(pin_buzzer, freq, duration_ms);
}

void beepn(uint8_t num, uint32_t freq, uint32_t duration_ms) {
  if (num > 0) {
    for (uint8_t i = 0; i < num - 1; i++) {
      tone(pin_buzzer, freq, duration_ms);
      delay(duration_ms + 20);
    }
    tone(pin_buzzer, freq, duration_ms);
  }
}

bool isButtonPressed(uint8_t button_mask) {
  if (button_states & button_mask) {
    return true;
  }
  return false;
}

bool isStartTriggered(){
  static bool start_pressed = false;
  static bool start_released = true;

  if(START_BUTTON == HIGH){
    if( start_released ) {
      start_released = false;
      start_pressed = true;
      return true;
    }
  }
  else{
    start_released = true;
  }
  return false;
}

bool isButtonTriggered(uint8_t button_mask) {
  static bool a_pressed = false, b_pressed = false, select_pressed = false, start_pressed = false, up_pressed = false, down_pressed = false, left_pressed = false, right_pressed = false;
  static bool a_released = true, b_released = true, select_released = true, start_released = true, up_released = true, down_released = true, left_released = true, right_released = true;
  if (button_states & button_mask) {
    switch (button_mask) 
    {
      case button_a:
        if (a_released) {
          a_pressed = true;
          a_released = false;
          return true;
        }
        break;
      case button_b:
        if (b_released) {
          b_pressed = true;
          b_released = false;
          return true;
        }
        break;
      case button_select:
        if (select_released) {
          select_pressed = true;
          select_released = false;
          return true;
        }
        break;
      case button_start:
        if (start_released) {
          start_pressed = true;
          start_released = false;
          return true;
        }
        break;
      case button_up:
        if (up_released) {
          up_pressed = true;
          up_released = false;
          return true;
        }
        break;
      case button_down:
        if (down_released) {
          down_pressed = true;
          down_released = false;
          return true;
        }
        break;
      case button_left:
        if (left_released) {
          left_pressed = true;
          left_released = false;
          return true;
        }
        break;
      case button_right:
        if (right_released) {
          right_pressed = true;
          right_released = false;
          return true;
        }
        break;
    }
  }
  else {
    switch (button_mask) {
    case button_a:
      a_released = true;
      break;
    case button_b:
      b_released = true;
      break;
    case button_select:
      select_released = true;
      break;
    case button_start:
      start_released = true;
      break;
    case button_up:
      up_released = true;
      break;
    case button_down:
      down_released = true;
      break;
    case button_left:
      left_released = true;
      break;
    case button_right:
      right_released = true;
      break;
    }
  }
  return false;
}

// Set left flipper duty cycle
void setLeftFlipperPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > flipper_maxpwm) {
    pwm = flipper_maxpwm;
  }
  analogWrite(pin_lflipper, 255*pwm/100);
}

// Set right flipper duty cycle
void setRightFlipperPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > flipper_maxpwm) {
    pwm = flipper_maxpwm;
  }
  analogWrite(pin_rflipper, 255*pwm/100);
}

// Set DC Motor duty cycle
void setDCMotorPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > dcmotor_maxpwm) {
    pwm = dcmotor_maxpwm;
  }
  analogWrite(pin_dcmotor, 255*pwm/100);
}

// Set shooter duty cycle
void setShooterPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > shooter_maxpwm) {
    pwm = shooter_maxpwm;
  }
  analogWrite(pin_shooter, 255*pwm/100);
    //if(DEBUG) Serial.println(255*pwm/100);

}

// Set left tilter duty cycle
void setLeftTilterPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > tilter_maxpwm) {
    pwm = tilter_maxpwm;
  }
  analogWrite(pin_ltilter, 255*pwm/100);
}

// Set right tilter duty cycle
void setRightTilterPwm(uint8_t pwm) {
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > tilter_maxpwm) {
    pwm = tilter_maxpwm;
  }
  analogWrite(pin_rtilter, 255*pwm/100);
}

// Fire solenoid toward ramp when ball is detected, increase score
void shoot(void) {
  static uint32_t onTime_ms = 0;
  static bool b_isShooterOn = false;
  static uint32_t recharge_ms = shooter_period_ms;
  static bool b_released = false;
  if (recharge_ms > 0) {
    recharge_ms--;
  }
  if (b_released && recharge_ms == 0 && isButtonPressed(button_up)) {
    if (DEBUG) Serial.println("User shoot");
 
    // Activate solenoid
    setShooterPwm(50);
    b_isShooterOn = true;
    b_released = false;

    // Reset countdown timer
    recharge_ms = shooter_period_ms;
  }
  else if (recharge_ms == 0 && receiver1_val < receiver1_threshold) {
    if (DEBUG) Serial.println("Auto shoot");
    // Activate solenoid
    setShooterPwm(shooter_maxpwm);
    b_isShooterOn = true;
    b_released = false;

    // Reset countdown timer
    recharge_ms = shooter_period_ms;

    // Increase score
    increaseScore(2);
  }
  

  if (b_isShooterOn) {
    onTime_ms++;
  }

  // Turn off after onTime has elapased
  if (onTime_ms > shooter_onTime_ms) {
     setShooterPwm(0);
     b_isShooterOn = 0;
     onTime_ms = 0;
     b_released = true;
  }



  // detect if button is released
  if (!isButtonPressed(button_b)) {
    b_released = true;
  }
  
  
}

// Engage the left flipper
void flipLeft(void) {
  static uint32_t onTime_ms = 0;
  static bool b_isFlipperOn = false;
  static uint32_t recharge_ms = flipper_period_ms;
  static bool b_released = false;
  
  if (recharge_ms > 0) {
    recharge_ms--;
  }

  // if button is pressed, activate
  if (b_released && recharge_ms == 0 && (isButtonPressed(button_b) || (LEFT_BUTTON == HIGH))) {
    if (DEBUG) Serial.println("Activate left flipper");
    
    // Activate left flipper
    setLeftFlipperPwm(flipper_maxpwm);
    b_isFlipperOn = true;
    b_released = false;
    
    // Reset countdown timer
    recharge_ms = flipper_period_ms;
  }
 
  
  if (b_isFlipperOn) {
    onTime_ms++;
  }

  // Set to hold state after onTime has elapsed
  if (onTime_ms > flipper_onTime_ms) {
   setLeftFlipperPwm(flipper_holdpwm);
   b_isFlipperOn = 0;
   onTime_ms = 0;
  }

  // if button is released, turn off
  if (!isButtonPressed(button_b) && LEFT_BUTTON == LOW) {
    setLeftFlipperPwm(0);
    b_released = true;
  }
  
}

// Engage the right flipper
void flipRight(void) {
  static uint32_t onTime_ms = 0;
  static bool b_isFlipperOn = false;
  static uint32_t recharge_ms = flipper_period_ms;
  static bool b_released = false;
  if (recharge_ms > 0) {
    recharge_ms--;
  }

  // if button is pressed, activate
  if (b_released && recharge_ms == 0 && (isButtonPressed(button_a) || RIGHT_BUTTON == HIGH)) {
    if (DEBUG) Serial.println("Activate right flipper");
    // Activate right flipper
    setRightFlipperPwm(flipper_maxpwm);
    b_isFlipperOn = true;
    b_released = false;
    
    // Reset countdown timer
    recharge_ms = flipper_period_ms;
  }
  
  if (b_isFlipperOn) {
    onTime_ms++;
  }

  // Set to hold state after onTime has elapsed
  if (onTime_ms > flipper_onTime_ms) {
   setRightFlipperPwm(flipper_holdpwm); 
   b_isFlipperOn = 0;
   onTime_ms = 0;
  }

  // if button is released, turn off
  if (!isButtonPressed(button_a) && RIGHT_BUTTON == LOW) {
    setRightFlipperPwm(0);
    b_released = true;
  }

}

// Raise the right tilter to tilt left
void tiltLeft(void) {
  static uint32_t onTime_ms = 0;
  static bool b_isTilterOn = false;
  static uint32_t recharge_ms = tilter_period_ms;
  static bool b_released = false;
  if (recharge_ms > 0) {
    recharge_ms--;
  }

  // if button is pressed, activate
  if (b_released && recharge_ms == 0 && isButtonPressed(button_left)) {
    if (DEBUG) Serial.println("Tilt left");
    // Raise right tilter
    setRightTilterPwm(tilter_maxpwm);
    b_isTilterOn = true;
    b_released = false;
    
    // Reset countdown timer
    recharge_ms = tilter_period_ms;
  }
  
  if (b_isTilterOn) {
    onTime_ms++;
  }

  // Set to hold state after onTime has elapsed
  if (onTime_ms > tilter_onTime_ms) {
   setRightTilterPwm(tilter_holdpwm);
   b_isTilterOn = 0;
   onTime_ms = 0;
  }

  // if button is released, turn off
  if (!isButtonPressed(button_left)) {
    setRightTilterPwm(0);
    b_released = true;
  }
  
}

// Raise the left tilter to tilt right
void tiltRight(void) {
  static uint32_t onTime_ms = 0;
  static bool b_isTilterOn = false;
  static uint32_t recharge_ms = tilter_period_ms;
  static bool b_released = false;
  if (recharge_ms > 0) {
    recharge_ms--;
  }

  // if button is pressed, activate
  if (b_released && recharge_ms == 0 && isButtonPressed(button_right)) {
    if (DEBUG) Serial.println("Tilt right");
    // Raise left tilter
    setLeftTilterPwm(tilter_maxpwm);
    b_isTilterOn = true;
    b_released = false;
    
    // Reset countdown timer
    recharge_ms = tilter_period_ms;
  }
  
  if (b_isTilterOn) {
    onTime_ms++;
  }

  // Set to hold state after onTime has elapsed
  if (onTime_ms > tilter_onTime_ms) {
   setLeftTilterPwm(tilter_holdpwm);
   b_isTilterOn = 0;
   onTime_ms = 0;
  }

  // if button is released, turn off
  if (!isButtonPressed(button_right)) {
    setLeftTilterPwm(0);
    b_released = true;
  }
  
}

void startGame(void) {
  b_isGameOn = true;
  score = 0;
  setDCMotorPwm(dcmotor_maxpwm);
  beepn(3, 2000, 70);
}

void stopGame(void) {
  b_isGameOn = false;
  DISPLAY_OFF;
  setDCMotorPwm(0);
  setLeftFlipperPwm(0);
  setRightFlipperPwm(0);
  setShooterPwm(0);
  setLeftTilterPwm(0);
  setRightTilterPwm(0);
  beep(2000, 400);
}

void increaseScore(uint32_t num) {
  flashB();
  beep(2000, 70);
  
  score += num;
  if (score < 0) {
    score = 0;
  }
  else if (score > 9999) {
    score = 9999;
  }
}

boolean isRoundLost(){
  static int32_t lastTime_ms = millis();
  bool roundLost = false;

  if (millis() - lastTime_ms > roundLostInterval_ms) {
    if (receiver2_val < receiver2_threshold){
      roundLost = true;
      lastTime_ms = millis();
    }
  }
  return roundLost;
}

void resetGame(){
  static uint32_t lastResetTime_ms = millis();
  if (millis() - lastResetTime_ms > resetGameInterval_ms) {
    score = 0;
    lastResetTime_ms = millis();
  }
}

void rampScore(){
  static uint32_t lastScoreTime_ms = millis();

  //if ramp connect is high then increment the point
  if(CP1 == HIGH && millis() - lastScoreTime_ms > rampScoreInterval_ms){
    increaseScore(4);
    beep(3000, 100);
    lastScoreTime_ms = millis();
    if(DEBUG){
      Serial.println("ramp connect");
    }
  }
}

void castleScore(){
  /*
    static uint32_t lastScoreTime_ms = millis();
  
  //if castle  is high then increment the point
  if(CP2 == HIGH && millis() - lastScoreTime_ms > castleScoreInterval_ms){
    increaseScore(10);
    beep(2000, 100);
    lastScoreTime_ms = millis();
  }
  */
  pCastleReader = analogRead(pCastle);
  static uint32_t lastScoreTime_ms = millis();

  if( pCastleReader > castleThresh && millis() - lastScoreTime_ms > piezoElementScoreInterval_ms){
    increaseScore(10);
    beep(3000,100);
    lastScoreTime_ms = millis();
    if(DEBUG){
      Serial.println("castle hit");
      Serial.println(pCastleReader);
    }
  }
}

void pElementScore(){
  pElementReader = analogRead(pElem);
  static uint32_t lastScoreTime_ms = millis();

  if( pElementReader > threshold && millis() - lastScoreTime_ms > piezoElementScoreInterval_ms){
    increaseScore(1);
    beep(2000,100);
    lastScoreTime_ms = millis();
    if(DEBUG){
      Serial.println("hit");
      Serial.println(pElementReader);
    }
  }
  
}

void fadeR(uint32_t pwm) {
  static uint32_t lastUpdateTime_ms = millis();

  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmR) {
    pwm = maxLedPwmR;
  }
  
  if (millis() - lastUpdateTime_ms > 20) {
    if (ledPwmR < pwm) {
      ledPwmR++;
    }
    else if (ledPwmR > pwm) {
      ledPwmR--;
    }
    setLedPwmR(ledPwmR);
    lastUpdateTime_ms = millis();
  }
  
}

void fadeG(uint32_t pwm) {
  static uint32_t lastUpdateTime_ms = millis();

  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmG) {
    pwm = maxLedPwmG;
  }
  
  if (millis() - lastUpdateTime_ms > 20) {
    if (ledPwmG < pwm) {
      ledPwmG++;
    }
    else if (ledPwmG > pwm) {
      ledPwmG--;
    }
    setLedPwmG(ledPwmG);
    lastUpdateTime_ms = millis();
  }
  
}

void fadeB(uint32_t pwm) {
  static uint32_t lastUpdateTime_ms = millis();

  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmB) {
    pwm = maxLedPwmB;
  }
  
  if (millis() - lastUpdateTime_ms > 20) {
    if (ledPwmB < pwm) {
      ledPwmB++;
    }
    else if (ledPwmB > pwm) {
      ledPwmB--;
    }
    setLedPwmB(ledPwmB);
    lastUpdateTime_ms = millis();
  }
  
}

void flash(uint8_t r, uint8_t g, uint32_t b) {
  setLedPwmR(r);
  setLedPwmG(g);
  setLedPwmB(b);
}

void flashR(void) {
  setLedPwmR(maxLedPwmR);
}

void flashG(void) {
  setLedPwmG(maxLedPwmG);
}

void flashB(void) {
  setLedPwmB(maxLedPwmB);
}

void setLedPwmR(uint32_t pwm){
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmR) {
    pwm = maxLedPwmR;
  }
  ledPwmR = pwm;
  analogWrite(pin_ledR, map(pwm, 0, 100, 0, 255));
}

void setLedPwmG(uint32_t pwm){
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmG) {
    pwm = maxLedPwmG;
  }
  ledPwmG = pwm;
  analogWrite(pin_ledG, map(pwm, 0, 100, 0, 255));
}

void setLedPwmB(uint32_t pwm){
  if (pwm < 0) {
    pwm = 0;
  }
  else if (pwm > maxLedPwmB) {
    pwm = maxLedPwmB;
  }
  ledPwmB = pwm;
  analogWrite(pin_ledB, map(pwm, 0, 100, 0, 255));
}

void movingDoor(){
  static uint32_t lastUpdateTime_ms = millis();
  static boolean movingRight = true;
  static uint32_t servoPos = servoMidAngle;

  if(millis() - lastUpdateTime_ms > servoInterval_ms){
    
    if( movingRight && (servoPos < servoMidAngle + servoMaxAngle) ){
      servoPos++;
      servo.write(servoPos);    
    }
    else if(movingRight){
      movingRight = false;
    }
    else if(!movingRight && (servoPos > servoMidAngle - servoMaxAngle)){
      servoPos--;
      servo.write(servoPos);
    }
    else if(!movingRight){
      movingRight = true;
    }
    
    lastUpdateTime_ms = millis();
    
  }
  
}



