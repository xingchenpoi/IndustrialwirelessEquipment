/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"





/*******************************************************************************
** ����ԭ�ͣ�void LED_Bsp_Init(s_LED *dev)
** �������ܣ�LED�弶������ʼ��
** ���������dev LED�׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LED_Bsp_Init(s_LED *dev)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //ʱ�ӳ�ʼ��

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	dev->isOpen = TRUE;
}





/*******************************************************************************
** ����ԭ�ͣ�void LED_Bsp_DeInit(s_LED *dev)
** �������ܣ�LED�弶��������ʼ��
** ���������dev LED�׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LED_Bsp_DeInit(s_LED *dev)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //ʱ�ӳ�ʼ��

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	dev->isOpen = FALSE;
}




/*******************************************************************************
** ����ԭ�ͣ�void LED_Entry(s_LED *led)
** �������ܣ�LED�������
** ���������led LED�׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LED_Entry(s_LED *led)
{
	if (led->isOpen == FALSE)                      //LED û�г�ʼ���˳�
		return;

	if (led->isFlash == FALSE)					   //LED��˸ʹ��
		return;

	if (APP_TIM_ReadDecounterValue(TIM_LED) != 0)  //�жϼ�ʱ��û�е�
		return;

	APP_TIM_StartDecounter(TIM_LED, LED_BLINK_CYCLE);         //���¿�ʼ��ʱ

}





/*******************************************************************************
** ����ԭ�ͣ�void LED_Lanuch(void)
** �������ܣ�LED��������
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void LED_Lanuch(void)
{
	LED_Entry(&dev_led);
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/