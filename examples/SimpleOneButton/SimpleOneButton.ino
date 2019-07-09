/*
 This is a sample sketch to show how to use the ButtonKingLibrary
 to detect double-click events on a button.

 Setup a test circuit:
 * Connect a pushbutton to pin A1 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output attach a led and resistor to ground
   or see the built-in led on the standard arduino board.

 The Sketch shows how to setup the library and bind a special function to the doubleclick event.
 In the loop function the button.tick function has to be called as often as you like.
*/

#include "ButtonKing.h"

// Setup a new OneButton on pin A1.
ButtonKing button(A1, true);


// setup code here, to run once:
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  // link the doubleclick function to be called on a doubleclick event.
  button.setDoubleClick(doubleclick);
} // setup


// main code here, to run repeatedly:
void loop() {
  // keep watching the push button:
  button.isClick();

  // You can implement other code in here or just wait a while
  delay(10);
} // loop


// this function will be called when the button was pressed 2 times in a short timeframe.
void doubleclick() {
  static int m = LOW;
  // reverse the LED
  m = !m;
  digitalWrite(13, m);
} // doubleclick

// End
