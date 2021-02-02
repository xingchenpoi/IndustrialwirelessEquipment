/* Includes ------------------------------------------------------------------*/
#include "APP_Led.h"





/*******************************************************************************
** ����ԭ�ͣ�void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode)
** �������ܣ�LED����
** ���������led   led�ṹ���׵�ַ
			 mode  ledģʽ
** �����������
** ��    ע��

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
			break;

		case eLED_ON:
			led->isFlash = FALSE;
			led->Ctrl(TRUE);             //����
			break;

		case eLED_OFF:
			led->isFlash = FALSE;
			led->Ctrl(FALSE);            //�ر�;
			break;

		case eLED_ONE_FLASH:
			led->isFlash = TRUE;
			led->Ctrl(TRUE);             //����
			APP_TIM_StartDecounter(led->timer, led->flashingCycle);   //��ʼ��ʱ
			break;
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void APP_LED_Comm_OneFlash(void)
** �������ܣ�LEDͨ�ŵ���˸һ��
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void APP_LED_Comm_OneFlash(void)
{
	APP_LED_Set(&dev_ledComm, eLED_ONE_FLASH);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
