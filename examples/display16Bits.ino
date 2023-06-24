//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
#define OUTPUTS_SIZE DUAL //number of ouputs of your shift register (SINGLE = 8, DUAL = 16)
//including the library.
#include <ShiftRegister.h>
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, OUTPUTS_SIZE);
void setup() {
  //setup the arduino pins
  sr.setup();
}

void loop() {
  sr.display(0b0101010101010101);
  delay(1000);
  sr.display(0b1010101010101010);
  delay(1000);
}