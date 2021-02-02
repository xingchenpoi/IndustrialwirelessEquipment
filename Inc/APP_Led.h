/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Led.h
** 摘    要：

*******************************************************************************/
#ifndef __APP_LED_H
#define __APP_LED_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode);
	void APP_LED_Comm_OneFlash(void);

#ifdef __cplusplus
}
#endif
#endif /*__APP_LED_H */

/*--------------------------------文件结尾------------------------------------*/

