/**
 * @file ButtonKing.cpp
 *
 * @brief Library for detecting button clicks, doubleclicks and simple long
 * press and double Long press pattern on a single button.
 *
 * @author Tanyanat Pichitwong
 * @Copyright Copyright (c) by Tanyanat Pichitwong
 *
 * Changelog: see ButtonKing.h
 */

#include "ButtonKing.h"

// ----- Initialization and Default Values -----

/**
 * Construct a new ButtonKing object but not initialize the IO pin.
 */
ButtonKing::ButtonKing()
{
  _pin = -1;
}

ButtonKing::ButtonKing(int pin, int activeLow, bool pullupActive)
{
  // ButtonKing();
  _pin = pin;

  if (activeLow) {
    // the button connects the input pin to GND when pressed.
    _intButtonStage = LOW;

  } else {
    // the button connects the input pin to VCC when pressed.
    _intButtonStage = HIGH;
  } // if

  if (pullupActive) {
    // use the given pin as input and activate internal PULLUP resistor.
    pinMode(pin, INPUT_PULLUP);
  } else {
    // use the given pin as input
    pinMode(pin, INPUT);
  } // if
} // ButtonKing


// explicitly set the number of millisec that have to pass by before a click is
// assumed as safe.
void ButtonKing::setTimeDebounce(int ticks)
{
  _debounceTime = ticks;
} // setDebounceTime


// explicitly set the number of millisec that have to wait before counting the
// button-ticks was ended.
void ButtonKing::setTimeCount(int ticks)
{
  _waitTime = ticks;
} // setTimeCount


// save function for click event
void ButtonKing::setClick(callbackFunction newFunction)
{
  _setClick = newFunction;
} // attachClick

// save function for press event
void ButtonKing::setPress(callbackFunction newFunction)
{
  _setPress = newFunction;
} // attachPress

// save function for release event
void ButtonKing::setRelease(callbackFunction newFunction)
{
  _setRelease = newFunction;
} // attachRelease

// save function for doubleClick event
void ButtonKing::setDoubleClick(callbackFunction newFunction)
{
  _setDoubleClick = newFunction;
} // attachDoubleClick

// save function for doublePress event
void ButtonKing::setDoublePress(callbackFunction newFunction)
{
  _setDoublePress = newFunction;
} // attachDoublePress

// save function for tripleClick event
void ButtonKing::setTripleClick(callbackFunction newFunction)
{
  _setTripleClick = newFunction;
} // attachTripleClick

// save function for triplePress event
void ButtonKing::setTriplePress(callbackFunction newFunction)
{
  _setTriplePress = newFunction;
} // attachTriplePress

int ButtonKing::getPressedTimer(){
  return _stopPressedTimer - _pressedTimer;
}

/**
 * Advance the finite state machine (FSM) using the given level.
 */
void ButtonKing::isClick(void)
{
  unsigned long now = millis(); // current (relative) time in msecs.

  if(_buttonCount != 0 || _buttonCount == 0 && _debounceState == 2){ // this is not the 1st times.
    if(millis() - _waitingTimer >= _waitTime){ // complete.
      if(digitalRead(_pin) == _intButtonStage){
        if (_buttonCount == 1) {
          // Click the button.
          if (_setClick)
            _setClick();
        } else if (_buttonCount == 2) {
            // DoubleClick the button.
            if (_setDoubleClick)
              _setDoubleClick();
        } else if (_buttonCount == 3) {
            // TripleClick the button.
            if (_setTripleClick)
              _setTripleClick();
        }
      } else {
          if (_buttonCount == 0) {
            // Pressing the button.
            if (_setPress)
              _setPress();
          } else if (_buttonCount == 1) {
            // DoublePressing the button.
            if (_setDoublePress)
              _setDoublePress();
          } else if (_buttonCount == 2) {
            // TriplePressing the button.
            if (_setTriplePress)
              _setTriplePress();
          }
          _pressedTimer = millis(); // remember the time that button started to pressed.
          _debounceState = 3;
      }
      // RESET //
      _buttonCount = 0;
      _debounceTimer = 0;
      _waitingTimer = 0;
    }
  }

  // Implementation of the state machine

  if (_debounceState == 0) { // waiting for pressing
    if(digitalRead(_pin) != _intButtonStage && !_buttonFlag){
      _debounceTimer = now;
      if(_buttonCount == 0){ // for the 1st time.
        _waitingTimer = now;
      }
      _buttonFlag = true;
      _debounceState = 1;
    }
  } else if (_debounceState == 1) { // wait for debounce timer.
      if(millis() - _debounceTimer >= _debounceTime){
        if(digitalRead(_pin) != _intButtonStage){
          _debounceState = 2;
        }
      }
  } else if (_debounceState == 2) { // wait for release the button.
      if(digitalRead(_pin) == _intButtonStage){
        _buttonCount++;
        _buttonFlag = false;
        _debounceState = 0;
      }
  } else if (_debounceState == 3) { //wait for released after time-out.
    if(digitalRead(_pin) == _intButtonStage ){
      _buttonFlag = false;
      _debounceState = 0;
      // Stop Pressing the button.
      if (_setRelease)
        _setRelease();
      _stopPressedTimer = millis();
    }
  }
} // ButtonKing

void ButtonKing::reset(void)
{
  _debounceState = 0;
  _buttonCount = 0;
  _buttonFlag = false;
  _waitingTimer = 0;
  _debounceTimer = 0;
  _pressedTimer = 0;
  _stopPressedTimer = 0;
}

// end.
