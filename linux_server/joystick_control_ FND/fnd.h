#pragma once
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#ifndef _FND_H
#define _FND_H

extern const int DIG1;
extern const int A;
extern const int F;
extern const int DIG2;
extern const int DIG3;
extern const int B2;
extern const int DIG4;
extern const int G;
extern const int C;
extern const int DP;
extern const int D;
extern const int E;

extern const int leds[12];
extern const int digits[4];

#endif

//             A
//          F     B
//             G
//          E     C
//             D     DP


void digitalOnOff(int, int, int, int);
void displayNumber(int);
void setPinMode(void);
void displayFND16(int);
void displayFND10(int);
