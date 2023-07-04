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

#include "ShiftRegister.h"

/**
 * @param ser The SER pin number which is used to set the new incoming value.
 * @param rck The RCK pin number which is used to copy the shift register values to the register for ouptuts.
 * @param srck The SRCK pin number which is used to shift to right the shift register.
 * @param numberOfSRegister The number of 74hc595 registers linked together.
 */
ShiftRegister::ShiftRegister(uint8_t ser, uint8_t rck, uint8_t srck, int numberOfSRegisters){
    din = ser;
    copy = rck;
    shifter = srck;
    registersBits = numberOfSRegisters*8;
    head = nullptr;
    list_size = 0;
    initList(registersBits);
}  

/**
 * Setup the pinsMode to OUTPUT mode
 */
void ShiftRegister::setup(){
    pinMode(din, OUTPUT);
    pinMode(copy, OUTPUT);
    pinMode(shifter, OUTPUT);
    //to remove
    Serial.begin(9600);
}

/**
 * Begin silent shifts (should be called before endSilentShift)
 * reset the RCK bit to 0
 */
void ShiftRegister::beginSilentShift(){
    digitalWrite(copy, LOW);
}

/**
 * End silent shifts (should be called after a beginShift)
 * copy the shift register to the outputs register. RCK to 1.
 */
void ShiftRegister::endSilentShift(){
    digitalWrite(copy, HIGH);
}

/**
 * Should be called between beginSilentShift and endSilentShift, 
 * make a sigle shift without copying to the output register.
 * Time Complexity: O(1) where n is the number of outputs.
 * @param data The data to shift into the register. 0 or 1.
 */
void ShiftRegister::silentShift(bool data){
    silentShiftWithoutMemory(data);
    shiftList(data);
}

/** 
 * make a single shift and copy the result to the output register.
 * @param data The data to shift into the register. 0 or 1.
 */
void ShiftRegister::shift(bool data){
    beginSilentShift();
    silentShift(data);
    endSilentShift();
}

/**
 * Set the register data.
 * @param data The data array to send to the register.
 * @param length The data array length.
 * It should be the same size as the number of outputs of your register.
 */
void ShiftRegister::display(bool data[], int length){
    if(length > registersBits) length = registersBits;
    beginSilentShift();
    for(int i = length-1; i >= 0; i--){
        silentShift(data[i]);
    }
    endSilentShift();
}

/**
 * Set the register data.
 * @param data The data 8 bytes to send to the register.
 * It should be the same size as the number of outputs of your register.
 */
void ShiftRegister::display(unsigned long data){
    unsigned long mask = 0x1;
    unsigned long bits = data;
    beginSilentShift();
    for(int i = registersBits-1; i >= 0; i--){
        silentShift(bits & mask);
        bits = bits >> 1;
    }
    endSilentShift();
}

/**
 * Reset all outputs to 0
 * 
 */
void ShiftRegister::allBitsLow(){
    beginSilentShift();
    for(int i = registersBits-1; i >= 0; i--){
        silentShift(false);
    }
    endSilentShift();
}

/**
 * Set all outputs to 1
 */
void ShiftRegister::allBitsHigh(){
    beginSilentShift();
    for(int i = registersBits-1; i >= 0; i--){
        silentShift(true);
    }
    endSilentShift();
}

/**
   * Remove the last element of the list.
  */
void ShiftRegister::removeLast(){
    if(head == nullptr) return;
    bool_cell_t * last_element = head->before;
    bool_cell_t * before_last = last_element->before;
    head->before = before_last;
    before_last->next = head;
    if(last_element == head) head = nullptr;
    delete last_element;
    list_size--;
}

/**
 * The new cell containing the new value become the new head.
 * @param b The boolean to add.
 */
void ShiftRegister::addHead(bool b){
    if(head == nullptr) {
        head = createElement(b, nullptr, nullptr);
        list_size++;
        return;
    }
    bool_cell_t * last_element = head->before;
    bool_cell_t * element = createElement(b, last_element, head);
    head->before = element;
    last_element->next = element;
    head = element;
    list_size++;
}

/**
 * Shift the list and add a new head element, the last tail element is deleted.
 * @param b The boolean to add.
 */
void ShiftRegister::shiftList(bool b){
    addHead(b);
    if(list_size > registersBits) removeLast();
}

/**
 * Creates a new element for a list.
 * @param b The value of the new element to create.
 * @param next The next element address.
 * @param before The before element address.
 * @return A new element for a list linked with the next and the before element.
 * If the next or before fields are null, they will point to the new element itself.
 */
bool_cell_t * ShiftRegister::createElement(bool b, bool_cell_t * before, bool_cell_t * next){
    bool_cell_t * element = new bool_cell_t;
    element->value = b;
    if(before == nullptr) element->before = element;
    else element->before = before;
    if(next == nullptr) element->next = element;
    else element->next = next;
    return element;
}

/**
 * Delete the list
 */
void ShiftRegister::deleteList(){
    while(head != nullptr && list_size > 0){
        removeLast();
    }
}

ShiftRegister::~ShiftRegister(){
    deleteList();
}

void print_all(bool_cell_t * head){
    bool_cell_t * e = head;
    Serial.print("[");
    while(e != head->before){
        Serial.print(e->value);
        Serial.print(",");
        e = e->next;
    }
    Serial.print(e->value);
    Serial.print("]");
    Serial.println();
}

/**
 * Set the value for a specified output number without changing other values.
 * Time Complexity: O(n) where n is the number of outputs.
 * @param index The output index inside of your registers.
 * @param value The value to set to this output (HIGH or LOW).
 * @warning If you want to make simple shifts use shift() or silentShift() instead.
 */
void ShiftRegister::writeTo(int index, bool value){
    if(index < 0 || index >= registersBits)return;
    beginSilentShift();
    bool_cell_t * end = head->before;
    bool_cell_t * e = end;
    int end_index = registersBits-1;
    if(index == end_index)end->value = value;
    silentShiftWithoutMemory(end->value);
    e = e->before;
    int i = end_index-1;
    while(e != end){
        if(i == index)e->value = value;
        silentShiftWithoutMemory(e->value);
        e = e->before;
        i--;
    }
    endSilentShift();
    print_all(head);
}

/**
 * Shift without updating the memory
 * @param data The value to shift into the registers.
 */
void ShiftRegister::silentShiftWithoutMemory(bool data){
    digitalWrite(shifter, LOW);
    if(data) digitalWrite(din, HIGH);
    else digitalWrite(din, LOW);
    digitalWrite(shifter, HIGH);
}

/**
 * Initialize the list of bits.
* @param size The size of the list. 
*/
void ShiftRegister::initList(int size){
    for(int i = 0; i < size; i++){
        addHead(false);
    }
}