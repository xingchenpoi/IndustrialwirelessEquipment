/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�bsp_switch.h
** ժ    Ҫ��

*******************************************************************************/
#ifndef __BSP_SWITCH_H
#define __BSP_SWITCH_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	void Switch_Bsp_Init(void);
	uint8_t Switch_DevAddr_Read(void);
	uint8_t Switch_NetAddr_Read(void);

#ifdef __cplusplus
}
#endif
#endif /*__BSP_SWITCH_H */

/*--------------------------------�ļ���β------------------------------------*/

