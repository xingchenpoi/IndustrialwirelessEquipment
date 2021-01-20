/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：
** 日    期：
** 文件名称：
** 摘    要：

*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/
#include "bsp_Di.h"  

/*-------------------------------- 全局变量 ----------------------------------*/



/*******************************************************************************
** 函数原型：void DI_Bsp_Init(void)
** 函数功能：DI初始化
** 输入参数：无
** 输出参数：无
** 备    注：


*******************************************************************************/
void DI_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	DI0_CLK_ENABLE;
	DI1_CLK_ENABLE;
	DI2_CLK_ENABLE;
	DI3_CLK_ENABLE;

	GPIO_InitStruct.Pin = DI0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DI0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI1_PIN;
	HAL_GPIO_Init(DI1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI2_PIN;
	HAL_GPIO_Init(DI2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI3_PIN;
	HAL_GPIO_Init(DI3_PORT, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 3);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/





