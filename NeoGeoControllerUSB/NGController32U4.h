//
// NGController32U4.h
//
// Authors:
//       Jon Thysell <thysell@gmail.com>
//       Mikael Norrgård <mick@daemonbite.com>
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

#ifndef NGController32U4_h
#define NGController32U4_h

enum
{
  SC_CTL_ON    = 1,   // The controller is connected (not used)
  SC_BTN_UP    = 2,
  SC_BTN_DOWN  = 4,
  SC_BTN_LEFT  = 8,
  SC_BTN_RIGHT = 16,
  SC_BTN_A     = 32,
  SC_BTN_B     = 64,
  SC_BTN_C     = 128,
  SC_BTN_D     = 256,
  SC_BTN_SEL   = 512,
  SC_BTN_START = 1024,
  DB15_PIN15_BIT = 7,
  DB15_PIN7_BIT = 6,
  DB15_PIN14_BIT = 5,
  DB15_PIN6_BIT = 4,
  DB15_PIN13_BIT = 3,
  DB15_PIN5_BIT = 1,
  DB15_PIN12_BIT = 7,
  DB15_PIN11_BIT = 6,
  DB15_PIN4_BIT = 4,
  DB15_PIN2_BIT = 1
};

const byte SC_INPUT_PINS = 9;

const byte SC_CYCLE_DELAY = 10; // Delay (µs) between setting the select pin and reading the button pins

class NGController32U4 {
  public:
    NGController32U4(void);

    word getStateMD();

  private:
    word _currentState;

    byte _inputReg1;
    byte _inputReg2;
    byte _inputReg3;
    byte _inputReg4;
};

#endif
