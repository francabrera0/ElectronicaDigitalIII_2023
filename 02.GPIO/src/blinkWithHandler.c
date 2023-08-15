/**
 * @file blinkWithHandler.c
 *
 * @brief This file use the gpio driver defined in gpioHandler.h to
 * 			blink the built in RGB led.
 */

#include "LPC17xx.h"
#include "gpioHandler.h"

#define REDLED 		(22)
#define GREENLED 	(25)
#define BLUELED 	(26)

void configGPIO(void);
void delay(uint32_t times);

int main(void) {

	configGPIO();

	gpioWrite(PORT0, REDLED, HIGH);
	gpioWrite(PORT3, GREENLED, HIGH);
	gpioWrite(PORT3, BLUELED, HIGH);

	while(1) {
		if(gpioRead(PORT0, 0)) {
			gpioWrite(PORT0, REDLED, LOW);
			gpioWrite(PORT3, GREENLED, LOW);
			gpioWrite(PORT3, BLUELED, LOW);
		}
		else {
			gpioWrite(PORT3, BLUELED, HIGH);
			gpioWrite(PORT0, REDLED, LOW);
			delay(1000);
			gpioWrite(PORT0, REDLED, HIGH);
			gpioWrite(PORT3, GREENLED, LOW);
			delay(1000);
			gpioWrite(PORT3, GREENLED, HIGH);
			gpioWrite(PORT3, BLUELED, LOW);
			delay(1000);
		}
	}

    return 0 ;
}

void configGPIO(void) {
	gpioConfig(PORT0, REDLED, NEITHER, OUTPUT);
	gpioConfig(PORT3, GREENLED, NEITHER, OUTPUT);
	gpioConfig(PORT3, BLUELED, NEITHER, OUTPUT);
	gpioConfig(PORT0, 0, PULLDOWN, INPUT);

}

void delay(uint32_t times) {
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++);
}
