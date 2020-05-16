/*  Gamepad.h
 *   
 *  Based on the advanced HID library for Arduino: 
 *  https://github.com/NicoHood/HID
 *  Copyright (c) 2014-2015 NicoHood
 * 
 *  Copyright (c) 2020 Mikael Norrgård <http://daemonbite.com>
 *  
 *  Modified by Joel Whybrow <retrorepair@yahoo.co.uk>
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

#pragma once

#include <Arduino.h>
#include "HID.h"

extern const char* gp_serial;

typedef __uint24 uint24_t;

// The numbers after colon are bit fields, meaning how many bits the field uses.
// Remove those if there are problems
typedef struct {
  union 
  {
    struct {
      bool  b0: 1 ;
      bool  b1: 1 ;
      bool  b2: 1 ;
      bool  b3: 1 ;
      bool  b4: 1 ;
      bool  b5: 1 ;
      bool  b6: 1 ;
      bool  b7: 1 ;
      bool  b8: 1 ;
      bool  b9: 1 ;
      bool  b10: 1 ;
      bool  b11: 1 ;
      bool  b12: 1 ;
      bool  b13: 1 ;
      bool  b14: 1 ;
      bool  b15: 1 ;
      bool  b16: 1 ;
      bool  b17: 1 ;                        
      bool  b18: 1 ;                        
      bool  b19: 1 ;                        
      bool  b20: 1 ;                        
      bool  b21: 1 ;                        
      bool  b22: 1 ;                        
      bool  b23: 1 ;                                                            
    };
    uint24_t buttons; //Must be large enough for all those buttons!
  };
  int8_t X  ;
  int8_t Y  ;  
  
} GamepadReport;


class Gamepad_ : public PluggableUSBModule
{
  private:
    uint8_t reportId;

  protected:
    int getInterface(uint8_t* interfaceCount);
    int getDescriptor(USBSetup& setup);
    uint8_t getShortName(char *name);
    bool setup(USBSetup& setup);
    
    uint8_t epType[1];
    uint8_t protocol;
    uint8_t idle;
    
  public:
    GamepadReport _GamepadReport;
    Gamepad_(void);
    void reset(void);
    void send();
};
