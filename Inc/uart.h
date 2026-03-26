/*
 * uart.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"



#define UART_BUFFER_SIZE	64
#define UART_PORTS			1

typedef struct{
	unsigned char buffer[UART_BUFFER_SIZE];
	volatile unsigned int head;
	volatile unsigned int tail;
}RingBuffer_TypeDef;

typedef struct{
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t StopBits;
	uint32_t parity;
	uint32_t Mode;
	uint32_t HWFlowCtl;
	uint32_t OverSampling;
}UART_InitTypeDef;

typedef struct{
	uint32_t SR;	// Status register
	uint32_t DR; 	// Data register
	uint32_t BRR; 	// Baud rate register
	uint32_t CR1; 	// Control register 1
	uint32_t CR2; 	// Control register 2
	uint32_t CR3; 	// Control register 3
	uint32_t GTPR; 	// Guard time and prescaler register
}USART_TypeDef;

typedef struct {
	USART_TypeDef		*Instance; /*Chooses Which UART*/
	UART_InitTypeDef	 Init;
}UART_HandleTypeDef;


#define USART_WL_8B					(0x00U)
#define USART_WL_9B					(1U << 0xCU)

#define USART_PARITY_NONE			(0x00U)
#define USART_PARITY_ODD			(1U << 10U)
#define USART_PARITY_EVEN			(USART_PARITY_ODD | 1U << 9U)

#define USART_STOP_BIT1				(0x00U << 0X0CU)
#define USART_STOP_BITf5			(0x1U  << 0x0CU)
#define USART_STOP_BIT2				(0x2U  << 0x0CU)
#define USART_STOP_BIT1f5			(0x3U  << 0x0CU)

#define USART_MODE_TX				(1U << 0x3U)
#define USART_MODE_RX				(1U << 0x2U)
#define USART_MODE_TX_RX			(USART_MODE_TX | USART_MODE_RX)

#define USART_RXNE_EN				(1U << 0x05U)
#define USART_TXNE_EN				(1U << 0x07U)
#define USART_EIE_EN				(1U << 0x00U)

#define USART_EN					(1U << 0x0DU)

#define USART_HWCONTROL_NONE		(0x00U)
#define USART_HWCONTROL_RTS			(1U << 0x08U)
#define USART_HWCONTROL_CTS			(1U << 0x09U)
#define USART_HWCONTROL_RTS_CTS		(UART_HWCONTROL_RTS |UART_HWCONTROL_CTS)

#define USART_OverSampling_16		(0x00U)
#define USART_OverSampling_8		(1U << 0x0FU)

#define USART1 						((USART_TypeDef*) USART1_BASE)
#define USART2						((USART_TypeDef*) USART2_BASE)
#define USART3						((USART_TypeDef*) USART3_BASE)
#define UART4						((USART_TypeDef*) UART4_BASE )
#define UART5						((USART_TypeDef*) UART5_BASE )
#define USART6						((USART_TypeDef*) USART6_BASE)

void USART_Init(UART_HandleTypeDef* huart);
void USART_MspInit(UART_HandleTypeDef* huart);
uint16_t USART_Compute_Baud(uint32_t pclk, uint32_t baudrate);
void debug(int ch);

/*Ring Buffer Setup*/

/*Initialize the Ring Buffer*/
void RingBuffer_Init(void);

/*Recieve data from UART*/
void UART_Recieve(void);

/*Transmit data from UART*/
void UART_Transmit(int c);

void UART_Transmit(int c);

void UART_isr (UART_HandleTypeDef *huart);


void __UART_ENABLE_IT_EIE(UART_HandleTypeDef* huart);
void __UART_ENABLE_IT_RXNE(UART_HandleTypeDef* huart);

#endif /* UART_H_ */
