#include <wiringPi.h>

#define BASE 100
#define SPI_CHAN 0

#ifndef _JOYSTICK_H
#define _JOYSTICK_H

extern const int SW;

#endif 

void readJoystick(int *dst);
int map(int val, int inMin, int inMax, int outMin, int outMax);
void joystick_init();
