#define DIR 7
#define EN 9
#define STEP 8
#define BUTTON_PIN_2 12
#define BUTTON_PIN_1 13
#define BUTTON_PIN_3 11
#define BUTTON_PIN_4 10
#define POT A0
#include <GyverStepper2.h>
GStepper2<STEPPER2WIRE> stepper(3200, STEP, DIR, EN);
unsigned long pot;
bool first_button = 0;
bool second_button = 0;
bool third_button = 0;
bool fourth_button = 0;
int speed_pov = 0;
void setup() {
  Serial.begin(9600);
  pinMode(POT, INPUT);
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);
  pinMode(BUTTON_PIN_4, INPUT);
  stepper.setSpeed(0);
  stepper.setAcceleration(1000);
}
void loop() {
  stepper.tick();
  stepper.setSpeed(speed_pov);
  
  first_button = digitalRead(BUTTON_PIN_1);
  second_button = digitalRead(BUTTON_PIN_2);
  third_button = digitalRead(BUTTON_PIN_3);
  fourth_button = digitalRead(BUTTON_PIN_4);
  if (first_button == 0 && second_button == 0 && third_button == 0 && fourth_button == 0) {
    speed_pov = 0;
    stepper.disable();
  }
  if (first_button == 1 && second_button == 0 && third_button == 0 && fourth_button == 0) {
    stepper.enable();
    digitalWrite(DIR, HIGH);
    speed_pov = 900;
    
  }
  if (first_button == 0 && second_button == 1 && third_button == 0 && fourth_button == 0) {
    stepper.enable();
    digitalWrite(DIR, LOW);
    speed_pov = 900;
    
  }
  if (first_button == 0 && second_button == 0 && third_button == 1 && fourth_button == 0) {
    stepper.enable();
     pot = map(analogRead(POT), 0, 1023, 300, 900);
    digitalWrite(DIR, HIGH);
    speed_pov = int(pot);
  }
  if (first_button == 0 && second_button == 0 && third_button == 0 && fourth_button == 1) {
    stepper.enable();
     pot = map(analogRead(POT), 0, 1023, 300, 900);
    digitalWrite(DIR, LOW);
    speed_pov = int(pot);
  }
  static uint32_t tmr2;
  if (millis() - tmr2 > 20) {
    tmr2 = millis();
    Serial.println(speed_pov);
  }
}