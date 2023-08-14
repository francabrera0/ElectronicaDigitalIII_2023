#include "LPC17xx.h"

#define REDLED 		(1<<22)
#define GREENLED 	(1<<25)
#define BLUELED 	(1<<26)

void configGPIO(void);
void delay(uint32_t times);

int main(void) {

	configGPIO();
	LPC_GPIO0->FIOSET |= REDLED;
	LPC_GPIO3->FIOSET |= GREENLED;
	LPC_GPIO3->FIOSET |= BLUELED;

	while(1) {
		LPC_GPIO3->FIOSET |= BLUELED;
		LPC_GPIO0->FIOCLR |= REDLED;
		delay(1000);
		LPC_GPIO0->FIOSET |= REDLED;
		LPC_GPIO3->FIOCLR |= GREENLED;
		delay(1000);
		LPC_GPIO3->FIOSET |= GREENLED;
		LPC_GPIO3->FIOCLR |= BLUELED;
		delay(1000);
	}

    return 0 ;
}

void configGPIO(void) {
	/*PINSEL*/
	LPC_PINCON->PINSEL1 &= ~(0x3<<12);
	LPC_PINCON->PINSEL7 &= ~(0xf<<18);

	/*FIODIR*/
	LPC_GPIO0->FIODIR |= REDLED;
	LPC_GPIO3->FIODIR |= BLUELED;
	LPC_GPIO3->FIODIR |= GREENLED;
}

void delay(uint32_t times) {
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++);
}
