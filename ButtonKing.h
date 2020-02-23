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
typedef void (*parameterizedCallbackFunction)(void*);
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
  void setClick(parameterizedCallbackFunction newFunction, void* parameter);
  void setPress(callbackFunction newFunction);
  void setPress(parameterizedCallbackFunction newFunction, void* parameter);
  void setRelease(callbackFunction newFunction);
  void setRelease(parameterizedCallbackFunction newFunction, void* parameter);
  void setDoubleClick(callbackFunction newFunction);
  void setDoubleClick(parameterizedCallbackFunction newFunction, void* parameter);
  void setDoublePress(callbackFunction newFunction);
  void setDoublePress(parameterizedCallbackFunction newFunction, void* parameter);
  void setTripleClick(callbackFunction newFunction);
  void setTripleClick(parameterizedCallbackFunction newFunction, void* parameter);
  void setTriplePress(callbackFunction newFunction);
  void setTriplePress(parameterizedCallbackFunction newFunction, void* parameter);

  void isClick(void);
  void isClick(bool level);
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

  callbackFunction _ClickFunc = NULL;
  parameterizedCallbackFunction _paramClickFunc = NULL;
  void* _ClickFuncParam = NULL;

  callbackFunction _PressFunc = NULL;
  parameterizedCallbackFunction _paramPressFunc = NULL;
  void* _PressFuncParam = NULL;

  callbackFunction _ReleaseFunc = NULL;
  parameterizedCallbackFunction _paramReleaseFunc = NULL;
  void* _ReleaseFuncParam = NULL;

  callbackFunction _DoubleClickFunc = NULL;
  parameterizedCallbackFunction _paramDoubleClickFunc = NULL;
  void* _DoubleClickFuncParam = NULL;

  callbackFunction _DoublePressFunc = NULL;
  parameterizedCallbackFunction _paramDoublePressFunc = NULL;
  void* _DoublePressFuncParam = NULL;

  callbackFunction _TripleClickFunc = NULL;
  parameterizedCallbackFunction _paramTripleClickFunc = NULL;
  void* _TripleClickFuncParam = NULL;

  callbackFunction _TriplePressFunc = NULL;
  parameterizedCallbackFunction _paramTriplePressFunc = NULL;
  void* _TriplePressFuncParam = NULL;

};

#endif
