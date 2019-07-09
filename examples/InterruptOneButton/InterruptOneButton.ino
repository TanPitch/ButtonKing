/*
 InterruptOneButton.ino - Example for the ButtonKingLibrary library.
 This is a sample sketch to show how to use the ButtonKingLibrary
 to detect double-click events on a button by using interrupts.

 Setup a test circuit:
 * Connect a pushbutton to pin A1 (ButtonPin) and ground.
 * The pin 13 (StatusPin) is used for output attach a led and resistor to ground
   or see the built-in led on the standard arduino board.

 The Sketch shows how to setup the library and bind a special function to the doubleclick event.
 By using interrupts the doubleclick function will be called not from the main program.
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

  // You may have to modify the next 2 lines if using another pin than A1
  PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT9);  // This enables the interrupt for pin 1 of Port C: This is A1.
} // setup


// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A1: exactly where we need to check.
ISR(PCINT1_vect) {
  // keep watching the push button:
  button.tick(); // just call tick() to check the state.
}


// main code here, to run repeatedly:
void loop() {
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
