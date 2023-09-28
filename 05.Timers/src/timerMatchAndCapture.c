/*
 *  Times calculation
 * PR=4999 --> TC increments on every PR+1/CCLK = 50[us]
 *
 * 		f=1[Hz]     --> T=1000[ms] --> Ttogle=500[ms]  --> MATCH = (500[ms]/50[us])-1 = 9999
 * 		f=10[Hz]    --> T=100[ms]  --> Ttogle=50[ms]   --> MATCH = (50[ms]/50[us])-1 = 999
 * 		f=100[Hz]   --> T=10[ms]   --> Ttogle=5[ms]    --> MATCH = (5[ms]/50[us])-1  = 99
 */

#include "LPC17xx.h"

#define SET_PR 4999

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
    LPC_PINCON->PINSEL4 |= (1 << 20);
    LPC_SC->EXTINT |= (1);
    LPC_SC->EXTMODE |= (1);
    LPC_SC->EXTPOLAR |= (1);
    NVIC_SetPriority(EINT0_IRQn, 1);
    NVIC_EnableIRQ(EINT0_IRQn);
}

void configTimer0(void)
{
    LPC_PINCON->PINSEL3 |= (3 << 24); // P1.28 as MAT0.0

    LPC_SC->PCONP |= (1 << 1);
    LPC_SC->PCLKSEL0 |= (1 << 2); // PCLK = cclk

    LPC_TIM0->PR = SET_PR;
    LPC_TIM0->MR0 = periods[0];
    LPC_TIM0->MCR = 2;         // Timer0 reset on Match0
    LPC_TIM0->EMR |= (3 << 4); // MAT0.0 toggle mode
    LPC_TIM0->IR |= 0x3F;      // Clear all interrupt flag
    LPC_TIM0->TCR = 3;         // Enable and Reset
    LPC_TIM0->TCR &= ~2;
}

void configTimer1(void)
{
    LPC_PINCON->PINSEL3 |= (3 << 4); // P1.18 as CAP0.1

    LPC_SC->PCONP |= (1 << 2);
    LPC_SC->PCLKSEL0 |= (1 << 4); // PCLK = cclk
    LPC_TIM1->PR = SET_PR;

    LPC_TIM1->CCR |= (5); // CAP1.0 rising edge interrupt

    LPC_TIM1->IR |= 0x3F; // Clear all interrupt flags
    LPC_TIM1->TCR = 3;    // Enable and Reset
    LPC_TIM1->TCR &= ~2;
    NVIC_EnableIRQ(TIMER1_IRQn);
}

void EINT0_IRQHandler(void)
{
    state++;
    if (state > 2)
        state = 0;

    LPC_TIM0->TCR |= 2;
    LPC_TIM0->MR0 = periods[state];
    LPC_TIM0->TCR &= ~(2);

    LPC_SC->EXTINT |= 1;
}

void TIMER1_IRQHandler(void)
{

    uint32_t oldCount = count;
    count = LPC_TIM1->CR0;

    period = (count - oldCount) * 0.05;

    LPC_TIM1->IR |= 1 << 4;
}
