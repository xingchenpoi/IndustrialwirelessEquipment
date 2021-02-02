/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_switch.h
** 摘    要：

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

/*--------------------------------文件结尾------------------------------------*/

