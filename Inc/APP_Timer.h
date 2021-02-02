/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�APP_Timer.h
** ժ    Ҫ��

*******************************************************************************/
#ifndef __APP_TIMER_H
#define __APP_TIMER_H


/* ----------------------------------ͷ�ļ�-----------------------------------*/
#include "includes.h"




/*-------------------------------�ⲿ���ú�������-----------------------------*/
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
*   �汾��        �޸�����        �޸���        �޸�����
*
*******************************************************************************/


/*--------------------------------�ļ���β------------------------------------*/


