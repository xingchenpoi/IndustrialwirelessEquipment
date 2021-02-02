/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_led.c
** 摘    要：led 板级驱动初始化,灯控制，闪烁处理

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"





/*******************************************************************************
** 函数原型：void LED_Bsp_Init(void)
** 函数功能：LED板级驱动初始化
** 输入参数：dev LED首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //时钟初始化
	LED_COMM_CLK_ENABLE();

	LED_L();
	LED_COMM_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_COMM_PIN;
	HAL_GPIO_Init(LED_COMM_PORT, &GPIO_InitStruct);

	dev_led.isOpen = TRUE;
	dev_ledComm.isOpen = TRUE;
}





/*******************************************************************************
** 函数原型：void LED_Bsp_DeInit(void)
** 函数功能：LED板级驱动反初始化
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Bsp_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //时钟初始化
	LED_COMM_CLK_ENABLE();            

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_COMM_PIN;
	HAL_GPIO_Init(LED_COMM_PORT, &GPIO_InitStruct);

	dev_led.isOpen = FALSE;
	dev_ledComm.isOpen = FALSE;
}





/*******************************************************************************
** 函数原型：void LED_Run_Ctrl(bool onoff)
** 函数功能：LED 运行灯控制
** 输入参数：onoff  TRUE 开启 FALSE 关闭
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Run_Ctrl(bool onoff)
{
	if(onoff)
		LED_H();
	else
		LED_L();
}





/*******************************************************************************
** 函数原型：void LED_Comm_Ctrl(bool onoff)
** 函数功能：LED 通信灯控制
** 输入参数：onoff  TRUE 开启 FALSE 关闭
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Comm_Ctrl(bool onoff)
{
	if (onoff)
		LED_COMM_H();
	else
		LED_COMM_L();
}




/*******************************************************************************
** 函数原型：void LED_Entry(s_LED *led)
** 函数功能：LED处理入口
** 输入参数：led LED首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Entry(s_LED *led)
{
	if (led->isOpen == FALSE)                      //LED 没有初始化退出
		return;

	if (led->isFlash == FALSE)					   //LED闪烁使能
		return;

	if (APP_TIM_ReadDecounterValue(led->timer) != 0)  //判断计时有没有到
		return;

	HAL_GPIO_TogglePin(led->port, led->pin);

	if (led->mode == eLED_ONE_FLASH)               //如果闪烁为单次闪烁，则关闭灯
	{
		led->isFlash = FALSE;
		return;
	}

	APP_TIM_StartDecounter(led->timer, led->flashingCycle);         //重新开始计时
}





/*******************************************************************************
** 函数原型：void LED_Lanuch(void)
** 函数功能：LED启动函数
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Lanuch(void)
{
	LED_Entry(&dev_led);
	LED_Entry(&dev_ledComm);
}



/*--------------------------------文件结尾------------------------------------*/