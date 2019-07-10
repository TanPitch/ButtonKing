/*
 SimpleButtonKing.ino

 This is a sketch to show how to use the ButtonKing Library
 to detect double-click events on a single button.

 Copyright (c) by Tanyanat Pichitwong

 Setup a test circuit:
 * Connect a pushbutton to pin 8 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output
   - attach a led and resistor to ground
   - or see the built-in led.

 A doubleclick toggles the led on/off.
*/

#include "ButtonKing.h"

// Setup a new ButtonKing on pin 8.
ButtonKing button(8, true);


// setup code here, run once:
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output
  pinMode( 8, INPUT);       // sets the digital pin as input

  // link the toDoubleClick function to be called on a doubleclick event.
  button.setDoubleClick(toDoubleClick);
} // setup


// main code here, run repeatedly:
void loop() {
  // keep watching the push button:
  button.isClick();

  delay(10);
} // loop


// this function will be called when the button was doubleoressed.
void toDoubleClick() {
  static int k = LOW;
  // reverse the LED
  k = !k;
  digitalWrite(13, k);
} // toDoubleClick

// End
