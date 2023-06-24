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
 * @param numberOfOutputs The number of outputs for this register.
 */
ShiftRegister::ShiftRegister(uint8_t ser, uint8_t rck, uint8_t srck, int numberOfOutputs){
    this->din = ser;
    this->copy = rck;
    this->shifter = srck;
    this->length = numberOfOutputs;
}  

/**
 * Setup the pinsMode to OUTPUT mode
 */
void ShiftRegister::setup(){
    pinMode(din, OUTPUT);
    pinMode(copy, OUTPUT);
    pinMode(shifter, OUTPUT);
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
 * @param data The data to shift into the register. 0 or 1.
 */
void ShiftRegister::silentShift(bool data){
    digitalWrite(shifter, LOW);
    if(data) digitalWrite(din, HIGH);
    else digitalWrite(din, LOW);
    digitalWrite(shifter, HIGH);
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
 * It should be the same size as the number of outputs of your register.
 */
void ShiftRegister::display(bool data[]){
    if(sizeof(data)*8 < length) return;
    beginSilentShift();
    for(int i = length-1; i >= 0; i--){
        silentShift(data[i]);
    }
    endSilentShift();
}

/**
 * Set the register data.
 * @param data The data byte to send to the register.
 * It should be the same size as the number of outputs of your register.
 */
void ShiftRegister::display(uint8_t data){
    if(length < 8) return;
    uint8_t mask = 0x1;
    uint8_t bits = data;
    beginSilentShift();
    for(int i = length-1; i >= 0; i--){
        silentShift(bits & mask);
        bits = bits >> 1;
    }
    endSilentShift();
}

/**
 * Set the register data.
 * @param data The data 2 bytes to send to the register.
 * It should be the same size as the number of outputs of your register.
 */
void ShiftRegister::display16(uint16_t data){
    if(length < 16) return;
    uint16_t mask = 0x1;
    uint16_t bits = data;
    beginSilentShift();
    for(int i = length-1; i >= 0; i--){
        silentShift(bits & mask);
        bits = bits >> 1;
    }
    endSilentShift();
}