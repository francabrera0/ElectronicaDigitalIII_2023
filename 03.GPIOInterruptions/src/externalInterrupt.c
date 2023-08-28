#include "LPC17xx.h"

#define REDLED 		(1<<22)
#define GREENLED 	(1<<25)
#define BLUELED 	(1<<26)
#define EINT0  		(1<<0)
#define EINT1		(1<<1)
#define EINT2		(1<<2)


void configGPIO(void);
void configEINT(void);

int main(void) {

	configGPIO();
	configEINT();
	LPC_GPIO0->FIOSET |= REDLED;
	LPC_GPIO3->FIOSET |= GREENLED;
	LPC_GPIO3->FIOSET |= BLUELED;

	while(1) {
		//do nothing
	}

    return 0 ;
}

void EINT0_IRQHandler(void) {
	LPC_GPIO0->FIOCLR |= REDLED;
	LPC_GPIO3->FIOSET |= GREENLED;
	LPC_GPIO3->FIOSET |= BLUELED;
	LPC_SC->EXTINT |= EINT0;
}

void EINT1_IRQHandler(void) {
	LPC_GPIO0->FIOSET |= REDLED;
	LPC_GPIO3->FIOCLR |= GREENLED;
	LPC_GPIO3->FIOSET |= BLUELED;
	LPC_SC->EXTINT |= EINT1;
}

void EINT2_IRQHandler(void) {
	LPC_GPIO0->FIOSET |= REDLED;
	LPC_GPIO3->FIOSET |= GREENLED;
	LPC_GPIO3->FIOCLR |= BLUELED;
	LPC_SC->EXTINT |= EINT2;
}


void configGPIO(void) {
	/*PINSEL*/
	LPC_PINCON->PINSEL1 &= ~(0x3<<12); //P0.22 as GPIO
	LPC_PINCON->PINSEL7 &= ~(0xf<<18); //P3.25,  P3.26 as GPIO

	/*FIODIR*/
	LPC_GPIO0->FIODIR |= REDLED;    //P0.22 as output
	LPC_GPIO3->FIODIR |= BLUELED;   //P3.25 as output
	LPC_GPIO3->FIODIR |= GREENLED;  //P3.25 as output

}

void configEINT(void) {

	LPC_PINCON->PINSEL4 |= (1<<20); //EINT0
	LPC_PINCON->PINSEL4 |= (1<<22); //EINT1
	LPC_PINCON->PINSEL4 |= (1<<24); //EINT2

	LPC_SC->EXTMODE |= EINT0; //EINT0 edge sensitive
	LPC_SC->EXTMODE |= EINT1; //EINT1 edge sensitive
	LPC_SC->EXTMODE |= EINT2; //EINT2 edge sensitive

	LPC_SC->EXTPOLAR |= EINT0; //EINT0 rising edge
	LPC_SC->EXTPOLAR |= EINT1; //EINT1 rising edge
	LPC_SC->EXTPOLAR &= ~(EINT2); //EINT2 falling edge

	LPC_SC->EXTINT |= EINT0; //EINT0 clear flag
	LPC_SC->EXTINT |= EINT1; //EINT1 clear flag
	LPC_SC->EXTINT |= EINT2; //EINT2 clear flag

	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);

}

