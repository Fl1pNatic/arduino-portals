#include <OLED_I2C.h>
OLED screen(SDA, SCL, 8);
extern uint8_t SmallFont[];
typedef enum GameScreen { MENU = 0, GAME } GameScreen;
GameScreen curScreen = MENU;
float clicks = 0;
int toGive = 1;
int reqClicks = 50;
int level = 1;
bool hold;
void setup() {
  screen.begin();
  screen.setFont(SmallFont);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

}

void loop() {
  screen.clrScr();
  switch(curScreen){
    case MENU:
      if(digitalRead(2) == 1 || digitalRead(3) == 1 || digitalRead(4) == 1 || digitalRead(5) == 1){
        curScreen = GAME;
      }    
      screen.print("Clicker", 48, 15);
      screen.print("Any button - PLAY", 16, 32);
      break;
    case GAME:
      if(digitalRead(5) == 1 && hold == false){
        hold = true;
        clicks = clicks + toGive;
      }
      if(digitalRead(5) != 1){
        hold = false;
      }
      if(digitalRead(2) == 1 && clicks >= reqClicks){
        clicks = clicks - reqClicks;
        toGive = toGive * 2;
        reqClicks = reqClicks * level;
        level++;
      }
      if(digitalRead(3) == 1){
        reqClicks = 50;
        clicks = 0;
        level = 1;
        toGive = 1;
      }
      screen.print("Clicks:", 0, 32);
      screen.printNumI(clicks, 80, 32);
      screen.print("Left-up - Upgrade", 0, 5);
      screen.print("Right-up - Reset", 0, 15);
      screen.print("Req. clicks:", 0, 45);
      screen.printNumI(reqClicks, 80, 45);
      screen.print("Per click:", 0, 55);
      screen.printNumI(toGive, 60, 55);
      break;
  }
  screen.update();
}
