/*
 * it.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "it.h"
//#include "uart.h"

extern Debounce_Handel_t user_btn;
extern void UART_isr (UART_HandleTypeDef *huart);
extern UART_HandleTypeDef huart2;

void EXTI15_10_IRQHandler(void){
	if((EXTI->PR & (1U << 13)) != 0){
        if (Debounce_Check(&user_btn, Get_Tick())) {
        	GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
		EXTI->PR |= (1U << 13);
	}
}



void USART2_IRQHandler(){
	if(USART2->SR & (1U << 0x05U)){
		/* USART2 Callback Function*/
		UART_isr(&huart2);
	}
}

