#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"

#include <stdio.h>


void configADC();
void configTimer();
void configGPIO();

uint16_t ADC0Value = 0;

int main(void)
{
	configTimer();
	configGPIO();
	configADC();

	while(1)
    {

    }

	return 0;

}

void configTimer()
{
	TIM_TIMERCFG_Type configTimer;
	configTimer.PrescaleValue = 10000;
	configTimer.PrescaleOption = TIM_PRESCALE_TICKVAL;

	TIM_MATCHCFG_Type configMatch;
	configMatch.IntOnMatch = DISABLE;
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	configMatch.MatchChannel = 1;
	configMatch.MatchValue = 4999;
	configMatch.ResetOnMatch = ENABLE;
	configMatch.StopOnMatch = DISABLE;

	TIM_ConfigMatch(LPC_TIM0, &configMatch);
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configTimer);
	TIM_Cmd(LPC_TIM0, ENABLE);

	return;
}


void configADC()
{
	LPC_PINCON->PINSEL1 |= (1<<14);  //ADC0 Pin
	LPC_PINCON->PINMODE1 |= (1<<15); //Neither

	ADC_Init(LPC_ADC, 200000);
	ADC_BurstCmd(LPC_ADC, DISABLE);
	ADC_StartCmd(LPC_ADC, ADC_START_ON_MAT01);
	ADC_ChannelCmd(LPC_ADC, 0, ENABLE);
	ADC_EdgeStartConfig(LPC_ADC, ADC_START_ON_RISING);
	ADC_IntConfig(LPC_ADC, ADC_ADINTEN0, ENABLE);
	NVIC_EnableIRQ(ADC_IRQn);

	return;
}

void ADC_IRQHandler()
{
	ADC0Value=((LPC_ADC->ADDR0)>>4)&0xFFF;
	LPC_GPIO0->FIOPIN = ADC0Value;
	LPC_ADC->ADGDR &= LPC_ADC->ADGDR;
	return;
}

void configGPIO()
{
	LPC_GPIO0->FIODIR |= (0xFFF<<0);
	LPC_GPIO0->FIOMASK |= ~(0xFFF<<0);
}
