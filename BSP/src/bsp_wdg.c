/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_wdg.c
** 摘    要：硬件看门狗初始化，定时喂狗

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_wdg.h"





/*******************************************************************************
** 函数原型：void WDG_Bsp_Init(void)
** 函数功能：硬件看门狗板级驱动初始化
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void WDG_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	WDG_CLK_ENABLE();

	GPIO_InitStruct.Pin = WDG_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(WDG_PORT, &GPIO_InitStruct);

}



/*******************************************************************************
** 函数原型：void WDG_Lanuch(void)
** 函数功能：硬件看门狗启动程序
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void WDG_Lanuch(void)
{
	if (APP_TIM_ReadDecounterValue(TIM_WDG) != 0)
		return;

	APP_TIM_StartDecounter(TIM_WDG, 200);

	HAL_GPIO_TogglePin(WDG_PORT, WDG_PIN);
}



/*--------------------------------文件结尾------------------------------------*/

