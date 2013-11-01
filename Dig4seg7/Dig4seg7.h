/*
  Dig4seg7.cpp - Library for displaying digits on 4 digit 7 segment displays.
  Created by Alexey V. Chuvashov, October 31, 2013.
  Released into the public domain.
*/

#ifndef Dig4seg7_h
#define Dig4seg7_h

#include "Arduino.h"

class Dig4seg7
{
  public:
    Dig4seg7(int digitsPins[], int segmentsPins[]);
    void displayNumber(int number);
    void lightNumber(byte numberToDisplay);
  private:
    int* _segmentsPins;
    int* _digitsPins;
};

#endif

