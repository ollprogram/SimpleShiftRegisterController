//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
#define REGS 1 // shift register number
//including the library.
#include <ShiftRegister.h>
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, REGS);
void setup() {
  //setup the arduino pins
  sr.setup();
  sr.allBitsLow();//if you want to reset bits on startup
}

bool data1[] = {0, 0, 0, 0, 1, 1, 1, 1};
bool data2[] = {1, 1, 1, 1, 0, 0, 0, 0};
const int dataSize = 8; // The array length.

void loop() {
  sr.display(data1, dataSize);
  delay(1000);
  sr.display(data2, dataSize);
  delay(1000);
}
