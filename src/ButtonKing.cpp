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


// set the mode that tell program to detect triple click or not.
void ButtonKing::setTripleMode(bool turns)
{
  _tripleMode = turns;
} // setTripleMode


// set the mode that tell program to detect triple click or not.
void ButtonKing::setClickMode(bool turns)
{
  _countMode = turns;
} // setClickMode


// explicitly set the number of millisec that count click run before timeout
void ButtonKing::setCountClickTimeout(int ticks)
{
  _countTimer = ticks;
} // setCountClickTimeout


// explicitly set the times that count clicks have to done
void ButtonKing::setCountClickTo(int ticks)
{
  _countTo = ticks;
} // setCountClickTo


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

// save function for tripleClick event
void ButtonKing::setTripleClick(callbackFunction newFunction)
{
  _setTripleClick = newFunction;
} // attachTripleClick

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

// save function for TripleShortPressStart event
void ButtonKing::setShortTripleStart(callbackFunction newFunction)
{
  _setShortTripleStart = newFunction;
} // attachTripleShortPressStart

// save function for TripleLongPressStart event
void ButtonKing::setLongTripleStart(callbackFunction newFunction)
{
  _setLongTripleStart = newFunction;
} // attachTripleLongPressStart

// save function for TriplelongPressStop event
void ButtonKing::setLongTripleStop(callbackFunction newFunction)
{
  _setLongTripleStop = newFunction;
} // attachTripleLongPressStop

// save function for CountClickComplete event
void ButtonKing::setCountClickComplete(callbackFunction newFunction)
{
  _setCountClickComplete = newFunction;
} // attachCountClickComplete

// save function for CountClickTimeout event
void ButtonKing::setCountClickTimeout(callbackFunction newFunction)
{
  _setCountClickTimeout = newFunction;
} // attachCountClickTimeout

// function to get the duration of the long press
int ButtonKing::setPressedDuration(){
  return _StopTimer - _StartTimer;
}


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
      if(millis() - _Timer01 >= _debounceTime) {
        if(_countMode == false) {
          _Timer01 = now; // remember starting time
          _state = 2; // step to state 2
        } // if
        else {
          if( _countClick == 0) {
            _Timer02 = now; // remember starting time
          } // if
          _state = 12;  // step to state 12
        }
      }
      else if(!activeLevel) {
        _state = 0; // return
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
              _StartTimer = now;
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
          _StopTimer = now;
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
              if(_tripleMode == false) {
                // Double Press
                if (_setDoubleClick)
                  _setDoubleClick();
                _state = 0; // return
              }
              else {
                _Timer01 = now; // remember starting time
                _state = 8; // step to state 8
              }
            } // if
            else {
              // Start Double Short Press
              if (_setShortDoubleStart)
                _setShortDoubleStart();
                _StartTimer = now;
              _Timer01 = now; // remember starting time
              _state = 7; // step to state 7
            }
          }
      else {
        if(!activeLevel && _tripleMode == false) {
          // Double Press
          if (_setDoubleClick)
          _setDoubleClick();
          _state = 0; // return
        }
        else if(!activeLevel && _tripleMode == true) {
          _Timer01 = now; // remember starting time
          _state = 8; // step to state 8
        }
      }
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
              _StopTimer = now;
            _state = 0; // return
          } // if
  } else if (_state == 8) { // waiting for Triple Press
    if(millis() - _Timer01 <= _DoubleTime ) {
      if( digitalRead(Button_Pin) == LOW ) {
        _Timer02 = now; // remember starting time
        _state = 9; // step to state 9
      } // if
    } // if
    else {
      // Double Press
      if (_setDoubleClick)
        _setDoubleClick();
      _state = 0; // return
    } // if
  } else if (_state == 9) { // waiting for 3rd debounce_time
    if(millis() - _Timer02 >= _debounceTime) {
      if(activeLevel) {
        _Timer01 = now; // remember starting time
        _state = 10; // step to state 10
      }
      else if(!activeLevel) {
        _stage = 0; // return
      } // if
    } // if
  } else if (_state == 10) { // waiting for 3rd Long pressed
    if(millis() - _Timer01 >= _shortTime) {
      if(!activeLevel) {
        // Triple Click
        if (_setTripleClick)
          _setTripleClick();
        _stage = 0; // return
      }
      else {
        // Start Triple Short Press
        if (_setShortTripleStart)
          _setShortTripleStart();
        _Timer01 = now; // remember starting time
        _state = 10; // step to state 10
      } //3rd Long Press
    }
    else {
      if(!activeLevel) {
        // Triple Click
        if (_setTripleClick)
          _setTripleClick();
        _stage = 0; // return
      }
    }
  } else if (_state == 11) { // waiting for 3rd Long pressed stop
    if( millis() - _Timer01 >= _longTime ) {
      if(activeLevel) {
        // Start Triple Long Press
        if (_setLongTripleStart)
          _setLongTripleStart();
      } // if
    } // if
    if(!activeLevel) {
      // Stop Triple Long Press
      if (_setLongTripleStop)
        _setLongTripleStop();
      _stage = 0; // return
    } // if
  } else if (_state == 12) { // waiting for full release in count mode
    if(!activeLevel && millis() - _Timer02 < _countTimer){
      _countClick++;
      // Single Press
      if (_setClick)
        _setClick();
      //Serial.println(reach_counter);
      _stage = 13;
      if(_countClick == _countTo) {
        // complete Count Click
        if (_setCountClickComplete)
          _setCountClickComplete();
        _countClick = 0;
      }
    }
    else if(!activeLevel && millis() - _Timer02 >= _countTimer) {
      _stage = 13;
    }
  } else if (_stage == 13) { // Time Out
      if( _countMode == false ) {
        _stage = 0; // return
      } // if
      else {
        if( millis() - _Timer02 >= _countTimer) {
          // Count Click Time Out
          if (_setCountClickTimeout)
            _setCountClickTimeout();

          Serial.println("Time Out");
          _stage = 0;
          _countClick = 0;
        }
        else {
          _stage = 0;
        }
      }
  }

} // ButtonKing.isClick()


// end.
