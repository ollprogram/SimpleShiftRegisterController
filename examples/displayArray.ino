//You can test it by connecting leds to your 74hc595 outputs
//Shift register inputs
#define SER 13 // the next data to add to the register
#define RCK 12 // the register validation 
#define SRCK 8 // the shift register clock
#define OUTPUTS_SIZE SINGLE //number of ouputs of your shift register (SINGLE = 8, DUAL = 16)
//including the library.
#include <ShiftRegister.h>
//instantiate 
ShiftRegister sr(SER, RCK, SRCK, OUTPUTS_SIZE);
void setup() {
  //setup the arduino pins
  sr.setup();
}

bool data1[] = {0, 0, 0, 0, 1, 1, 1, 1};
bool data2[] = {1, 1, 1, 1, 0, 0, 0, 0};

void loop() {
  sr.display(data1);
  delay(1000);
  sr.display(data2);
  delay(1000);
}
