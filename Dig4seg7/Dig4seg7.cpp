/*
  Dig4seg7.cpp - Library for displaying digits on 4 digit 7 segment displays.
  Created by Alexey V. Chuvashov, October 31, 2013.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Dig4seg7.h"

//                                 0        1        2        3        4        5
const byte _digitsPattern[] = {B1111110,B0110000,B1101101,B1111001,B0110011,B1011011,
//                                 6        7        8        9      empty
                               B1011111,B1110000,B1111111,B1111011,B0000000};

Dig4seg7::Dig4seg7(int digitsPins[], int segmentsPins[])
{
  for (int i = 0; i < 4; ++i){
    pinMode(digitsPins[i], OUTPUT);  
  }
  for (int i = 0; i < 7; ++i){
    pinMode(segmentsPins[i], OUTPUT);  
  }
  _digitsPins = digitsPins;
  _segmentsPins = segmentsPins;
}

void Dig4seg7::displayNumber(int number) {

  #define DISPLAY_BRIGHTNESS 300 // 50 - 5000

  #define DIGIT_ON  LOW
  #define DIGIT_OFF HIGH

  long beginTime = millis();

  for(int digit = 3 ; digit >= 0 ; digit--) {
    //Turn on a digit for a short amount of time
    digitalWrite(_digitsPins[digit], DIGIT_ON);

    //Turn on the right segments for this digit
    lightNumber(number % 10);
    number /= 10;

    //Display this digit for a fraction of a second (between 1us and 5000us, 500 is pretty good)
    delayMicroseconds(DISPLAY_BRIGHTNESS); 

    //Turn off all segments
    lightNumber(10); 
    
    //Turn off all _digitsPattern
    for (int i = 0; i < 4; ++i){
      digitalWrite(_digitsPins[i], DIGIT_OFF);
    }
  }

  //Wait for 20ms to pass before we paint the display again
  while( (millis() - beginTime) < 10) ; 
}

void Dig4seg7::lightNumber(byte numberToDisplay) {
  byte b = _digitsPattern[numberToDisplay];
  for (int i = 0; i < 7; i++)
    digitalWrite(_segmentsPins[i], bitRead(b, 6-i));

}