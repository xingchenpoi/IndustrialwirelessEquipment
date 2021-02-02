/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Di.h
** 摘    要：

*******************************************************************************/
#ifndef __APP_DI_H
#define __APP_DI_H

/* ----------------------------------头文件-----------------------------------*/
#include "includes.h"


/*-------------------------------外部调用变量声明-----------------------------*/



/*-------------------------------外部调用函数声明-----------------------------*/
extern void DI_Sta_Get(DI_TypeDef *p);
extern void DI_Pulse_Count(DI_TypeDef *p, eDI_CHL chl);
extern void DI_Lanuch(void);

#endif                                                                          //__BSP_H 

/*******************************************************************************
*   版本号        修改日期        修改者        修改内容
*
*******************************************************************************/

/*--------------------------------文件结尾------------------------------------*/
