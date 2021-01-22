/* Includes ------------------------------------------------------------------*/
#include "APP_Led.h"





/*******************************************************************************
** 函数原型：void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode)
** 函数功能：LED设置
** 输入参数：led   led结构体首地址
			 mode  led模式
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode)
{
	if (mode >= eLED_End_Of_Table)
		return;

	led->mode = mode;

	switch (mode)
	{
	case eLED_FLASH:
		led->isFlash = TRUE;
		led->port = LED_PORT;
		led->pin = LED_PIN;
		break;

	case eLED_ON:
		led->isFlash = FALSE;
		HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_RESET);
		break;

	case eLED_OFF:
		led->isFlash = FALSE;
		HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET);
		break;

	}
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
