//
// NGController32U4.cpp
//
// Authors:
//       Jon Thysell <thysell@gmail.com>
//       Mikael Norrgård <mick@daemonbite.com>
//       Joel Whybrow <retrorepair@yahoo.co.uk>
//
// (Based on the code by Jon Thysell, but the interfacing is almost completely
//  rewritten by Mikael Norrgård, source modified by Joel Whybrow for use as
//  a Neo Geo adapter)
//
// Copyright (c) 2017 Jon Thysell <http://jonthysell.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Arduino.h"
#include "NGController32U4.h"

NGController32U4::NGController32U4(void)
{
    // Setup input pins (A0,A1,A2,A3,14,15,6,5,4,2 or PF7,PF6,PF5,PF4,PB3,PB1,PD7,PC6,PD4,PD1)
    DDRC  &= ~B01000000; // input
    PORTC |=  B01000000; // high to enable internal pull-up
    DDRD  &= ~B10010010; // input
    PORTD |=  B10010010; // high to enable internal pull-up
    DDRF  &= ~B11110000; // input
    PORTF |=  B11110000; // high to enable internal pull-up
    DDRB  &= ~B00001010; // input
    PORTB |=  B00001010; // high to enable internal pull-up
    
    _inputReg1 = 0;
    _inputReg2 = 0;
    _inputReg3 = 0;
    _inputReg4 = 0;
    _currentState = 0;

}

word NGController32U4::getStateMD()
{
  _currentState = 0;

  // Read input register(s)
  _inputReg1 = PINF;
  _inputReg2 = PINB;
  _inputReg3 = PIND;
  _inputReg4 = PINC;

  // Short delay to stabilise outputs in controller
  delayMicroseconds(SC_CYCLE_DELAY);

  // Read input pins for Up, Down, Left, Right, A, B, C, D, Select, Start
  if (bitRead(_inputReg1, DB15_PIN15_BIT) == LOW) { _currentState |= SC_BTN_UP; }
  if (bitRead(_inputReg1, DB15_PIN7_BIT)  == LOW) { _currentState |= SC_BTN_DOWN; }
  if (bitRead(_inputReg1, DB15_PIN14_BIT) == LOW) { _currentState |= SC_BTN_LEFT; }
  if (bitRead(_inputReg1, DB15_PIN6_BIT)  == LOW) { _currentState |= SC_BTN_RIGHT; }
  if (bitRead(_inputReg2, DB15_PIN13_BIT) == LOW) { _currentState |= SC_BTN_A; }
  if (bitRead(_inputReg2, DB15_PIN5_BIT)  == LOW) { _currentState |= SC_BTN_B; }
  if (bitRead(_inputReg3, DB15_PIN12_BIT) == LOW) { _currentState |= SC_BTN_C; }
  if (bitRead(_inputReg3, DB15_PIN4_BIT)  == LOW) { _currentState |= SC_BTN_D; }
  if (bitRead(_inputReg3, DB15_PIN2_BIT)  == LOW) { _currentState |= SC_BTN_SEL; }
  if (bitRead(_inputReg4, DB15_PIN11_BIT) == LOW) { _currentState |= SC_BTN_START; }                
  


  return _currentState;
}
