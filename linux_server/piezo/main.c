#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include "keypad.h"
#include <stdlib.h>

const int pinPiezo = 18;
const int melody[] = {131, 147, 165, 174, 196, 220, 247, 262};

int main(){

	wiringPiSetupGpio();
	softToneCreate(pinPiezo);

	pin_mode();
	pin_pupd();

	while(1){

		read_keypad();

		if (value != 'a'){
			printf("%c\n",value);
			int valueInt = atoi(&value);
	
			softToneWrite(pinPiezo, melody[valueInt-1]);
			delay(200);
			softToneWrite(pinPiezo, 0);
		}

		value = 'a';
	}
	return 0;

}
