#pragma once
//
//    FILE: HC4052.h
//  AUTHOR: Rob Tillaart
//    DATE: 2023-01-25
// VERSION: 0.1.2
// PURPOSE: Arduino library for HC4052 2x4 channel multiplexer and compatibles.
//     URL: https://github.com/RobTillaart/HC4052


#include "Arduino.h"

#define HC4052_LIB_VERSION         (F("0.1.2"))


class HC4052
{
public:
  explicit HC4052(uint8_t A, uint8_t B, uint8_t enablePin = 255)
  {
    _pins[0] = A;
    _pins[1] = B;
    uint8_t i = 2;
    while (i--)
    {
      pinMode(_pins[i], OUTPUT);
      digitalWrite(_pins[i], LOW);
    }
    _channel = 0;

    if (enablePin != 255)
    {
      _enablePin = enablePin;
      pinMode(_enablePin, OUTPUT);
      digitalWrite(_enablePin, HIGH);
    }
  }


  void setChannel(uint8_t channel)
  {
    if ((channel & 0x03) != _channel)
    {
      _channel = channel & 0x03;
      digitalWrite(_pins[0], _channel & 0x01);
      digitalWrite(_pins[1], _channel & 0x02);
    }
  }


/*
  bool setChannel(uint8_t channel)
  {
    if (channel > 0x03) return false;
    if (channel  != _channel)
    {
      _channel = channel;
      digitalWrite(_pins[0], _channel & 0x01);
      digitalWrite(_pins[1], _channel & 0x02);
    }
    return true;
  }
*/


  uint8_t getChannel()
  {
    return _channel;
  }


  void enable()
  {
    if (_enablePin != 255)
    {
      digitalWrite(_enablePin, LOW);
    }
  }


  void disable()
  {
    if (_enablePin != 255)
    {
      digitalWrite(_enablePin, HIGH);
    }
  }


  bool isEnabled()
  {
    if (_enablePin != 255)
    {
      return (digitalRead(_enablePin) == LOW);
    }
    return true;
  }


private:
  uint8_t  _pins[3];
  uint8_t  _enablePin = 255;
  uint8_t  _channel   = 0;
};


//  -- END OF FILE --

