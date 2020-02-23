// -----
// ButtonKing.h - Library for detecting button clicks, doubleclicks, simple long
// press and double Long press pattern on a single button. This class is
// implemented for use with the Arduino environment.
// Copyright (c) by Tanyanat Pichitwong
// -----
// 08.07.2019 created by Tanyanat Pichitwong
// 09.07.2019 transformed into a library
// 23.02.2020 created new algorhythm
// -----

#ifndef ButtonKing_h
#define ButtonKing_h

#include "Arduino.h"

// ----- Callback function types -----

extern "C" {
typedef void (*callbackFunction)(void);
}


class ButtonKing
{
public:
  // ----- Constructor -----
  ButtonKing();

  ButtonKing(int pin, int active, bool pullupActive = true);

  // ----- Set runtime parameters -----

  // set # millisec after safe click is assumed.
  void setTimeDebounce(int ticks);

  // set # millisec to ending the button-tickings counter.
  void setTimeCount(int ticks);

  // attach functions that will be called when button was pressed in the
  // specified way.
  void setClick(callbackFunction newFunction);
  void setPress(callbackfunction newFunction);
  void setRelease(callbackFunction newFunction);
  void setDoubleClick(callbackFunction newFunction);
  void setDoublePress(callbackFunction newFunction);
  void setTripleClick(callbackFunction newFunction);
  void setTriplePress(callbackFunction newFunction);

  void isClick(void);
  int getPressedTimer();           // using to get how long the button was pressed.

  void reset(void);                // using to reset the library

private:
  int _pin; // hardware pin number.
  unsigned int _debounceTime = 10; // time to wait for debouncing.
  unsigned int _waitTime = 500;    // time to close the counter that counts
                                   // the button pressing.

  bool _intButtonStage;            // intial stage of the button.
  bool _newButtonStage;            // new or current stage of the button.

  int _debounceState = 0;          // debounce function using machine stage.
  int _buttonCount = 0;            // total button ticks.

  bool _buttonFlag = false;        // to flag if callout function was run or not.

  unsigned long _waitingTimer;     // current time to end all of the function.
  unsigned long _debounceTimer;    // current time to end the debouncing.
  unsigned long _pressedTimer;     // time that the button start pressing.
  unsigned long _stopPressedTimer; // time that the button stop pressing.

  // These variables will hold functions acting as event source.

  callbackFunction _setClick = NULL;
  callbackFunction _setPress = NULL;
  callbackFunction _setRelease = NULL;
  callbackFunction _setDoubleClick = NULL;
  callbackFunction _setDoublePress = NULL;
  callbackFunction _setTripleClick = NULL;
  callbackFunction _setTriplePress = NULL;

};

#endif
