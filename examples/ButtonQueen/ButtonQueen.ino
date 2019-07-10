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
Button 1 ShortPress start
Button 1 LongPress  start
Button 1 longPress...
Button 1 longPress...
Button 1 longPress...
Button 1 longPress stop
Button 2 ShortPress start
Button 2 longPress start
Button 2 longPress...
Button 2 longPress...
Button 2 longPress stop
Button 1 DoubleShortPress start
Button 1 DoubleLongPress  start
Button 1 DoubleLongPress...
Button 1 DoubleLongPress...
Button 1 DoubleLongPress...
Button 1 DoubleLongPress  stop
Button 2 DoubleShortPress start
Button 2 DoubleLongPress start
Button 2 DoubleLongPress...
Button 2 DoubleLongPress...
Button 2 DoubleLongPress stop

*/

#include "ButtonKing.h"

// Setup a new ButtonKing on pin 8.
ButtonKing button1(8, true);
// Setup a new ButtonKing on pin 9.
ButtonKing button2(9, true);


// setup code here, run once:
void setup() {
 
  pinMode(8, INPUT);      // sets the digital pin as input
  pinMode(9, INPUT);      // sets the digital pin as input
 
  // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting ButtonQueen...");

  // link the button 1 functions.
  button1.setClick(click1);
  button1.setDoubleClick(doubleclick1);
  button1.setShortDoubleStart(shortDoublePressStart1);
  button1.setLongDoubleStart(longDoublePressStart1);
  button1.setLongDoubleStop(longDoublePressStop1);
  button1.setShortClickStart(shortPressStart1);
  button1.setLongClickStart(longPressStart1);
  button1.setLongClickStop(longPressStop1);

  // link the button 2 functions.
  button2.setClick(click2);
  button2.setDoubleClick(doubleclick2);
  button2.setShortDoubleStart(shortDoublePressStart2);
  button2.setLongDoubleStart(longDoublePressStart2);
  button2.setLongDoubleStop(longDoublePressStop2);
  button2.setShortClickStart(shortPressStart2);
  button2.setLongClickStart(longPressStart2);
  button2.setLongClickStop(longPressStop2);

} // setup


// main code here, run repeatedly:
void loop() {
  // keep watching the push buttons:
  button1.isClick();
  button2.isClick();

  delay(10);
} // loop


// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click.");
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is double pressed for a Short time.
void shortDoublePressStart1() {
  Serial.println("Button 1 double shortPress start");
} // DoubleShortPressStart1


// This function will be called once, when the button1 is double pressed for a long time.
void longDoublePressStart1() {
  Serial.println("Button 1 double longPress start");
} // DoublelongPressStart1


// This function will be called once, when the button1 is released after beeing double pressed for a long time.
void longDoublePressStop1() {
  Serial.println("Button 1 double longPress stop");
} // DoublelongPressStop1


// This function will be called once, when the button1 is pressed for a Short time.
void shortPressStart1() {
  Serial.println("Button 1 shortPress start");
} // ShortPressStart1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
} // longPressStop1


// ... and the same for button 2:

// This function will be called when the button2 was pressed 1 time (and no 2. button press followed).
void click2() {
  Serial.println("Button 2 click.");
} // click2


// This function will be called when the button2 was pressed 2 times in a short timeframe.
void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


// This function will be called once, when the button2 is double pressed for a Short time.
void shortDoublePressStart2() {
  Serial.println("Button 2 double shortPress start");
} // DoubleShortPressStart2


// This function will be called once, when the button2 is double pressed for a long time.
void longDoublePressStart2() {
  Serial.println("Button 2 double longPress start");
} // DoublelongPressStart2


// This function will be called once, when the button2 is released after beeing double pressed for a long time.
void longDoublePressStop2() {
  Serial.println("Button 2 double longPress stop");
} // DoublelongPressStop2


// This function will be called once, when the button2 is pressed for a Short time.
void shortPressStart2() {
  Serial.println("Button 2 shortPress start");
} // ShortPressStart2


// This function will be called once, when the button2 is pressed for a long time.
void longPressStart2() {
  Serial.println("Button 2 longPress start");
} // longPressStart2


// This function will be called once, when the button2 is released after beeing pressed for a long time.
void longPressStop2() {
  Serial.println("Button 2 longPress stop");
} // longPressStop2


// End
