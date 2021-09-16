#include <OLED_I2C.h>
OLED  screen(SDA, SCL, 8);
extern uint8_t SmallFont[];
void setup() {
  //Sets pinmodes for 4 buttons that I have
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);      
}

void loop() {
  screen.clrScr();
  //Code here
  screen.update();
}
