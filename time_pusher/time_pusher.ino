#include <Servo.h>
#include <Dig4seg7.h>

Servo pusherServo; //Servo instance 
int digitsPins[] = {11,10,9,6}; //<- PWM avr pin. display pin -> 12,9,8,6 
int segmentsPins[] = {2,3,4,5,34,7,8}; //<- avr digital pin. display pin -> 11,7,4,2,1,10,5 
Dig4seg7 myDisplay(digitsPins, segmentsPins);

int ledPin = 13; // led pin 
int buttonPin = 30; //button pin
int ptrPin = A0; //porentiometer analog pin
int servoPin = 32;

int startAngle = 15; //start searvo angle
int endAngle = 35;   
int currentDelay = 0; 
long startTime = 0;

#define BUTTON_UP LOW
#define BUTTON_DOWN HIGH

void setup() {                
  pusherServo.attach(servoPin);
  pusherServo.write(startAngle);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonStatus = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonStatus); 
  if (buttonStatus == BUTTON_DOWN && startTime == 0) {
    pusherServo.write(endAngle);
    startTime = millis();
  }
  
  int numberForDisplayng = 0;
  if (buttonStatus == BUTTON_UP && startTime == 0) {
    currentDelay = map(analogRead(ptrPin), 0, 1023, 0, 9999);
    numberForDisplayng = currentDelay;
  }
  else {
    if (millis() - startTime > currentDelay) {
      startTime = 0;
      pusherServo.write(startAngle);
    }
    numberForDisplayng = millis() - startTime;
//    numberForDisplayng = currentDelay + startTime - millis();
  }
  myDisplay.displayNumber(numberForDisplayng);
}




