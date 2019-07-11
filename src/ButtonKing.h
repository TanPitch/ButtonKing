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

  // set mode for use/ not use triple clicks
  void setTripleMode(bool turns);

  // set mode between normal mode and couting clicks mode
  void setClickMode(bool turns);

  // set Count Clicks Time Out - Default is 10 sec
  void setCountClickTimeout(int ticks);

  // set Count Clicks to - Default is 5 times
  void setCountClickTo(int ticks);

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
  void setTripleClick(callbackFunction newFunction);
  void setShortTripleStart(callbackFunction newFunction);
  void setLongTripleStart(callbackFunction newFunction);
  void setLongTripleStop(callbackFunction newFunction);
  void setCountClickComplete(callbackFunction newFunction);
  void setCountClickTimeout(callbackFunction newFunction);

  void isClick(void);

  void isClick(bool level);

  int setPressedDuration();
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
  bool _tripleMode = false; // turn on/off triple clicks
  bool _countMode = false; // switch between normal / counting clicks mode

  unsigned int _countClick = 0; // count the clicks
  unsigned int _countTo = 5; // count the clicks to
  unsigned long _countTimer = 10000; // clicks timeout

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
  callbackFunction _setTripleClick = NULL;
  callbackFunction _setShortTripleStart = NULL;
  callbackFunction _setLongTripleStart = NULL;
  callbackFunction _setLongTripleStop = NULL;
  callbackFunction _setCountClickComplete = NULL;
  callbackFunction _setCountClickTimeout = NULL;

  int _state = 13;
  unsigned long _Timer01;
  unsigned long _Timer02;
  unsigned long _StartTimer;
  unsigned long _StopTimer;
};

#endif
