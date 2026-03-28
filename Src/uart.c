/*
 * uart.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "uart.h"

extern UART_HandleTypeDef huart2;


#define uart &huart2
#define TIMEOUT_DEF	500


uint16_t timeout;


RingBuffer_TypeDef rx_buffer = { { 0 }, 0, 0};
RingBuffer_TypeDef tx_buffer = { { 0 }, 0, 0};

RingBuffer_TypeDef *_rx_buffer;
RingBuffer_TypeDef *_tx_buffer;


void store_char(unsigned char c, RingBuffer_TypeDef * buffer);


/********************************************************************************************/
void RingBuffer_Init(void){
	_rx_buffer = &rx_buffer;
	_tx_buffer = &tx_buffer;

	/*Enable the error interrupt*/
	__UART_ENABLE_IT_EIE(uart);

	/*Enable the rx interrupt*/
	__UART_ENABLE_IT_RXNE(uart);
}

void store_char(unsigned char c, RingBuffer_TypeDef * buffer){

}

void UART_isr(UART_HandleTypeDef *huart){

}
/********************************************************************************************/


/********************************************************************************************/
Status_TypeDef USART_Init(UART_HandleTypeDef* huart){

	if(huart == NULL) return VIC_ERROR;

	USART_MspInit(huart);

    /*Transfer Mode*/
    huart->Instance->CR1 = huart->Init.Mode;

    /*Set Baudrate*/
    if(huart->Instance == USART1 || huart->Instance == USART6)
		huart->Instance->BRR = USART_Compute_Baud(RCC_GetP2CLK_Freq(),huart->Init.BaudRate);
    else
    	huart->Instance->BRR = USART_Compute_Baud(RCC_GetP1CLK_Freq(),huart->Init.BaudRate);

    /*No of stop Bits*/
    huart->Instance->CR2 |= huart->Init.StopBits;

    /*Word Length*/
    huart->Instance->CR1 |= huart->Init.WordLength;

    /*parity control*/
    huart->Instance->CR1 |= huart->Init.parity;

    /*HWFlow control*/
    huart->Instance->CR3 |= huart->Init.HWFlowCtl;

    /*Over Sampling*/
    huart->Instance->CR1 |= huart->Init.OverSampling;

    /*Enable the usart Instance*/
    huart->Instance->CR1 |= USART_EN;

    NVIC_Enable(USART2_IRQ);
    return VIC_OK;
}

uint16_t USART_Compute_Baud(uint32_t pclk, uint32_t baudrate){
	return ((pclk + (baudrate / 2U)) / baudrate);
}
/********************************************************************************************/


/********************************************************************************************/
int __io_putchar(int ch){
	debug(ch);
	return ch;
}
void debug(int ch){
	while(!(USART2->SR & (1U << 7)));
	USART2->DR = (ch &0xFF);
}
/********************************************************************************************/


/********************************************************************************************/
void __UART_ENABLE_IT_EIE(UART_HandleTypeDef* huart){
	huart->Instance->CR3 |= USART_EIE_EN;
}
void __UART_ENABLE_IT_RXNE(UART_HandleTypeDef* huart){
	huart->Instance->CR1 |= USART_RXNE_EN;
}
/********************************************************************************************/
