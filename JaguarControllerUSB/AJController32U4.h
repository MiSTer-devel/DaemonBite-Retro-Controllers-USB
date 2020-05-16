//
// AJController32U4.h
//
// Authors:
//       Jon Thysell <thysell@gmail.com>
//       Mikael Norrgård <mick@daemonbite.com>
//       Joel Whybrow <retrorepair@yahoo.co.uk>
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

#ifndef AJController32U4_h
#define AJController32U4_h

enum
{
  J_CONT_CON  = 1,   // The controller is connected (not used)
  J_BTN_UP    = 2,
  J_BTN_DOWN  = 4,
  J_BTN_LEFT  = 8,
  J_BTN_RIGHT = 16,
  J_BTN_A     = 32,
  J_BTN_B     = 64,
  J_BTN_C     = 128,
  J_BTN_OPT   = 256,
  J_BTN_PAUSE = 512,
  J_BTN_0     = 1024,
  J_BTN_1     = 2048,
  J_BTN_2     = 4096,
  J_BTN_3     = 8192,
  J_BTN_4     = 16384,
  J_BTN_5     = 32768,
  J_BTN_6     = 65536,
  J_BTN_7     = 131072,
  J_BTN_8     = 262144,
  J_BTN_9     = 524288,
  J_BTN_STAR  = 1048576,
  J_BTN_HASH  = 2097152,
  HD15_PIN14_BIT = 7, //Row 6
  HD15_PIN13_BIT = 6, //Row 5
  HD15_PIN12_BIT = 4, //Row 4
  HD15_PIN11_BIT = 5, //Row 3
  HD15_PIN10_BIT = 3, //Row 2
  HD15_PIN6_BIT  = 2, //Row 1
  HD15_PIN4_BIT  = 4, //Column 4
  HD15_PIN3_BIT  = 0, //Column 3
  HD15_PIN2_BIT  = 7, //Column 2
  HD15_PIN1_BIT  = 1  //Column 1
};

const byte J_INPUT_PINS = 9;

const byte J_CYCLE_DELAY = 10; // Delay (µs) between setting the select pin and reading the button pins

class AJController32U4 {
  public:
    AJController32U4(void);

    long getStateJag();

  private:
    long _currentState;
    long _currentState2;
    byte _inputReg1;
    byte _inputReg2;
    byte _count;
};

#endif
