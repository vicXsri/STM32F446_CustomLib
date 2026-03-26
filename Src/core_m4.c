/*
 * core_m4.c
 *
 *  Created on: Jun 1, 2025
 *      Author: Vichu
 */


#include "core_m4.h"

void NVIC_Enable(uint32_t IRQn){
	__asm volatile("":::"memory");
	NVIC_R->ISER[(((uint32_t)IRQn) >> 5UL)] |= (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
	__asm volatile("":::"memory");
}
