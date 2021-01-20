/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：
** 日    期：
** 文件名称：APP_DataHandle.c
** 摘    要：串口处理接口

*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/
#include "APP_Timer.h"                                                         // 头文件                                                          


/*--------------------------------- 常量 ------------------------------------*/

const uint8_t cTIM_TimePeriodMs = PERIOD_OF_TIM_LAUNCH_CALL;

/*--------------------------------- 变量 ------------------------------------*/
t_TIM_TAB_DEF_ELEMENT TIM_TableOfCntAndDecnt[end_of_table_cnt_decnt];


/*-------------------------------- 函数声明 ---------------------------------*/



/*******************************************************************************
** 函数原型：void APP_TIM_Launch(void)
** 函数功能：计时入口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_TIM_Launch(void)
{
	uint8_t i = 0;
	for (i = 0; i < end_of_table_cnt_decnt; i++)
	{
		if (TIM_TableOfCntAndDecnt[i].activate == TRUE)
		{
			if (TIM_TableOfCntAndDecnt[i].type == DECOUNT)
			{
				if (TIM_TableOfCntAndDecnt[i].value >= cTIM_TimePeriodMs)
				{
					TIM_TableOfCntAndDecnt[i].value -= cTIM_TimePeriodMs;
				}
				else
				{
					TIM_TableOfCntAndDecnt[i].value = 0;
				}
			}
			else
			{
				TIM_TableOfCntAndDecnt[i].value += cTIM_TimePeriodMs;
			}
		}
	}

}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/




/*******************************************************************************
** 函数原型：uint16_t APP_TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table)
** 函数功能：读取当前计时（加法）
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
uint16_t APP_TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table)
{
	return (TIM_TableOfCntAndDecnt[offset_table].value);
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：uint16_t APP_TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table)
** 函数功能：读取当前计时(减法)
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
uint16_t APP_TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table)
{
	return (TIM_TableOfCntAndDecnt[offset_table].value);
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：void APP_TIM_StartCounter(e_TIM_TABLE_ID offset_table)
** 函数功能：开始当前计时
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_TIM_StartCounter(e_TIM_TABLE_ID offset_table)
{
	TIM_TableOfCntAndDecnt[offset_table].type = COUNT;
	TIM_TableOfCntAndDecnt[offset_table].value = 0;
	TIM_TableOfCntAndDecnt[offset_table].activate = TRUE;
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：void APP_TIM_StartDecounter(e_TIM_TABLE_ID offset_table, uint32_t value)
** 函数功能：开始当前计时(减法)
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_TIM_StartDecounter(e_TIM_TABLE_ID offset_table, uint32_t value)
{
	TIM_TableOfCntAndDecnt[offset_table].type = DECOUNT;
	TIM_TableOfCntAndDecnt[offset_table].value = value;
	TIM_TableOfCntAndDecnt[offset_table].activate = TRUE;
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：void APP_TIM_StopDecounter(e_TIM_TABLE_ID offset_table)
** 函数功能：停止当前计时(减法)
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_TIM_StopDecounter(e_TIM_TABLE_ID offset_table)
{
	TIM_TableOfCntAndDecnt[offset_table].type = DECOUNT;
	TIM_TableOfCntAndDecnt[offset_table].value = 1;
	TIM_TableOfCntAndDecnt[offset_table].activate = FALSE;
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：void APP_TIM_StopCounter(e_TIM_TABLE_ID offset_table)
** 函数功能：停止当前计时(加法)
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_TIM_StopCounter(e_TIM_TABLE_ID offset_table)
{
	TIM_TableOfCntAndDecnt[offset_table].type = COUNT;
	TIM_TableOfCntAndDecnt[offset_table].value = 0;
	TIM_TableOfCntAndDecnt[offset_table].activate = FALSE;
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





/*******************************************************************************
** 函数原型：bool APP_TIM_ReadCntOrDecntActivate(e_TIM_TABLE_ID offset_table)
** 函数功能：获取计时任务是否激活数值
** 输入参数：无
** 输出参数：FALSE 未激活 TRUE 已激活
** 备    注：

*******************************************************************************/
bool APP_TIM_ReadCntOrDecntActivate(e_TIM_TABLE_ID offset_table)
{
	return (TIM_TableOfCntAndDecnt[offset_table].activate);
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/

/*--------------------------------文件结尾------------------------------------*/