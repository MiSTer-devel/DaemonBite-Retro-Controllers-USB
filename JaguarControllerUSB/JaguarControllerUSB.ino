/*  DaemonBite Jaguar USB Adapter
 *  Author: Mikael Norrgård <mick@daemonbite.com>
 *  Modified by Joel Whybrow <retrorepair@yahoo.co.uk>
 *  
 *  Copyright (c) 2020 Mikael Norrgård <http://daemonbite.com>
 *  
 *  GNU GENERAL PUBLIC LICENSE
 *  Version 3, 29 June 2007
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  
 */

#include "AJController32U4.h"
#include "Gamepad.h"

// ATT: 20 chars max (including NULL at the end) according to Arduino source code.
// Additionally serial number is used to differentiate arduino projects to have different button maps!
const char *gp_serial = "Jaguar to USB";

// Controller HD15 pins (looking face-on to the end of the plug):
//
//   5   4   3   2   1
//     10  9   8   7   6
//  15  14  13  12  11
//
// Connect pin 7 to +5V and pin 9 to GND
// Connect the remaining pins to digital I/O pins (see below)
// HD15    Arduino Pro Micro
// --------------------------------------
//  1      2  PD1
//  2      6  PD7
//  3      3  PD0
//  4      4  PD4
//  6     16  PB2
//  10    14  PB3
//  11    A2  PF5
//  12    A3  PF4
//  13    A1  PF6
//  14    A0  PF7

AJController32U4 controller;

// Set up USB HID gamepad
Gamepad_ Gamepad;
bool usbUpdate = false; // Should gamepad data be sent to USB?

// Controller states
uint24_t currentState = 0;
long lastState = 1;

void setup()
{ 
}

void loop()
{
  currentState = controller.getStateJag();
  sendState();
}

void sendState()
{
  // Only report controller state if it has changed
  if (currentState != lastState)
  {
    Gamepad._GamepadReport.buttons = currentState >> 5; //Shift bits to the right where buttons start after X/Y
    Gamepad._GamepadReport.Y = ((currentState & B00000100) >> 2) - ((currentState & B00000010) >> 1);
    Gamepad._GamepadReport.X = ((currentState & B00010000) >> 4) - ((currentState & B00001000) >> 3);
    Gamepad.send();
    lastState = currentState;
  }
}
