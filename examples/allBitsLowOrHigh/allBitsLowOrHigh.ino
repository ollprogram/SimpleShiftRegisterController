//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
//including the library.
#include <ShiftRegister.h>
#define REGS 1 // shift register number
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, REGS);
void setup() {
  //setup the arduino pins
  sr.setup();
  sr.allBitsLow();//if you want to reset bits on startup
}

void loop() {
  sr.allBitsLow();
  delay(1000);
  sr.allBitsHigh();
  delay(1000);
}
