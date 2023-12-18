#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include "keypad.h"

const int led = 5;

int main()
{
	wiringPiSetupGpio();
	softPwmCreate(led, 0, 100);
	delay(1000);
	pin_mode();
	pin_pupd();
	while(1){

		read_keypad();
		int valueInt = atoi(&value);
		if(valueInt == 0) softPwmWrite(led, 0);
		if(valueInt == 1) softPwmWrite(led, 25);
		if(valueInt == 2) softPwmWrite(led, 50);
		if(valueInt == 3) softPwmWrite(led, 75);
		if(valueInt == 4) softPwmWrite(led, 100);
		delay(10);
	
	}
	return 0;

}
