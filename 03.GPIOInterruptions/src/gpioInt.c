#include "LPC17xx.h"

#define REDLED 		(1<<22)
#define GREENLED 	(1<<25)
#define BLUELED 	(1<<26)
#define INPUT1		(1<<9)
#define INPUT2		(1<<10)
#define INPUT3		(1<<11)

void configGPIO(void);
void configGpioInt(void);

int main(void) {

	configGPIO();
	configGpioInt();
	LPC_GPIO0->FIOSET |= REDLED;
	LPC_GPIO3->FIOSET |= GREENLED;
	LPC_GPIO3->FIOSET |= BLUELED;

	while(1) {
		//do nothing
	}

    return 0 ;
}

void EINT3_IRQHandler(void) {
	//debounce treating

	if(LPC_GPIOINT->IO0IntStatF & INPUT1) { //P0.9 falling
		LPC_GPIO0->FIOCLR |= REDLED;
		LPC_GPIO3->FIOSET |= GREENLED;
		LPC_GPIO3->FIOSET |= BLUELED;
		LPC_GPIOINT->IO0IntClr |= INPUT1;
	}
	else if(LPC_GPIOINT->IO0IntStatR & INPUT2) { //P0.10 rising
		LPC_GPIO0->FIOSET |= REDLED;
		LPC_GPIO3->FIOCLR |= GREENLED;
		LPC_GPIO3->FIOSET |= BLUELED;
		LPC_GPIOINT->IO0IntClr |= INPUT2;
	}
	else if(LPC_GPIOINT->IO0IntStatF & INPUT3 || LPC_GPIOINT->IO0IntStatR & INPUT3) { //P0.11 falling/rising
		LPC_GPIO0->FIOSET |= REDLED;
		LPC_GPIO3->FIOSET |= GREENLED;
		LPC_GPIO3->FIOCLR |= BLUELED;
		LPC_GPIOINT->IO0IntClr |= INPUT3;
	}
}

void configGPIO(void) {
	/*PINSEL*/
	LPC_PINCON->PINSEL1 &= ~(0x3<<12); //P0.22 as GPIO
	LPC_PINCON->PINSEL7 &= ~(0xf<<18); //P3.25,  P3.26 as GPIO
	LPC_PINCON->PINSEL0 &= ~(0x2f<<18); //P0.9, P0.10 as GPIO

	/*FIODIR*/
	LPC_GPIO0->FIODIR |= REDLED;    //P0.22 as output
	LPC_GPIO3->FIODIR |= BLUELED;   //P3.25 as output
	LPC_GPIO3->FIODIR |= GREENLED;  //P3.25 as output
	LPC_GPIO0->FIODIR &= ~(INPUT1); //P0.9 as input
	LPC_GPIO0->FIODIR &= ~(INPUT2); //P0.10 as input
	LPC_GPIO0->FIODIR &= ~(INPUT3); //P0.11 as input

	LPC_PINCON->PINMODE0 &= ~(0x2f<<18); //P0.9 and P0.11 with pull-up
	LPC_PINCON->PINMODE0 |= (0x3<<20);
}

void configGpioInt(void) {
	LPC_GPIOINT->IO0IntEnF |= INPUT1; //P0.9 falling edge interrupt
	LPC_GPIOINT->IO0IntEnR |= INPUT2; //P0.10 rising edge interrupt
	LPC_GPIOINT->IO0IntEnF |= INPUT3;
	LPC_GPIOINT->IO0IntEnR |= INPUT3; //P0.11 falling/rising edge interrupt

	NVIC_EnableIRQ(EINT3_IRQn); //ISER0 |= (1<<21) (table 52)
}

