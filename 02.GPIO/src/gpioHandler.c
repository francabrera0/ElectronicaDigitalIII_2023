#include <stdio.h>
#include <stdint.h>
#include <LPC17xx.h>
#include "gpioHandler.h"

volatile uint32_t* pinselBase = &LPC_PINCON->PINSEL0;
volatile uint32_t* pinmodeBase = &LPC_PINCON->PINMODE0;
volatile uint32_t* fiodirBase = &LPC_GPIO0->FIODIR;
volatile uint32_t* fiopinBase = &LPC_GPIO0->FIOPIN;


void gpioConfig(int portNumber, int pin, int pinMode, int direction) {

	int column = (pin<=15) ? 0:1;
	int pinAux = (pin>=16) ? pin-16:pin;

	*(pinselBase + portNumber*2 + column) &= ~(3<<2*pinAux);
	*(pinmodeBase + portNumber*2 + column) &= ~(3<<2*pinAux);
	*(fiodirBase + portNumber*8) &= ~(1<<pin);

	if(pinMode!=0)
		*(pinmodeBase + portNumber*2 + column) |= (pinMode<<2*pinAux);

	*(fiodirBase + portNumber*8) |= (direction<<pin);
}

void gpioWrite(int portNumber, int pin, int state) {
	if (state==LOW)
		*(fiopinBase + portNumber*8) &= ~(1<<pin);
	else
		*(fiopinBase + portNumber*8) |= (1<<pin);
}

int gpioRead(int portNumber, int pin) {
	return (*(fiopinBase + portNumber*8)>>pin) & 0x01;
}
