/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Led.c
** 摘    要：LED状态设置，设置LED通信灯闪烁一次

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "APP_Led.h"





/*******************************************************************************
** 函数原型：void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode)
** 函数功能：LED状态设置
** 输入参数：led   led结构体首地址
			 mode  led模式
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode)
{
	if (mode >= eLED_End_Of_Table)
		return;

	led->mode = mode;

	switch (mode)
	{
		case eLED_FLASH:
			led->isFlash = TRUE;
			break;

		case eLED_ON:
			led->isFlash = FALSE;
			led->Ctrl(TRUE);             //开启
			break;

		case eLED_OFF:
			led->isFlash = FALSE;
			led->Ctrl(FALSE);            //关闭;
			break;

		case eLED_ONE_FLASH:
			led->isFlash = TRUE;
			led->Ctrl(TRUE);             //开启
			APP_TIM_StartDecounter(led->timer, led->flashingCycle);   //开始计时
			break;
	}
}





/*******************************************************************************
** 函数原型：void APP_LED_Comm_OneFlash(void)
** 函数功能：LED通信灯闪烁一次
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_LED_Comm_OneFlash(void)
{
	APP_LED_Set(&dev_ledComm, eLED_ONE_FLASH);
}


/*--------------------------------文件结尾------------------------------------*/
