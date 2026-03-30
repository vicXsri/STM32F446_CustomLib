/*
 * pwr.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */


#include "pwr.h"


void __PWR_VOLTAGESCALING_CONFIG(void){
	PWR->CR |= PWR_VOS_SCALE1;
}

Status_TypeDef __PWR_OVERDRIVE_ENABLE(void){

	uint32_t tickstart =0;

	PWR->CR |= PWR_ODEN;

	tickstart = Get_Tick();
	while(!(PWR->CSR & (1UL << 16U))){
		if((Get_Tick() - tickstart) > PWR_TIMEOUT ){
			return VIC_TIMEOUT;
		}
	}

	PWR->CR |= PWR_ODSWEN;

	tickstart = Get_Tick();
	while(!(PWR->CSR & (1UL << 17U))){
		if((Get_Tick() - tickstart) > PWR_TIMEOUT ){
			return VIC_TIMEOUT;
		}
	}

	return VIC_OK;
}

//void __PWR_OVERDRIVE_ENABLE(void){
//	PWR->CR &= ~PWR_ODEN;
//}
