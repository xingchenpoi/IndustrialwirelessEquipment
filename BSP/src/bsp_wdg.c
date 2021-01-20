/* Includes ------------------------------------------------------------------*/
#include "bsp_wdg.h"


/*******************************************************************************
** ����ԭ�ͣ�void WDG_Lanuch(void)
** �������ܣ�Ӳ�����Ź���������
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void WDG_Lanuch(void)
{
	if (APP_TIM_ReadDecounterValue(TIM_WDG) != 0)
		return;

	APP_TIM_StartDecounter(TIM_WDG, 200);

	HAL_GPIO_TogglePin(WDG_PORT, WDG_PIN);
}