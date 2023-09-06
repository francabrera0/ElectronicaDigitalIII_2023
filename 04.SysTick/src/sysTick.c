#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void ledConfig(void);
void intConfig(void);

#define WAVEFORM  0xaa	//(10101010)


int main(void) {
	ledConfig();
	intConfig();

	while(1) {

	};

    return 0 ;
}


void ledConfig(void){
	LPC_PINCON->PINSEL1 &= ~(3<<12); 	//P0.22 as GPIO
	LPC_GPIO0->FIODIR2 |= (1<<6); 		//P0.22 as output
}

void intConfig(void){

	LPC_PINCON->PINSEL4 |= (1<<24); 	//P2.12 as EINT2 (pin 25:24 = 0b01)
	LPC_PINCON->PINMODE4 &= ~(3<<24); 	//pullUp

	LPC_SC->EXTMODE |= (1<<2); 			//P2.12 edge interrupt
	LPC_SC->EXTPOLAR &= ~(1<<2); 		//Falling edge
	LPC_SC->EXTINT |= (1<<2); 			//Clear flags
	NVIC_EnableIRQ(EINT2_IRQn); 		//NVIC enable

	if(SysTick_Config(SystemCoreClock/100)) { //Cmsis function
		while(1);
	}

	/*SysTick->LOAD = ((SystemCoreClock/100)-1);
	SysTick->CTRL = (1) | (1<<1) | (1<<2);
	SysTick->VAL = 0;
	NVIC_SetPriority(SysTick_IRQn,5);*/
}

void EINT2_IRQHandler(void){
	static uint8_t state; 	//System state
	if(state){
		LPC_GPIO0->FIOSET |= (1<<22); 	//Turn off led
		SysTick->CTRL &= ~(1<<1); 		//SysTick interrupts disabled
	}
	else{
		SysTick->CTRL |= (1<<1); 		//SysTick interrupts enabled
	}

	state = !state;
	LPC_SC->EXTINT |= (1<<2); 			//Clear EINT2 flag
}


void SysTick_Handler(void){
	static uint8_t clkDiv = 0;
	static uint8_t counter = 0;

	if(clkDiv==10){
		LPC_GPIO0->FIOPIN = (((~WAVEFORM & 0xff) << counter & 0x80)<<15);
		counter = (counter==7) ? 0:counter+1;
		clkDiv=0;
	}
	else {
		clkDiv ++;
	}

	SysTick->CTRL &= SysTick->CTRL; //Clear flag
}
