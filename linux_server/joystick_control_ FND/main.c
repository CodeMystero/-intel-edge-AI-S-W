#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include "fnd.h"
#include "joystick.h"


int main()
{
	wiringPiSetupGpio();

	joystick_init();
	setPinMode();

	printf("Raspberry Pi SPI ADC program\n");
	mcp3004Setup(BASE, SPI_CHAN);
	int i = 0;

	while(1){

		int jstick[3];
		
		readJoystick(jstick);

		if(jstick[0] > 80) i++;
		if(jstick[0] < 70) i--;
		if(jstick[2] == 1) i=0;
		displayFND10(i);
		
	}
	return 0;
}

