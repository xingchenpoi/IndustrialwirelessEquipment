/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_LED.h
** 摘    要：

*******************************************************************************/
#ifndef __BSP_LED_H
#define __BSP_LED_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"

	void LED_Lanuch(void);
	void LED_Bsp_Init(void);
	void LED_Bsp_DeInit(void);
	void LED_Run_Ctrl(bool onoff);
	void LED_Comm_Ctrl(bool onoff);
#ifdef __cplusplus
}
#endif
#endif /*__BSP_LED_H */
/*--------------------------------文件结尾------------------------------------*/

