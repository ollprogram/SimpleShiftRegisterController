/*
* Copyright (C) 2023 ollprogram
*
* This file is part of SimpleShiftRegisterController.
* SimpleShiftRegisterController is free software: you can redistribute it and/or modify it under the terms of
* the GNU General Public License as published by the Free Software Foundation, either version 3 of the License,
* or (at your option) any later version.
* SimpleShiftRegisterController is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
* You should have received a copy of the GNU General Public License along with SimpleShiftRegisterController.
* If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#define SINGLE 8
#define DUAL 16

#include "Arduino.h" 

/**
* @author ollprogram
* A class which represent a simple shift registor without the "reset" and the "enable" pins
*
*/
class ShiftRegister{
  public:
  /**
  * @param ser The SER pin number which is used to set the new incoming value.
  * @param rck The RCK pin number which is used to copy the shift register values to the register for ouptuts.
  * @param srck The SRCK pin number which is used to shift to right the shift register.
  * @param numberOfOutputs The number of outputs for this register.
  */
  ShiftRegister(uint8_t ser, uint8_t rck, uint8_t srck, int numberOfOutputs);

  /**
  * Setup the pinsMode to OUTPUT mode
  */
  void setup();

  /**
  * Begin silent shifts (should be called before endSilentShift)
  * reset the RCK bit to 0
  */
  void beginSilentShift();

  /**
  * End silent shifts (should be called after a beginShift)
  * copy the shift register to the outputs register. RCK to 1.
  */
  void endSilentShift();

  /**
  * Should be called between beginSilentShift and endSilentShift, 
  * make a sigle shift without copying to the output register.
  * @param data The data to shift into the register. 0 or 1.
  */
  void silentShift(bool data);

  /** 
  * make a single shift and copy the result to the output register.
  * @param data The data to shift into the register. 0 or 1.
  */
  void shift(bool data);

  /**
  * Set the register data.
  * @param data The data array to send to the register.
  * It should be the same size as the number of outputs of your register.
  */
  void display(bool data[]);

 /**
  * Set the register data.
  * @param data The data byte to send to the register.
  * It should be the same size as the number of outputs of your register.
  */
  void display(uint8_t data);

  /**
  * Set the register data.
  * @param data The data 2 bytes to send to the register.
  * It should be the same size as the number of outputs of your register.
  */
  void display16(uint16_t data);

  private:
  uint8_t din;
  uint8_t copy;
  uint8_t shifter;
  int length;
};

#endif