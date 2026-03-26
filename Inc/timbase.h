/*
 * timbase.h
 *
 *  Created on: Jun 3, 2025
 *      Author: Vichu
 */

#ifndef TIMBASE_H_
#define TIMBASE_H_

#include "main.h"

#define CTRL_ENABLE			(1U << 0)
#define CTRL_TICKINT		(1U << 1)
#define CTRL_CLOCKSRC		(1U << 2)
#define CTRL_COUNTFLAG		(1U << 16)

#define CLOCK_FREQ			SYS_DEF_CORE_CLOCK
#define	ONE_MSEC_LOAD		(CLOCK_FREQ/1000U)
#define	MAX_DELAY			(0xFFFFFFFF)
#define TICK_FREQ			(1)

#define SYS_INT			(1U << 2)

void delay(uint32_t delay);
void TimeBase_Init(uint32_t clk);
void Tick_Increament(void);
uint32_t Get_Tick(void);
#endif /* TIMBASE_H_ */


