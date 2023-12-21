
#include "joystick.h"

const int SW = 4;

void readJoystick(int *dst){

   int jsw = 0;
   int x = map(analogRead(BASE+0), 0, 1023, 0, 100);
   int y = map(analogRead(BASE+1), 0, 1023, 0, 100);
   if(digitalRead(SW) == 0) jsw = 1;

   *(dst+0) = x;
   *(dst+1) = y;
   *(dst+2) = jsw;
}

int map(int val, int inMin, int inMax, int outMin, int outMax){
   return (val-inMin)*(outMax-outMin)/(inMax-inMin)+outMin;
}

void joystick_init(){
   pinMode(SW, INPUT);
   pullUpDnControl(SW, PUD_UP);
}

