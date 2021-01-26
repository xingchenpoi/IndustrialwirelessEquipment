/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 2, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Channel7;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart2_tx);

    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Channel6;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_NORMAL;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmatx);
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/*******************************************************************************
** 函数原型：void usart_enable(UART_HandleTypeDef *usart, uint8_t *pData, uint16_t Size)
** 函数功能：串口使能
** 输入参数：usart		串口首地址
			 pData		接收数据首地址
			 Size		接收数据长度
** 输出参数：无
** 备    注：
*******************************************************************************/
void usart_enable(UART_HandleTypeDef *usart, uint8_t *pData, uint16_t Size)
{
	__HAL_UART_ENABLE(usart);
	HAL_UART_Receive_DMA(usart, pData, Size);

	__HAL_UART_CLEAR_IDLEFLAG(usart);

	/* 使能idle中断 */
	__HAL_UART_ENABLE_IT(usart, UART_IT_IDLE);

}





/*******************************************************************************
** 函数原型：void usart_enable(UART_HandleTypeDef *usart, uint8_t *pData, uint16_t Size)
** 函数功能：串口使能
** 输入参数：usart		串口首地址
			 pData		接收数据首地址
			 Size		接收数据长度
** 输出参数：无
** 备    注：
*******************************************************************************/
void Usart_Bsp_Init(UART_INDEX com, s_Uart_Para para)
{
	UART_HandleTypeDef* uartHandle = NULL;
	s_Usart *uart_buff = NULL;
	uint16_t rxBuffSize = 0;

	if (!IS_USART_COM(com))   //如果串口编号不对，退出
		return;

	switch (com)
	{
		case COM1:
			uartHandle = &huart1;
			uartHandle->Instance = USART1;
			uart_buff = &s_usart1;
			rxBuffSize = USART1_RX_CNT_MAX;
			break;

		case COM2:
			uartHandle = &huart2;
			uartHandle->Instance = USART2;
			uart_buff = &s_usart2;
			rxBuffSize = USART2_RX_CNT_MAX;
			break;

		default:
			return;
	}

	uartHandle->Init.BaudRate = para.BaudRate;
	uartHandle->Init.WordLength = para.WordLength;
	uartHandle->Init.StopBits = para.StopBits;
	uartHandle->Init.Parity = para.Parity;
	uartHandle->Init.Mode = UART_MODE_TX_RX;
	uartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(uartHandle) != HAL_OK)        //重新初始化
	{
		Error_Handler();
	}

	usart_enable(uartHandle, uart_buff->RxBuf, rxBuffSize);

}





/*******************************************************************************
** 函数原型：void Usart_Para_Set(uint16_t data, s_Uart_Para *para)
** 函数功能：串口参数设置
** 输入参数：data  串口参数
			 para  串口参数首地址
** 输出参数：无
** 备    注：
*******************************************************************************/
void Usart_Para_Set(uint16_t data, s_Uart_Para *para)
{
	uint16_t temp = 0;
	s_Uart_Para tempPara = { 0 };

	temp = data & 0x0fff;    //波特率设置
	switch (temp)
	{
		case 0:
			tempPara.BaudRate = 1200;
			break;

		case 1:
			tempPara.BaudRate = 2400;
			break;

		case 2:
			tempPara.BaudRate = 4800;
			break;

		case 3:
			tempPara.BaudRate = 9600;
			break;

		case 4:
			tempPara.BaudRate = 19200;
			break;

		case 5:
			tempPara.BaudRate = 38400;
			break;

		case 6:
			tempPara.BaudRate = 57600;
			break;

		case 7:
			tempPara.BaudRate = 115200;
			break;

		default:
				return;
	}

	temp = (data >> 12) & 0x03;    //奇偶位设置
	switch (temp)
	{
		case 0:
			tempPara.Parity = UART_PARITY_NONE;
			tempPara.WordLength = UART_WORDLENGTH_8B;
			break;

		case 1:
			tempPara.Parity = UART_PARITY_ODD;
			tempPara.WordLength = UART_WORDLENGTH_9B;
			break;

		case 2:
			tempPara.Parity = UART_PARITY_EVEN;
			tempPara.WordLength = UART_WORDLENGTH_9B;
			break;

		default:
			return;
	}

	temp = (data >> 14)&0x03;    //停止位设置
	switch (temp)
	{
		case 0:
			tempPara.StopBits = UART_STOPBITS_1;
			break;

		case 1:
			tempPara.StopBits = UART_STOPBITS_2;
			break;

		default:
			return;
	}

	if(tempPara.Parity != UART_PARITY_NONE)           //如果校验位不是无校验，则停止位只支持1位停止位
		tempPara.StopBits = UART_STOPBITS_1;
	
	para->BaudRate = tempPara.BaudRate;        //参数赋值
	para->Parity = tempPara.Parity;
	para->StopBits = tempPara.StopBits;
	para->WordLength = tempPara.WordLength;
}




/*******************************************************************************
** 函数原型：uint16_t Usart_Para_Get(s_Uart_Para para)
** 函数功能：串口参数获取
** 输入参数：para  串口参数首地址
** 输出参数：转化成16进制后的参数
** 备    注：
*******************************************************************************/
uint16_t Usart_Para_Get(s_Uart_Para para)
{
	uint16_t ret = 0;

	switch (para.BaudRate)   //波特率
	{
		case 1200:
			ret = 0;
			break;

		case 2400:
			ret = 1;
			break;

		case 4800:
			ret = 2;
			break;

		case 9600:
			ret = 3;
			break;

		case 19200:
			ret = 4;
			break;

		case 38400:
			ret = 5;
			break;

		case 57600:
			ret = 6;
			break;

		case 115200:
			ret = 7;
			break;

		default:
			return 0;
	}

	switch (para.Parity)       //校验位
	{
		case UART_PARITY_NONE:
			ret += 0;
			break;

		case UART_PARITY_ODD:
			ret += 0x1000;
			break;

		case UART_PARITY_EVEN:
			ret += 0x2000;
			break;

		default:
			return 0;
	}

	if(para.StopBits == UART_STOPBITS_2) //停止位
		ret += 0x4000;


	return ret;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
