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
