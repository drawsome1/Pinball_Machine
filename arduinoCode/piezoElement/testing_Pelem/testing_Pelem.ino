int led = 13;
int pElem = A0;
int threshold = 1021;

int sensorReading = 0;
int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pelement();
}

void pelement(){
  sensorReading = analogRead(pElem);
  static uint32_t lastScoreTime_ms = millis();
  
  if(sensorReading > threshold && millis()- lastScoreTime_ms > 500){
    ledState = !ledState;

    digitalWrite(led, ledState);

    Serial.println("Knock");
    lastScoreTime_ms = millis();
  }
}


