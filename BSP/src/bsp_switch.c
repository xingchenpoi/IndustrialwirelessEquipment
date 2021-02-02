/* Includes ------------------------------------------------------------------*/
#include "bsp_switch.h"




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
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) << 3;

	return (uint8_t)~addr_tmp;          // 返回地址值：0-255
}
