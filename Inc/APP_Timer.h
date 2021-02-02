/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Timer.h
** 摘    要：

*******************************************************************************/
#ifndef __APP_TIMER_H
#define __APP_TIMER_H


/* ----------------------------------头文件-----------------------------------*/
#include "includes.h"




/*-------------------------------外部调用函数声明-----------------------------*/
extern void APP_TIM_Launch(void);
extern uint16_t APP_TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern uint16_t APP_TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern void APP_TIM_StartCounter(e_TIM_TABLE_ID offset_table);
extern void APP_TIM_StartDecounter(e_TIM_TABLE_ID offset_table, uint32_t value);
extern void APP_TIM_StopDecounter(e_TIM_TABLE_ID offset_table);
extern void APP_TIM_StopCounter(e_TIM_TABLE_ID offset_table);
extern bool APP_TIM_ReadCntOrDecntActivate(e_TIM_TABLE_ID offset_table);

#endif //__APP_LED_H 

/*******************************************************************************
*   版本号        修改日期        修改者        修改内容
*
*******************************************************************************/


/*--------------------------------文件结尾------------------------------------*/


