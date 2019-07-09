/*
 BlinkMachine.ino

 This is a sample sketch to show how to use the ButtonKingLibrary to detect double-click events on a button.

 Copyright (c) by Tanyanat Pichitwong

 Setup a test circuit:
 * Connect a pushbutton to pin A1 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output attach a led and resistor to ground
 or see the built-in led on the standard arduino board.

 The Sketch shows how to setup the library and bind a "machine" that can blink the LED slow or fast.
 A click on the button turns the led on.
 A doubleclick on the button changes the blink rate from ON to SLOW to FAST and back.
 In the loop function the button.tick function has to be called as often as you like.

 */

#include "ButtonKing.h"

// The actions I ca do...
typedef enum {
  ACTION_OFF,  // set LED "OFF".
  ACTION_ON,   // set LED "ON"
  ACTION_SLOW, // blink LED "SLOW"
  ACTION_FAST  // blink LED "FAST"
}
MyActions;

// Setup a new OneButton on pin A1.
ButtonKing button(A1, true);

MyActions nextAction = ACTION_OFF; // no action when starting


// setup code here, to run once.
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  // link the myClickFunction function to be called on a click event.
  button.setClick(myClickFunction);

  // link the doubleclick function to be called on a doubleclick event.
  button.setDoubleClick(myDoubleClickFunction);

  // set 80 msec. debouncing time. Default is 50 msec.
  button.setTimeDebounce(80);
} // setup


// main code here, to run repeatedly:
void loop() {
  unsigned long now = millis();

  // keep watching the push button:
  button.isClick();

  // You can implement other code in here or just wait a while

  if (nextAction == ACTION_OFF) {
    // do nothing.
    digitalWrite(13, LOW);

  } else if (nextAction == ACTION_ON) {
    // turn LED on
    digitalWrite(13, HIGH);

  } else if (nextAction == ACTION_SLOW) {
    // do a slow blinking
    if (now % 1000 < 500) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    } // if

  } else if (nextAction == ACTION_FAST) {
    // do a fast blinking
    if (now % 200 < 100) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    } // if
  } // if
} // loop


// this function will be called when the button was pressed 1 time and them some time has passed.
void myClickFunction() {
  if (nextAction == ACTION_OFF)
    nextAction = ACTION_ON;
  else
    nextAction = ACTION_OFF;
} // myClickFunction


// this function will be called when the button was pressed 2 times in a short timeframe.
void myDoubleClickFunction() {
  if (nextAction == ACTION_ON) {
    nextAction = ACTION_SLOW;

  } else if (nextAction == ACTION_SLOW) {
    nextAction = ACTION_FAST;

  } else if (nextAction == ACTION_FAST) {
    nextAction = ACTION_ON;
  } // if
} // myDoubleClickFunction

// End
