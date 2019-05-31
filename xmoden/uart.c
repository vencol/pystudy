/**
 * @file    uart.c
 * @author  Ferenc Nemeth
 * @date    21 Dec 2018
 * @brief   This module is a layer between the HAL UART functions and my Xmodem protocol.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth
 */

#include "uart.h"

UART_HandleTypeDef huart3;


static void XmodenUartGpioInit(void)
{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//	__HAL_RCC_USART3_CLK_ENABLE();

//	__HAL_RCC_GPIOB_CLK_ENABLE();
//	/**USART3 GPIO Configuration    
//	PB10     ------> USART3_TX
//	PB11     ------> USART3_RX 
//	*/
//	GPIO_InitStruct.Pin = GPIO_PIN_10;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//	GPIO_InitStruct.Pin = GPIO_PIN_11;
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	RCC->APB1ENR  |= RCC_APB1ENR_USART3EN;
	RCC->APB2ENR	|= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH = (GPIOB->CRH & 0xFFFF00FF) | 0x00004B00;
}
void XmodenUartInit(void)
{
	XmodenUartGpioInit();
//  huart3.Instance = USART3;
//  huart3.Init.BaudRate = 115200;
//  huart3.Init.WordLength = UART_WORDLENGTH_8B;
//  huart3.Init.StopBits = UART_STOPBITS_1;
//  huart3.Init.Parity = UART_PARITY_NONE;
//  huart3.Init.Mode = UART_MODE_TX_RX;
//  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart3) != HAL_OK)
//  {
////    Error_Handler();
//  }
	
//	USART3->CR1 &=  ~USART_CR1_UE;
//	
//	USART3->CR2 = (USART3->CR2 & 0xFFFFCFFF) | UART_STOPBITS_1;
//	USART3->CR1 = (USART3->CR1 & 0xFFFF69F3) | (UART_WORDLENGTH_8B | UART_PARITY_NONE | UART_MODE_TX_RX | UART_OVERSAMPLING_16);
//	USART3->CR3 = (USART3->CR3 & 0xFFFFFCFF) | UART_HWCONTROL_NONE;
//	
//  USART3->BRR = UART_BRR_SAMPLING16(HAL_RCC_GetPCLK1Freq(), 921600);
//	
//	USART3->CR2 &= 0xffffb7ff;
//	USART3->CR3 &= 0xffffffd5;	
//	USART3->CR1 |= USART_CR1_UE;
//	
//	USART3->CR1 |= 0x0120;
//	USART3->CR3 |= 0x0001;

	USART3->SR 	= 0x000000C0;
	USART3->BRR = 0x000000D0;
	USART3->CR1 = 0x0000200C;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;
}

//void HAL_UART_MspInit(UART_HandleTypeDef* huart)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  if(huart->Instance==USART3)
//  {
//  /* USER CODE BEGIN USART3_MspInit 0 */

//  /* USER CODE END USART3_MspInit 0 */
//    /* Peripheral clock enable */
//    __HAL_RCC_USART3_CLK_ENABLE();
//  
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    /**USART3 GPIO Configuration    
//    PB10     ------> USART3_TX
//    PB11     ------> USART3_RX 
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_10;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//    GPIO_InitStruct.Pin = GPIO_PIN_11;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /* USER CODE BEGIN USART3_MspInit 1 */

//  /* USER CODE END USART3_MspInit 1 */
//  }

//}

///**
//* @brief UART MSP De-Initialization
//* This function freeze the hardware resources used in this example
//* @param huart: UART handle pointer
//* @retval None
//*/
//void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
//{
//  if(huart->Instance==USART3)
//  {
//  /* USER CODE BEGIN USART3_MspDeInit 0 */

//  /* USER CODE END USART3_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_USART3_CLK_DISABLE();
//  
//    /**USART3 GPIO Configuration    
//    PB10     ------> USART3_TX
//    PB11     ------> USART3_RX 
//    */
//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

//  /* USER CODE BEGIN USART3_MspDeInit 1 */

//  /* USER CODE END USART3_MspDeInit 1 */
//  }

//}

static uint32_t Tickstart=0;
static HAL_StatusTypeDef NEWUART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Tickstart, uint32_t Timeout)
{
  /* Wait until flag is set */
  while( (((USART3->SR & Flag) ==  Flag )? SET : RESET) == Status) 
  {
    /* Check for the Timeout */
    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - Tickstart ) > Timeout))
      {
        /* Disable TXE, RXNE, PE and ERR (Frame error, noise error, overrun error) interrupts for the interrupt process */
        CLEAR_BIT(USART3->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE));
        CLEAR_BIT(USART3->CR3, USART_CR3_EIE);
        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}
HAL_StatusTypeDef NEWHAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint16_t* tmp;
  uint32_t tickstart = 0U;
  
  /* Check that a Tx process is not already ongoing */
	if((pData == NULL) || (Size == 0U))
	{
		return  HAL_ERROR;
	}
	/* Init tickstart for timeout managment */
	tickstart = HAL_GetTick();
	while(Size > 0U)
	{
		Size--;
		{
			if(NEWUART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}
			USART3->DR = (*pData++ & (uint8_t)0xFF);
		}
	}

	if(NEWUART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
	{
		return HAL_TIMEOUT;
	}

	return HAL_OK;
}

HAL_StatusTypeDef NEWHAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  
  /* Check that a Rx process is not already ongoing */
	if((pData == NULL) || (Size == 0U))
	{
		return  HAL_ERROR;
	}

	/* Init tickstart for timeout managment */
	tickstart = HAL_GetTick();

	/* Check the remain data to be received */
	while(Size > 0U)
	{
		Size--;
		{
			if(NEWUART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
			{
				return HAL_TIMEOUT;
			}
			*pData++ = (uint8_t)(USART3->DR & (uint8_t)0x00FF);

		}
	}

	return HAL_OK;
}
/**
 * @brief   Receives data from UART.
 * @param   *data: Array to save the received data.
 * @param   length:  Size of the data.
 * @return  status: Report about the success of the receiving.
 */
uart_status uart_receive(uint8_t *data, uint16_t length)
{
  uart_status status = UART_ERROR;

  if (HAL_OK == NEWHAL_UART_Receive(&huart3, data, length, UART_TIMEOUT))
  {
    status = UART_OK;
  }

  return status;
}

/**
 * @brief   Transmits a string to UART.
 * @param   *data: Array of the data.
 * @return  status: Report about the success of the transmission.
 */
uart_status uart_transmit_str(uint8_t *data)
{
  uart_status status = UART_ERROR;
  uint16_t length = 0u;

  /* Calculate the length. */
  while ('\0' != data[length])
  {
    length++;
  }

  if (HAL_OK == NEWHAL_UART_Transmit(&huart3, data, length, UART_TIMEOUT))
  {
    status = UART_OK;
  }

  return status;
}

/**
 * @brief   Transmits a single char to UART.
 * @param   *data: The char.
 * @return  status: Report about the success of the transmission.
 */
uart_status uart_transmit_ch(uint8_t data)
{
  uart_status status = UART_ERROR;

  /* Make available the UART module. */
//  if (HAL_UART_STATE_TIMEOUT == HAL_UART_GetState(&huart3))
//  {
//    HAL_UART_Abort(&huart3);
//  }

  if (HAL_OK == NEWHAL_UART_Transmit(&huart3, &data, 1u, UART_TIMEOUT))
  {
    status = UART_OK;
  }
  return status;
}
