/*
 DoubleInterrupt.ino

 This is a sketch to show how to use the ButtonKing Library
 to detect double-click events on a single button by using interrupts.

Copyright (c) by Tanyanat Pichitwong

 Setup a test circuit:
 * Connect a pushbutton to pin A1 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output
   - attach a led and resistor to ground
   - or see the built-in led.

   A doubleclick toggles the led on/off through interrupt.

*/

#include "ButtonKing.h"

// Setup a new ButtonKing on pin A1.
ButtonKing button(A1, true);


// setup code here, run once:
void setup() {
  // enable the standard led on pin 13.
  pinMode(13, OUTPUT);      // sets the digital pin as output

  // link the toDoubleClick function to be called on a doubleclick event.
  button.setDoubleClick(toDoubleClick);

  PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT9);  // This enables the interrupt for pin 1 of Port C: This is A1.
} // setup


// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A1: exactly where we need to check.
ISR(PCINT1_vect) {
  // keep watching the push button:
  button.isClick(); // just call isClick() to check the state.
}


// main code here, run repeatedly:
void loop() {
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
