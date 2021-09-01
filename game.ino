#include <OLED_I2C.h>//
OLED  screen(SDA, SCL, 8);
extern uint8_t SmallFont[];//Includes font(I forgot why, prob for debug mode)
int maxSpeed = 10;//Maximum speed the circle can reach
//Starting X and Y positions of the circle
int x = 64;
int y = 32;
float startSpeed = 2.0;//Starting speed
float accelAmount = 0.1;//If enableAccel is true this var will be used to define how fast the circle should accelerate
float Speed = startSpeed;/*Sets speed to the starting speed
Speed does change and all the other functions use it
Starting speed doesn't change and speed uses it as a starting value(thx cap)
*/
bool debug = true; //Debug mode(not made yet)
bool enableAccel = true;//Enable acceleration(if turned on - will be 
bool enableVert = true;
bool enableFake = true;
void setup() {
  pinMode(2, OUTPUT);//Left button
  pinMode(3, OUTPUT);//Right button
  screen.begin();//Screen enables
  screen.setFont(SmallFont);//Screen sets font to SmallFont but afaik it can work without this
  Serial.begin(9600);//Serial port for debugging purposes
}

void loop() {
    Serial.println(x + "<- X Y -> " + y);//Prints out X and Y of the circle to Serial port
    if(digitalRead(3) == 1 && digitalRead(2) != 1){ //Makes the circle go right
      x = x+Speed;
      delay(10);
      //Makes the circle accelerate if the var is true
      if(enableAccel == true){
        Speed = Speed + accelAmount; 
      }
    }
    if(digitalRead(2) == 1 && digitalRead(3) != 1) {//Makes the circle go left
      x = x-Speed;
      delay(10);
      //Makes the circle accelerate if the var is true
      if(enableAccel == true){
        Speed = Speed + accelAmount; 
      }
    }
    //"Portals" | Basically just teleports ball to the opposite side
    if(x >= 128){
      x = 1;
    }
    if(x <= 0){
      x = 127;
    }
    if(y >= 64){
      y = 1;
    }
    if(y <= 0){
      y = 63;
    }
    //Makes the ball move down if both buttons are pressed and enableVert is true
    if(digitalRead(2) == 1 && digitalRead(3) == 1 && enableVert == true){
      y = y+Speed;
      //Makes the circle accelerate if the var is true
      if(enableAccel == true){
        Speed = Speed+0.1; 
      }
    }
    if(digitalRead(2) == 0 && digitalRead(3) == 0 && enableAccel == true){//If all buttons are released and acceleration is enabled - Speed gets set to starting speed
      Speed = startSpeed;
    }
    if(Speed > maxSpeed){//If speed exceeds max speed it gets set back to it
      Speed = maxSpeed;
    }
    screen.clrScr(); //Clears previous frame before drawing a new one
    screen.drawCircle(x, y, 5);//Draws a circle(player)
    //Draws lines to represent portals
    screen.drawLine(0, 64, 0, 0);
    screen.drawLine(127, 64, 127, 0);
    screen.drawLine(0, 63, 128, 63);
    screen.drawLine(0, 1, 128, 1);
    //If fakes are enabled - Use them
    if(enableFake == true){
      fake();
    }
    screen.update();//Updates the screen
}

void fake(){ //Simulates real portal by drawing a second circle when the main circle is near the edge of the wall(needs to be finished by picking right co-ordinates to draw circle on)
    if(x == 123){
      screen.drawCircle(1, y, 5);
    }
    if(x == 124){
      screen.drawCircle(2, y, 5);
    }
    if(x == 125){
      screen.drawCircle(3, y, 5);
    }
    if(x == 126){
      screen.drawCircle(5, y, 5);
    }
}