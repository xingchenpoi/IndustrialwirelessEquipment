/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"





/*******************************************************************************
** 函数原型：void LED_Bsp_Init(s_LED *dev)
** 函数功能：LED板级驱动初始化
** 输入参数：dev LED首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Bsp_Init(s_LED *dev)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //时钟初始化

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	dev->isOpen = TRUE;
}





/*******************************************************************************
** 函数原型：void LED_Bsp_DeInit(s_LED *dev)
** 函数功能：LED板级驱动反初始化
** 输入参数：dev LED首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Bsp_DeInit(s_LED *dev)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //时钟初始化

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	dev->isOpen = FALSE;
}




/*******************************************************************************
** 函数原型：void LED_Entry(s_LED *led)
** 函数功能：LED处理入口
** 输入参数：led LED首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Entry(s_LED *led)
{
	if (led->isOpen == FALSE)                      //LED 没有初始化退出
		return;

	if (led->isFlash == FALSE)					   //LED闪烁使能
		return;

	if (APP_TIM_ReadDecounterValue(TIM_LED) != 0)  //判断计时有没有到
		return;

	APP_TIM_StartDecounter(TIM_LED, LED_BLINK_CYCLE);         //重新开始计时

}





/*******************************************************************************
** 函数原型：void LED_Lanuch(void)
** 函数功能：LED启动函数
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void LED_Lanuch(void)
{
	LED_Entry(&dev_led);
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/