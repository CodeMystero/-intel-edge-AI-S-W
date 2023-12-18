#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include "lcd1602.h"

#define BASE 100
#define SPI_CHAN 0
const int led = 21;


int main()
{
	wiringPiSetup();
	printf("Raspberry Pi SPI ADC Program\n");
	mcp3004Setup(BASE, SPI_CHAN);

	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();


	int result;
	
	while(1){
		result = analogRead(BASE+SPI_CHAN);
		lcdClear();
		lcdLoc(LINE1);
		typeln("-=CDS VALUE====-");
		lcdLoc(LINE2);
		typeln("LIGHT ** ");
		typeInt(result);
		typeln(" **");
		//printf("CDS: %d\n", analogRead(BASE + SPI_CHAN));
		delay(500);

	}
	return 0;
}
