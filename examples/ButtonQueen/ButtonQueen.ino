/*
 ButtonQueen.ino
 This is a sketch to show how to use the ButtonKing Library
 to detect click events on 2 buttons in parallel.
 Copyright (c) by Tanyanat Pichitwong
 Setup a test circuit:
 * Connect a pushbutton to pin 8 (ButtonPin) and ground.
 * Connect a pushbutton to pin 9 (ButtonPin) and ground.
 * The Serial interface is used for output the detected button events.
*/

/* Sample output:
Starting TwoButtons...
Button 1 click.
Button 2 click.
Button 1 doubleclick.
Button 2 doubleclick.
Button 1 tripleclick.
Button 2 tripleclick.
Button 1 press.
Button 2 press.
Button 1 doublepress.
Button 2 doublepress.
Button 1 triplepress.
Button 2 triplepress.
Button 1 release.
Button 2 release.
*/

#include "ButtonKing.h"

// Setup a new ButtonKing on pin 8.
ButtonKing button1(8, true);
// Setup a new ButtonKing on pin 9.
ButtonKing button2(9, true);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting ButtonQueen...");

  // link the button 1 functions.
  button1.setClick(click1);
  button1.setDoubleClick(doubleclick1);
  button1.setTripleClick(tripleclick1);
  button1.setPress(press1);
  button1.setRelease(release1);
  button1.setDoublePress(doublepress1);
  button1.setTriplePress(triplepress1);

  // link the button 2 functions.
  button2.setClick(click2);
  button2.setDoubleClick(doubleclick2);
  button2.setTripleClick(tripleclick2);
  button2.setPress(press2);
  button2.setRelease(release2);
  button2.setDoublePress(doublepress2);
  button2.setTriplePress(triplepress2);

} // setup


// main code here, run repeatedly:

void loop() {
  // keep watching the push buttons:
  button1.isClick();
  button2.isClick();
  
  delay(10);
} // loop

// ----- button 1 callback functions

// This function will be called when the button1 was clicked.
void click1() {
  Serial.println("Button 1 click.");
} // click1

// This function will be called when the button1 was double-clicked.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1

// This function will be called when the button1 was triple-clicked.
void tripleclick1() {
  Serial.println("Button 1 tripleclick.");
} // tripleclick1

// This function will be called when the button1 was pressed.
void press1() {
  Serial.println("Button 1 press.");
} // press1

// This function will be called when the button1 was released..
void release1() {
  Serial.println("Button 1 release.");
  Serial.println( button1.getPressedTimer() );
} // release1

// This function will be called when the button1 was double-pressed.
void doublepress1() {
  Serial.println("Button 1 doublePRESS.");
} // doublepress1

// This function will be called when the button1 was triple-pressed.
void triplepress1() {
  Serial.println("Button 1 triplePRESS.");
} // triplepress1

// ----- button 2 callback functions

// This function will be called when the button2 was clicked.
void click2() {
  Serial.println("Button 2 click.");
} // click2

// This function will be called when the button2 was double-clicked.
void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2

// This function will be called when the button2 was triple-clicked.
void tripleclick2() {
  Serial.println("Button 2 tripleclick.");
} // tripleclick2

// This function will be called when the button2 was pressed.
void press2() {
  Serial.println("Button 2 press.");
} // press2

// This function will be called when the button2 was released..
void release2() {
  Serial.println("Button 2 release.");
  Serial.println( button2.getPressedTimer() );
} // release2

// This function will be called when the button2 was double-pressed.
void doublepress2() {
  Serial.println("Button 2 doublePRESS.");
} // doublepress2

// This function will be called when the button2 was triple-pressed.
void triplepress2() {
  Serial.println("Button 2 triplePRESS.");
} // triplepress2


// End
