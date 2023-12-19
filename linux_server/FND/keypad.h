#pragma once
#include <stdio.h>
#include <wiringPi.h>

#ifndef _KEYPAD_H
#define _KEYPAD_H

extern const int _R[4];
extern const int _C[4];
extern char key_pad[4][4];
extern char value;

#endif

void pin_mode();
void pin_pupd();
void read_keypad();
