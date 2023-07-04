//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
#define REGS 2 // shift register number
//including the library.
#include <ShiftRegister.h>
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, REGS);
void setup() {
  //setup the arduino pins
  sr.setup();
  sr.allBitsLow();//if you want to reset bits on startup
}

const int size = REGS*8;

void loop() {
  sr.writeTo(0, HIGH);
  delay(1000);
  sr.writeTo(0, LOW);
  delay(1000);
}
