/* Includes ------------------------------------------------------------------*/
#include "bsp_wdg.h"


/*******************************************************************************
** 函数原型：void WDG_Lanuch(void)
** 函数功能：硬件看门狗启动程序
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void WDG_Lanuch(void)
{
	if (APP_TIM_ReadDecounterValue(TIM_WDG) != 0)
		return;

	APP_TIM_StartDecounter(TIM_WDG, 200);

	HAL_GPIO_TogglePin(WDG_PORT, WDG_PIN);
}