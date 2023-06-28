
# SimpleShiftRegisterController
A Shift Register Controller simple API for the 74hc595 adapted to small projects.

---

## Author and license

Copyright (C) 2023 ollprogram

SimpleShiftRegisterController is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.
SimpleShiftRegisterController is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.
You should have received a copy of the [GNU General Public License](LICENSE) along with SimpleShiftRegisterController.
If not, see <https://www.gnu.org/licenses/>.

---

## Description

I made a very simple API in order to control a Shift Register like the 74hc595 without repeating the same code each time.
This API also allows you to control multiple 74hc595 in cascade connection. 
 
---

## Usage

All examples are available [here](examples/)

<br> You can set all bits by using a the display method with an integer (only working for less than 8 registers) or with a bit array. See the related examples : 
- [display using an 8 bits integer](examples/display8Bits/display8Bits.ino)
- [display using a 16 bits integer](examples/display16Bits/display16Bits.ino)
- [display using an array of bits](examples/displayArray/displayArray.ino)

Or you can also control bits of the shift register yourself bit by bit. See the related examples :
- [shifting without writing each shift to the outputs](examples/silentShift/silentShift.ino)
- [shifting and writing each shift to the outputs](examples/silentShift/silentShift.ino)

---

## Download & Install

You can find and download the zip file in the releases. 

On arduino IDE select 'sketch > include library > add .ZIP library'
