//
// AJController32U4.cpp
//
// Authors:
//       Jon Thysell <thysell@gmail.com>
//       Mikael Norrgård <mick@daemonbite.com>
//       Joel Whybrow <retrorepair@yahoo.co.uk>
//
// (Based on the code by Jon Thysell, but the interfacing is almost completely
//  rewritten by Mikael Norrgård, source modified by Joel Whybrow for use as
//  an Atari Jaguar adapter)
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
#include "AJController32U4.h"

AJController32U4::AJController32U4(void)
{
    // Setup output (column) pins (2,3,4,6 or PD1,PD0,PD4,PD7)
    DDRD  |= B10010011; // output
    PORTD |= B10010011; // high

    // Setup input (row) pins (A3,A2,A1,A0,14,16 or PF4,PF5,PF6,PF7,PB3,PB2)
    DDRF  &= ~B11110000; // input
    PORTF |=  B11110000; // high to enable internal pull-up
    DDRB  &= ~B00001100; // input
    PORTB |=  B00001100; // high to enable internal pull-up
    
    _inputReg1 = 0;
    _inputReg2 = 0;
    _currentState = 0;
    _count = 0;
       

    // Jaguar controllers are quite unique in that the buttons
    // are in a matrix. The columns are strobed LOW and the rows
    // are read one at a time by the console. Button presses are 
    // registered when a row is found to be LOW. Knowing what 
    // column is active at that time the console knows which button
    // has been pressed. Below is a table of those signals (From
    // http://arcarc.xmission.com/Web%20Archives/Deathskull%20%28May-2006%29/games/tech/jagcont.html):
    //
    //                      Column address pin
    //                    (outputs from console)
    //                      4   | 3  |  2  |  1
    //               -----------------------------       
    //      Row data  6 | Pause |    |     |
    //    (inputs to 10 |   A   | B  |  C  |Option   
    //      console) 11 | Right | 1  |  2  |  3
    //               12 | Left  | 4  |  5  |  6
    //               13 | Down  | 7  |  8  |  9
    //               14 |  Up   | *  |  0  |  #


}

long AJController32U4::getStateJag()
{  
  _currentState2 = 0;
  
  // Read input register(s)
  _inputReg1 = PINF;
  _inputReg2 = PINB;

  // Make column active depending on _count
  (_count == 3) ? PORTD &= ~B00000010 : PORTD |= B00000010;
  (_count == 0) ? PORTD &= ~B10000000 : PORTD |= B10000000;
  (_count == 1) ? PORTD &= ~B00000001 : PORTD |= B00000001;
  (_count == 2) ? PORTD &= ~B00010000 : PORTD |= B00010000;

  // Short delay to stabilise outputs in controller  
  delayMicroseconds(J_CYCLE_DELAY);  

  if(_count == 0)
  {
   (bitRead(_inputReg2, HD15_PIN10_BIT) == LOW) ? _currentState |= J_BTN_OPT  : _currentState &= ~J_BTN_OPT ;
   (bitRead(_inputReg1, HD15_PIN11_BIT) == LOW) ? _currentState |= J_BTN_3    : _currentState &= ~J_BTN_3   ;
   (bitRead(_inputReg1, HD15_PIN12_BIT) == LOW) ? _currentState |= J_BTN_6    : _currentState &= ~J_BTN_6   ;
   (bitRead(_inputReg1, HD15_PIN13_BIT) == LOW) ? _currentState |= J_BTN_9    : _currentState &= ~J_BTN_9   ;
   (bitRead(_inputReg1, HD15_PIN14_BIT) == LOW) ? _currentState |= J_BTN_HASH : _currentState &= ~J_BTN_HASH;  
  }

  if(_count == 1)
  {
   (bitRead(_inputReg2, HD15_PIN10_BIT) == LOW) ? _currentState |= J_BTN_C : _currentState &= ~J_BTN_C   ;
   (bitRead(_inputReg1, HD15_PIN11_BIT) == LOW) ? _currentState |= J_BTN_2 : _currentState &= ~J_BTN_2   ;
   (bitRead(_inputReg1, HD15_PIN12_BIT) == LOW) ? _currentState |= J_BTN_5 : _currentState &= ~J_BTN_5   ;
   (bitRead(_inputReg1, HD15_PIN13_BIT) == LOW) ? _currentState |= J_BTN_8 : _currentState &= ~J_BTN_8   ;
   (bitRead(_inputReg1, HD15_PIN14_BIT) == LOW) ? _currentState |= J_BTN_0 : _currentState &= ~J_BTN_0   ;
  }

  if(_count == 2)
  {
    (bitRead(_inputReg2, HD15_PIN10_BIT) == LOW) ? _currentState |= J_BTN_B    : _currentState &= ~J_BTN_B; 
    (bitRead(_inputReg1, HD15_PIN11_BIT) == LOW) ? _currentState |= J_BTN_1    : _currentState &= ~J_BTN_1; 
    (bitRead(_inputReg1, HD15_PIN12_BIT) == LOW) ? _currentState |= J_BTN_4    : _currentState &= ~J_BTN_4; 
    (bitRead(_inputReg1, HD15_PIN13_BIT) == LOW) ? _currentState |= J_BTN_7    : _currentState &= ~J_BTN_7; 
    (bitRead(_inputReg1, HD15_PIN14_BIT) == LOW) ? _currentState |= J_BTN_STAR : _currentState &= ~J_BTN_STAR;  
  }

  if(_count == 3)
  {
    (bitRead(_inputReg2, HD15_PIN6_BIT)  == LOW) ? _currentState |= J_BTN_PAUSE : _currentState &= ~J_BTN_PAUSE;
    (bitRead(_inputReg2, HD15_PIN10_BIT) == LOW) ? _currentState |= J_BTN_A     : _currentState &= ~J_BTN_A;
    (bitRead(_inputReg1, HD15_PIN14_BIT) == LOW) ? _currentState |= J_BTN_UP    : _currentState &= ~J_BTN_UP;
    (bitRead(_inputReg1, HD15_PIN13_BIT) == LOW) ? _currentState |= J_BTN_DOWN  : _currentState &= ~J_BTN_DOWN;       
    (bitRead(_inputReg1, HD15_PIN11_BIT) == LOW) ? _currentState |= J_BTN_RIGHT : _currentState &= ~J_BTN_RIGHT;
    (bitRead(_inputReg1, HD15_PIN12_BIT) == LOW) ? _currentState |= J_BTN_LEFT  : _currentState &= ~J_BTN_LEFT;  
  }
  
  if (_count >= 3){
    _count = 0;
  }
  else{
    _count++;
  }
  
  if (!_currentState == 0) {_currentState2 = (_currentState);}
  return _currentState2;
}
