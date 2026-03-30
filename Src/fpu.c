/*
 * fpu.c
 *
 *  Created on: Mar 27, 2026
 *      Author: Vichu
 */


#include "fpu.h"


#define FPU_CPCAR_ADDRESS	0xE000ED88


void FPU_Init(void){
	uint32_t *addr = (uint32_t*)0xE000ED88;
	*addr |= (0x1UL << 20U);
	*addr |= (0x1UL << 21U);
	*addr |= (0x1UL << 22U);
	*addr |= (0x1UL << 23U);

}
