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
    _intButtonStage = HIGH;

  } else {
    // the button connects the input pin to VCC when pressed.
    _intButtonStage = LOW;
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

/////////////////////////////////////////////////////////////////////////////

// save function for click event
void ButtonKing::setClick(callbackFunction newFunction)
{
  _ClickFunc = newFunction;
} // setClick

// save function for parameterized click event
void ButtonKing::setClick(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramClickFunc = newFunction;
  _ClickFuncParam = parameter;
} // setClick


// save function for press event
void ButtonKing::setPress(callbackFunction newFunction)
{
  _PressFunc = newFunction;
} // setPress

// save function for parameterized press event
void ButtonKing::setPress(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramPressFunc = newFunction;
  _PressFuncParam = parameter;
} // setPress


// save function for release event
void ButtonKing::setRelease(callbackFunction newFunction)
{
  _ReleaseFunc = newFunction;
} // setRelease

// save function for parameterized release event
void ButtonKing::setRelease(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramReleaseFunc = newFunction;
  _ReleaseFuncParam = parameter;
} // setRelease


// save function for doubleclick event
void ButtonKing::setDoubleClick(callbackFunction newFunction)
{
  _DoubleClickFunc = newFunction;
} // setDoubleClick

// save function for parameterized doubleclick event
void ButtonKing::setDoubleClick(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramDoubleClickFunc = newFunction;
  _DoubleClickFuncParam = parameter;
} // setDoubleClick


// save function for doublepress event
void ButtonKing::setDoublePress(callbackFunction newFunction)
{
  _DoublePressFunc = newFunction;
} // setDoublePress

// save function for parameterized doublepress event
void ButtonKing::setDoublePress(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramDoublePressFunc = newFunction;
  _DoublePressFuncParam = parameter;
} // setDoublePress


// save function for tripleclick event
void ButtonKing::setTripleClick(callbackFunction newFunction)
{
  _TripleClickFunc = newFunction;
} // setTripleClick

// save function for parameterized tripleclick event
void ButtonKing::setTripleClick(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramTripleClickFunc = newFunction;
  _TripleClickFuncParam = parameter;
} // setTripleClick


// save function for triplepress event
void ButtonKing::setTriplePress(callbackFunction newFunction)
{
  _TriplePressFunc = newFunction;
} // setTriplePress

// save function for parameterized triplepress event
void ButtonKing::setTriplePress(parameterizedCallbackFunction newFunction, void* parameter)
{
  _paramTriplePressFunc = newFunction;
  _TriplePressFuncParam = parameter;
} // setTriplePress

int ButtonKing::getPressedTimer(){
  return _stopPressedTimer - _pressedTimer;
}

/**
 * @brief Check input of the configured pin and then advance the finite state
 * machine (FSM).
 */
void ButtonKing::isClick(void)
{
  if (_pin >= 0) {
    isClick(digitalRead(_pin) != _intButtonStage);
  }
}

/**
 * Advance the finite state machine (FSM) using the given level.
 */
void ButtonKing::isClick(bool activeLevel)
{
  unsigned long now = millis(); // current (relative) time in msecs.

  if((_buttonCount != 0) || (_buttonCount == 0 && _debounceState == 2)){ // this is not the 1st times.
    if(now - _waitingTimer >= _waitTime){ // complete.
      if(!activeLevel){
        if (_buttonCount == 1) {
          // Click the button.
          if (_ClickFunc)
            _ClickFunc();
          if (_paramClickFunc)
            _paramClickFunc(_ClickFuncParam);
        } else if (_buttonCount == 2) {
            // DoubleClick the button.
            if (_DoubleClickFunc)
              _DoubleClickFunc();
            if (_paramDoubleClickFunc)
              _paramDoubleClickFunc(_DoubleClickFuncParam);
        } else if (_buttonCount == 3) {
            // TripleClick the button.
            if (_TripleClickFunc)
              _TripleClickFunc();
            if (_paramTripleClickFunc)
              _paramTripleClickFunc(_TripleClickFuncParam);
        }
      } else {
          if (_buttonCount == 0) {
            // Pressing the button.
            if (_PressFunc)
              _PressFunc();
            if (_paramPressFunc)
              _paramPressFunc(_PressFuncParam);
          } else if (_buttonCount == 1) {
            // DoublePressing the button.
            if (_DoublePressFunc)
              _DoublePressFunc();
            if (_paramDoublePressFunc)
              _paramDoublePressFunc(_DoublePressFuncParam);
          } else if (_buttonCount == 2) {
            // TriplePressing the button.
            if (_TriplePressFunc)
              _TriplePressFunc();
            if (_paramTriplePressFunc)
              _paramTriplePressFunc(_TriplePressFuncParam);
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
    if(activeLevel && !_buttonFlag){
      _debounceTimer = now;
      if(_buttonCount == 0){ // for the 1st time.
        _waitingTimer = now;
      }
      _buttonFlag = true;
      _debounceState = 1;
    }
  } else if (_debounceState == 1) { // wait for debounce timer.
      if(now - _debounceTimer >= _debounceTime){
        if(activeLevel){
          _debounceState = 2;
        }
      }
  } else if (_debounceState == 2) { // wait for release the button.
      if(!activeLevel){
        _buttonCount++;
        _buttonFlag = false;
        _debounceState = 0;
      }
  } else if (_debounceState == 3) { //wait for released after time-out.
    if(!activeLevel){
      _buttonFlag = false;
      _debounceState = 0;
      // Stop Pressing the button.
      if (_ReleaseFunc)
        _ReleaseFunc();
      if (_paramReleaseFunc)
        _paramReleaseFunc(_ReleaseFuncParam);
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
