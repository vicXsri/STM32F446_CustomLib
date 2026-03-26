/*
 * flash.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "main.h"

typedef struct{
	uint32_t ACR; //Flash access control register
	uint32_t KEYR; //Flash key register
	uint32_t OTPKEYR; //Flash option key register
	uint32_t SR; //Flash status register
	uint32_t CR; //Flash control register
	uint32_t OTPCR; //Flash option control register
}FLASH_TypeDef;

#define FLASH	((FLASH_TypeDef*)FLASH_BASE)


#define FLASH_ACR_PRFTEN			(1U << 8)
#define FLASH_ACR_ICEN				(1U << 9)
#define FLASH_ACR_DCEN				(1U << 10)

#define FLASH_ACR_LATENCY_5WS		(0x05U << 0)


void __FLASH_PREFETCH_LATENCY(void);

#endif /* FLASH_H_ */
