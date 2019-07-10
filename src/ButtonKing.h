// -----
// ButtonKing.h - Library for detecting button clicks, doubleclicks, simple long
// press and double Long press pattern on a single button. This class is
// implemented for use with the Arduino environment.
// Copyright (c) by Tanyanat Pichitwong
// -----
// 08.07.2019 created by Tanyanat Pichitwong
// 09.07.2019 transformed into a library
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

  // set # millisec after single short press is assumed.
  void setTimeShort(int ticks);

  // set # millisec after single long press is assumed.
  void setTimeLong(int ticks);

  // set # millisec after double press is assumed.
  void setTimeDouble(int ticks);

  // attach functions that will be called when button was pressed in the
  // specified way.
  void setClick(callbackFunction newFunction);
  void setShortClickStart(callbackFunction newFunction);
  void setLongClickStart(callbackFunction newFunction);
  void setLongClickStop(callbackFunction newFunction);
  void setDoubleClick(callbackFunction newFunction);
  void setShortDoubleStart(callbackFunction newFunction);
  void setLongDoubleStart(callbackFunction newFunction);
  void setLongDoubleStop(callbackFunction newFunction);

  void isClick(void);

  void isClick(bool level);

  bool isLongPressed();
  int getPressedTicks();
  void reset(void);

private:
  int _pin; // hardware pin number.
  unsigned int _debounceTime = 10; // number of ticks for debounce times.
  unsigned int _shortTime = 500; // number of ticks that have to pass by
                                // before a short press is detected.
  unsigned int _longTime = 500; // number of ticks that have to pass by
                                // before a long button press is detected
  unsigned int _DoubleTime = 300; // number of ticks that have to pass by
                                  // before a double press is detected

  int _buttonPressed;

  // These variables will hold functions acting as event source.

  callbackFunction _setClick = NULL;
  callbackFunction _setShortClickStart = NULL;
  callbackFunction _setLongClickStart = NULL;
  callbackFunction _setLongClickStop = NULL;
  callbackFunction _setDoubleClick = NULL;
  callbackFunction _setShortDoubleStart = NULL;
  callbackFunction _setLongDoubleStart = NULL;
  callbackFunction _setLongDoubleStop = NULL;

  int _state = 0;
  unsigned long _Timer01;
  unsigned long _Timer02;
};

#endif
