/*
 *  Times calculation
 * PR=4999 --> TC increments on every PR+1/CCLK = 50[us]
 *
 * 		f=1[Hz]     --> T=1000[ms] --> Ttogle=500[ms]  --> MATCH = (500[ms]/50[us])-1 = 9999
 * 		f=10[Hz]    --> T=100[ms]  --> Ttogle=50[ms]   --> MATCH = (50[ms]/50[us])-1 = 999
 * 		f=100[Hz]   --> T=10[ms]   --> Ttogle=5[ms]    --> MATCH = (5[ms]/50[us])-1  = 99
 */

#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"

#define SET_PR 5000

void configEint(void);
void configTimer0(void);
void configTimer1(void);

uint8_t state = 0;

uint32_t count = 0;
float period = 0;

int periods[3] = {9999, 999, 99};

int main(void)
{
    configEint();
    configTimer0();
    configTimer1();

    while (1)
    {
    }
    return 0;
}

void configEint(void)
{
	//P2.10 as EINT0
	PINSEL_CFG_Type pinCfg;
	pinCfg.Portnum = PINSEL_PORT_2;
	pinCfg.Pinnum = PINSEL_PIN_10;
	pinCfg.Funcnum = PINSEL_FUNC_1;
	pinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PINSEL_ConfigPin(&pinCfg);

	//EINT0 configuration
	EXTI_InitTypeDef extiCfg;
	extiCfg.EXTI_Line = EXTI_EINT0;
	extiCfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	extiCfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	EXTI_Config(&extiCfg);
	EXTI_ClearEXTIFlag(EXTI_EINT0);

    NVIC_SetPriority(EINT0_IRQn, 1);
    NVIC_EnableIRQ(EINT0_IRQn);
}

void configTimer0(void)
{
    //P1.28 as MAT0.0
	PINSEL_CFG_Type pinCfg;
	pinCfg.Portnum = PINSEL_PORT_1;
	pinCfg.Pinnum = PINSEL_PIN_28;
	pinCfg.Funcnum = PINSEL_FUNC_3;
	pinCfg.Pinmode = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pinCfg);

	//TIM0 configuration
    TIM_TIMERCFG_Type timCfg;
	timCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	timCfg.PrescaleValue = SET_PR;

	//MAT0.0 Configuration
	TIM_MATCHCFG_Type matchCfg;
	matchCfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	matchCfg.IntOnMatch = DISABLE;
	matchCfg.MatchChannel = 0;
	matchCfg.MatchValue = periods[0];
	matchCfg.ResetOnMatch = ENABLE;
	matchCfg.StopOnMatch = DISABLE;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, (void*) &timCfg);
	TIM_ConfigMatch(LPC_TIM0, &matchCfg);
	TIM_Cmd(LPC_TIM0, ENABLE);

}

void configTimer1(void)
{
	// P1.18 as CAP1.0
	PINSEL_CFG_Type pinCfg;
	pinCfg.Portnum = PINSEL_PORT_1;
	pinCfg.Pinnum = PINSEL_PIN_18;
	pinCfg.Funcnum = PINSEL_FUNC_3;
	pinCfg.Pinmode = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&pinCfg);

	//TIM1 Configuration
    TIM_TIMERCFG_Type timCfg;
	timCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	timCfg.PrescaleValue = SET_PR;

	//CAP1.0 Configuration
	TIM_CAPTURECFG_Type capCfg;
	capCfg.CaptureChannel = 0;
	capCfg.FallingEdge = DISABLE;
	capCfg.IntOnCaption = ENABLE;
	capCfg.RisingEdge = ENABLE;

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, (void*) &timCfg);
	TIM_ConfigCapture(LPC_TIM1, &capCfg);
	TIM_Cmd(LPC_TIM1, ENABLE);

    NVIC_EnableIRQ(TIMER1_IRQn);
}

void EINT0_IRQHandler(void)
{
    state++;
    if (state > 2)
        state = 0;

    //It is easier to use registers than drivers
    LPC_TIM0->TCR |= 2;
    LPC_TIM0->MR0 = periods[state];
    LPC_TIM0->TCR &= ~(2);

    EXTI_ClearEXTIFlag(EXTI_EINT0);
}

void TIMER1_IRQHandler(void)
{

    uint32_t oldCount = count;
    count = LPC_TIM1->CR0;

    period = (count - oldCount) * 0.05;

    TIM_ClearIntPending(LPC_TIM1, TIM_CR0_INT);
}
