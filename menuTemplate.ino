#include <OLED_I2C.h>
OLED  screen(SDA, SCL, 8);
extern uint8_t SmallFont[];
typedef enum GameScreen { MENU = 0, GAME } GameScreen;

GameScreen curScreen = MENU;
void setup() {
  screen.begin();
  screen.setFont(SmallFont);  
  //Sets pinmodes for 4 buttons that I have
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);      
}

void loop() {
  screen.clrScr();
  switch(curScreen){
    case MENU:
      screen.print("Press ANY button", 16, 32);
      screen.print("to PLAY", 40, 47);
      screen.print("Title", 48, 15);
      if(digitalRead(2) == 1 || digitalRead(3) == 1 || digitalRead(4) == 1 || digitalRead(5) == 1){
        curScreen = GAME;
      }
      break;
    case GAME:
      //Game code here
      screen.print("Game screen", 16, 32);
      break;
  }
  screen.update();
}
