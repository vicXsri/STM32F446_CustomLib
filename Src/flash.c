/*
 * flash.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "flash.h"


void __FLASH_PREFETCH_LATENCY(void){
	FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN|FLASH_ACR_LATENCY_5WS;
}
