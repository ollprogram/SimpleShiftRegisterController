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

#include "Arduino.h" 

typedef struct bool_cell {
  struct bool_cell * next;
  struct bool_cell * before;
  bool value;
} bool_cell_t;

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
  * @param numberOfSRegister The number of 74hc595 registers linked together.
  */
  ShiftRegister(uint8_t ser, uint8_t rck, uint8_t srck, int numberOfSRegisters);

  ~ShiftRegister();

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
  * Time Complexity: O(1) where n is the number of outputs.
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
  * @param length The data array length.
  * It should be the same size as the number of outputs of your register.
  */
  void display(bool data[], int length);

  /**
  * Set the register data.
  * @param data The data 8 bytes to send to the register.
  * It should be the same size as the number of outputs of your register.
  */
  void display(unsigned long data);

  /**
  * Reset all outputs to 0
  * 
  */
  void allBitsLow();

  /**
   * Set all outputs to 1
  */
  void allBitsHigh();

  /**
   * Set the value for a specified output number without changing other values.
   * Complexity: O(n) where n is the number of outputs.
   * @warning If you want to make simple shifts use shift() or silentShift() instead.
   * @param index The output index inside of your registers.
   * @param value The value to set to this output (HIGH or LOW).
  */
  void writeTo(int index, bool value);

  private:
  uint8_t din;
  uint8_t copy;
  uint8_t shifter;
  int registersBits;
  /* BOOL LIST */
  bool_cell_t * head;
  int list_size;
  /**
   * Remove the last element of the list.
  */
  void removeLast();

  /**
   * The new cell containing the new value become the new head.
   * @param b The boolean to add.
  */
  void addHead(bool b);

  /**
   * Shift the list and add a new head element, the last tail element is deleted.
   * @param b The boolean to add.
  */
  void shiftList(bool b);

  /**
   * Creates a new element for a list.
   * @param b The value of the new element to create.
   * @param next The next element address.
   * @param before The before element address.
   * @return A new element for a list linked with the next and the before element.
   * If the next or before fields are null, they will point to the new element itself.
  */
  bool_cell_t * createElement(bool b, bool_cell_t * before, bool_cell_t * next);

  /**
   * Delete the list
  */
  void deleteList();

  /**
   * Shift without updating the memory
   * @param data The value to shift into the registers.
  */
  void silentShiftWithoutMemory(bool data);

 /**
 * Initialize the list of bits.
* @param size The size of the list. 
*/
  void initList(int size);
};

#endif