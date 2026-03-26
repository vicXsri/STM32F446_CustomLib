/*
 * timebase.c
 *
 *  Created on: Jun 3, 2025
 *      Author: Vichu
 */


#include "timbase.h"

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;


void delay(uint32_t delay){
	uint32_t tickstart = Get_Tick();
	uint32_t wait =delay;

	if(wait < MAX_DELAY){
		wait += (uint32_t)TICK_FREQ;
	}

	while((Get_Tick() - tickstart) < wait){}

}

uint32_t Get_Tick(void){
	__disable_IRQ();
	g_curr_tick_p = g_curr_tick;
	__enable_IRQ();
	return g_curr_tick_p;
}

void Tick_Increament(void){
	g_curr_tick += TICK_FREQ;
}

void TimeBase_Init(uint32_t clk){
	__disable_IRQ();
	SysTick->SCR = 0;
	SysTick->RVR = (clk / 1000) - 1;
	SysTick->CVR = 0;
	SysTick->SCR |= SYS_INT; // Set the clock source to processor clock
	SysTick->SCR |= CTRL_TICKINT; // Enable the Interrupt
	SysTick->SCR |= CTRL_ENABLE;  // Enable the systick
	while((SysTick->SCR & CTRL_COUNTFLAG) == 0);
	__enable_IRQ();
}

void SysTick_Handler(void){
	Tick_Increament();
}
