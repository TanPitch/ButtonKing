/**
 * @file ButtonKing.cpp
 *
 * @brief Library for detecting button clicks, doubleclicks and simple long
 * press  and double Long press pattern on a single button.
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
  // further initialization has moved to OneButton.h
}

ButtonKing::ButtonKing(int pin, int activeLow, bool pullupActive)
{
  // ButtonKing();
  _pin = pin;

  if (activeLow) {
    // the button connects the input pin to GND when pressed.
    _buttonPressed = LOW;

  } else {
    // the button connects the input pin to VCC when pressed.
    _buttonPressed = HIGH;
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


// explicitly set the number of millisec that have to pass by before a short
// button press is detected.
void ButtonKing::setTimeShort(int ticks)
{
  _shortTime = ticks;
} // setShortPressTime


// explicitly set the number of millisec that have to pass by before a long
// button press is detected.
void ButtonKing::setTimeLong(int ticks)
{
  _longTime = ticks;
} // setLongPressTime


// explicitly set the number of millisec that have to pass by before a double
// click is assumed.
void ButtonKing::setTimeDouble(int ticks)
{
  _DoubleTime = ticks;
} // setDoubleTime


// save function for click event
void ButtonKing::setClick(callbackFunction newFunction)
{
  _setClick = newFunction;
} // attachClick

// save function for doubleClick event
void ButtonKing::setDoubleClick(callbackFunction newFunction)
{
  _setDoubleClick = newFunction;
} // attachDoubleClick

// save function for SingleShortPressStart event
void ButtonKing::setShortClickStart(callbackFunction newFunction)
{
  _setShortClickStart = newFunction;
} // attachSingleShortPressStart

// save function for SingleLongPressStart event
void ButtonKing::setLongClickStart(callbackFunction newFunction)
{
  _setLongClickStart = newFunction;
} // attachSingleLongPressStart

// save function for longPressStop event
void ButtonKing::setLongClickStop(callbackFunction newFunction)
{
  _setLongClickStop = newFunction;
} // attachLongPressStop

// save function for DoubleShortPressStart event
void ButtonKing::setShortDoubleStart(callbackFunction newFunction)
{
  _setShortDoubleStart = newFunction;
} // attachDoubleShortPressStart

// save function for DoubleLongPressStart event
void ButtonKing::setLongDoubleStart(callbackFunction newFunction)
{
  _setLongDoubleStart = newFunction;
} // attachDoubleLongPressStart

// save function for Double longPressStop event
void ButtonKing::setLongDoubleStop(callbackFunction newFunction)
{
  _setLongDoubleStop = newFunction;
} // attachDoubleLongPressStop


void ButtonKing::reset(void){
  _state = 0; // restart.
  _Timer01 = 0;
  _Timer02 = 0;
}


/**
 * Check input of the configured pin.
 */
void ButtonKing::isClick(void)
{
  if (_pin >= 0) {
    isClick(digitalRead(_pin) == _buttonPressed);
  }
}


/**
 * Advance the finite state machine (FSM) using the given level.
 */
void ButtonKing::isClick(bool activeLevel)
{
  unsigned long now = millis(); // current (relative) time in msecs.

  // Implementation of the state machine

  if (_state == 0) { // waiting for menu pin being pressed.
    if (activeLevel) {
      _state = 1; // step to state 1
      _Timer01 = now; // remember starting time
    } // if
  } else if (_state == 1) { // Waitting for debounce
      if(millis() - _Timer01 >= _debounceTime){
        if(activeLevel) {
          _state = 2; // step to state 2
          _Timer01 = now; // remember starting time
        } // if
        else if(!activeLevel) {
          _state = 0; // return
        } // if
      } // if
  } else if (_state == 2) { // Waitting for long pressed
      if(millis() - _Timer01 >= _shortTime) {
        if(!activeLevel) {
          _state = 4; // step to state 4
          _Timer01 = now; // remember starting time
        } else {
            // Start Single Short Press
            if (_setShortClickStart)
              _setShortClickStart();
            _state = 3; // step to state 3
            _Timer01 = now; // remember starting time
          } // if
      } // if
      else{
        if(!activeLevel) {
          _state = 4; // step to state 4
          _Timer01 = now; // remember starting time
        } // if
      }
  } else if (_state == 3) { // Waitting for long pressed stop
      if(millis() - _Timer01 >= _longTime) {
        if(activeLevel) {
          // Start Single Long Press
          if (_setLongClickStart)
            _setLongClickStart();
        } // if
      }
      if(!activeLevel) {
        // Stop Single Long Press
        if (_setLongClickStop)
          _setLongClickStop();
        _state = 0; //return
      } // if
  } else if (_state == 4) { // waiting for Double press
      if(millis() - _Timer01 <= _DoubleTime ) {
            if(activeLevel) {
              _state = 5; // step to state 5
              _Timer02 = now; // remember starting time
            } // if
          } // if
          else {
            // Single Press
            if (_setClick)
              _setClick();
            _state = 0; // return
          } // if
  } else if (_state == 5) { // waiting for 2nd debounce
      if(millis() - _Timer02 >= _debounceTime) {
            if(activeLevel) {
              _state = 6; // step to state 6
              _Timer01 = now; // remember starting time
            } // if
            else if(!activeLevel) {
              _state = 0; // return
            } // if
          } // if
  } else if (_state == 6) { // waiting for 2nd Long pressed
      if(millis() - _Timer01 >= _shortTime) {
            if(!activeLevel) {
              // Double Press
              if (_setDoubleClick)
                _setDoubleClick();
              _state = 0; // return
            } // if
            else {
              // Start Double Short Press
              if (_setShortDoubleStart)
                _setShortDoubleStart();
              _Timer01 = now; // remember starting time
              _state = 7; // step to state 7
            } // if
          } // if
          else {
            if(!activeLevel) {
              // Double Press
              if (_setDoubleClick)
                _setDoubleClick();
              _state = 0; // return
            } // if
          } // if
  } else if (_state == 7) { // waiting for 2nd Long Pressed stop
      if( millis() - _Timer01 >= _longTime ) {
            if(activeLevel) {
              // Start Double Long Press
              if (_setLongDoubleStart)
                _setLongDoubleStart();
            } // if
          }
          if(!activeLevel) {
            // Stop Double Short Press
            if (_setLongDoubleStop)
              _setLongDoubleStop();
            _state = 0; // return
          } // if
  }
} // ButtonKing.isClick()


// end.
