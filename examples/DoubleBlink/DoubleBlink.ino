/*
 DoubleBlink.ino

 This is a sketch to show how to use the ButtonKing Library
 to detect double-click events on a single button.

 Copyright (c) by Tanyanat Pichitwong

 Setup a test circuit:
 * Connect a pushbutton to pin 8 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output
   - attach a led and resistor to ground
   - or see the built-in led.

 A click turns the led on.
 A doubleclick changes the blink rate from ON to SLOW to FAST.

 */

#include "ButtonKing.h"

// define the blink action.
typedef enum {
  LED_OFF,  // set LED "OFF".
  LED_ON,   // set LED "ON"
  LED_SLOW, // blink LED "SLOW"
  LED_FAST  // blink LED "FAST"
}
ledActions;

// Setup a new ButtonKing on pin A1.
ButtonKing button(8, true);

ledActions nextAction = LED_OFF; // no action when starting

// setup code here, run once.
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output
 
  pinMode(8, INPUT);      // sets the digital pin as input

  // link the toClick function to be called on a click event.
  button.setClick(toClick);

  // link the toDoubleClick function to be called on a doubleclick event.
  button.setDoubleClick(toDoubleClick);

  // set debouncing time to 80 msec. Default is 10 msec.
  button.setTimeDebounce(80);
} // setup


// main code here, run repeatedly:
void loop() {
  unsigned long now = millis();

  // keep watching the push button:
  button.isClick();


  if (nextAction == LED_OFF) {
    // do nothing.
    digitalWrite(13, LOW);

  } else if (nextAction == LED_ON) {
    // turn LED on
    digitalWrite(13, HIGH);

  } else if (nextAction == LED_SLOW) {
    // do a slow blinking
    if (now % 1000 < 500) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    } // if

  } else if (nextAction == LED_FAST) {
    // do a fast blinking
    if (now % 200 < 100) {
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
    } // if
  } // if
} // loop


// when the button was click, it will toggle led on/off.
void toClick() {
  if (nextAction == LED_OFF)
    nextAction = LED_ON;
  else
    nextAction = LED_OFF;
} // toClick Function


// when the button was double click, it will cycle through ON to SLOW to FAST led blinking rate.
void toDoubleClick() {
  if (nextAction == LED_ON) {
    nextAction = LED_SLOW;

  } else if (nextAction == LED_SLOW) {
    nextAction = LED_FAST;

  } else if (nextAction == LED_FAST) {
    nextAction = LED_ON;
  } // if
} // toDoubleClick Function

// End
