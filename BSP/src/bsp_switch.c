/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_switch.c
** 摘    要：拨码开关初始化，设备地址读取、网络地址读取

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_switch.h"



/*******************************************************************************
** 函数原型：void Switch_Bsp_Init(void)
** 函数功能：拨码开关初始化
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void Switch_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PA7 PA8 PA11 PA12
						 PA15 */
	//GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12
	//	| GPIO_PIN_15;
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB10 PB11
							 PB3 PB4 PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11
		| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}





/*******************************************************************************
** 函数原型：uint8_t Switch_DevAddr_Read(void)
** 函数功能：设备地址读取
** 输入参数：无
** 输出参数：设备地址
** 备    注：

*******************************************************************************/
uint8_t Switch_DevAddr_Read(void)
{
	uint8_t addr_tmp = 0;								// 临时地址

	// 读数    	
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) ;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) << 1;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)  << 2;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) << 3;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) << 4;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)  << 5;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)  << 6;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)  << 7;

	return (uint8_t)~addr_tmp;          // 返回地址值：0-255
}





/*******************************************************************************
** 函数原型：uint8_t Switch_NetAddr_Read(void)
** 函数功能：网络地址读取
** 输入参数：无
** 输出参数：网络地址
** 备    注：

*******************************************************************************/
uint8_t Switch_NetAddr_Read(void)
{
	uint8_t addr_tmp = 0xF0;								// 临时地址

		// 读数
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) << 1;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) << 2;
	//addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) << 3;
	addr_tmp |= 1 << 3;

	return (uint8_t)~addr_tmp;          // 返回地址值：0-255
}


/*--------------------------------文件结尾------------------------------------*/