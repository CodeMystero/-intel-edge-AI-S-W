#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include "keypad.h"

const int led = 5;
void pwm_(int);
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
		pwm_(valueInt);
	
	}
	return 0;

}

void pwm_(int src){
	softPwmWrite(led, 10*src);
	delay(10*src);
}
