//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
//including the library.
#include <ShiftRegister.h>
#define OUTPUTS_SIZE SINGLE //number of ouputs of your shift register (SINGLE = 8, DUAL = 16)
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, OUTPUTS_SIZE);
void setup() {
  //setup the arduino pins
  sr.setup();
}

void loop() {
  for(int i = 0; i < OUTPUTS_SIZE; i++){
    sr.shift(true);
    delay(100);
  }
  for(int i = 0; i < OUTPUTS_SIZE; i++){
    sr.beginSilentShift();//begin a shift of the shift register before copying to the register of the outputs.
    for(int j = 0; j <= i; j++){
      sr.silentShift(false);
    }
    for(int j = 0; j < OUTPUTS_SIZE-1-i; j++){
      sr.silentShift(true);
    }
    sr.endSilentShift();//display the result (copying to the register)
    delay(100);
  }
}
