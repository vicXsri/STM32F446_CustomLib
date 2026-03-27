/*
 * msp.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "msp.h"


void USART_MspInit(UART_HandleTypeDef* huart){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  if(huart->Instance == USART2){

		  __RCC_USART2_CLK_ENABLE();
		  __RCC_GPIOA_CLK_ENABLE();

		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/

		  /*TX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_2 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF7;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

		  /*RX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_3 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF7;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);
	  }

}


void CAN1_MspInit(CAN_HandleTypeDef* hcan){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(hcan->Instance == CAN1){

		  __RCC_CAN1_CLK_ENABLE();
		  __RCC_GPIOA_CLK_ENABLE();

		  /**CAN1 GPIO Configuration
			PA12     ------> CAN1_TX
			PA11     ------> CAN1_RX
		   **/

		  /*TX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_12 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF9;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

		  /*RX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_11 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF9;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

	  }

}
