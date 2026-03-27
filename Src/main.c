/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Srivisweswara
 * @brief          : Main program body
 ******************************************************************************
 **/

#include "main.h"

UART_HandleTypeDef huart2;
CAN_HandleTypeDef hcan1;

Debounce_Handel_t user_btn;

void SystemSetup();
void SystemClock_Config(void);
void M_GPIO_Init(void);
void M_USART2_UART_Init(void);
void Error_Handler(void);

uint8_t cntr=0;

int main(void)
{

 	SystemSetup();

 	SystemClock_Config();

 	M_GPIO_Init();

 	M_USART2_UART_Init();

	while(1){
		GPIO_TogglePin(GPIOA, GPIO_PIN_5);

//		(GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) ?
//		GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_SET):
//		GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_RESET);
		delay(1000);
//		delay(1000);
		printf("Hello World !!\r\n");
	}
 }

void SystemSetup(){
	__RCC_SYSCFG_CLK_ENABLE();
	TimeBase_Init(SYS_DEF_CORE_CLOCK);
}

void SystemClock_Config(void){
	RCC_OscInitTypeDef RCC_OscInitStruct ={0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct ={0};

	/*Enable PWR in APB1 Enable Register*/
	__RCC_PWR_CLK_ENABLE();

	/*SET VOS in SCALE1 Mode in CR register in power*/
	__PWR_VOLTAGESCALING_CONFIG();

	RCC_OscInitStruct.OscillatorType = RCC_OSC_TYPE_HSE;
	RCC_OscInitStruct.HSEState = HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = PLL_HSE_SRC;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;

	if(RCC_OscConfig(&RCC_OscInitStruct) != VIC_OK){
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|
								  RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLOCKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HLCK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HLCK_DIV2;

	if(RCC_ClkConfig(&RCC_ClkInitStruct) != VIC_OK){
		Error_Handler();
	}
}

void M_GPIO_Init(void){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__RCC_GPIOA_CLK_ENABLE();
	__RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin       = GPIO_PIN_5;
	GPIO_InitStruct.Mode      = GPIO_OUTPUT;
	GPIO_InitStruct.OType     = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = GPIO_PIN_13;
	GPIO_InitStruct.Mode      = GPIO_INPUT;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
// 	Debounce_Init(&user_btn, 100);

//	pc13_exti_interrupt(EXTI15_10_IRQ);
}

void M_USART2_UART_Init(void){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = USART_WL_8B;
	huart2.Init.StopBits = USART_STOP_BIT1;
	huart2.Init.parity = USART_PARITY_NONE;
	huart2.Init.Mode = USART_MODE_TX_RX;
	huart2.Init.HWFlowCtl = USART_HWCONTROL_NONE;
	huart2.Init.OverSampling = USART_OverSampling_16;

	USART_Init(&huart2);
}

void M_CAN1_Init(void){

	hcan1.Instance = CAN1;
//	hcan1.Init.Mode = ;
	hcan1.Init.Prescaler = 5;
	hcan1.Init.TimeSegment1 = 15;
	hcan1.Init.TimeSegment2 = 2;
	hcan1.Init.SyncJumpWidth = 1;

	CAN_Init(&hcan1);
}

void Error_Handler(void){
	GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	delay(500);
}
