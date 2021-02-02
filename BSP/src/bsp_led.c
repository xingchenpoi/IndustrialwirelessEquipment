/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�bsp_led.c
** ժ    Ҫ��led �弶������ʼ��,�ƿ��ƣ���˸����

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"





/*******************************************************************************
** ����ԭ�ͣ�void LED_Bsp_Init(void)
** �������ܣ�LED�弶������ʼ��
** ���������dev LED�׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LED_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //ʱ�ӳ�ʼ��
	LED_COMM_CLK_ENABLE();

	LED_L();
	LED_COMM_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_COMM_PIN;
	HAL_GPIO_Init(LED_COMM_PORT, &GPIO_InitStruct);

	dev_led.isOpen = TRUE;
	dev_ledComm.isOpen = TRUE;
}





/*******************************************************************************
** ����ԭ�ͣ�void LED_Bsp_DeInit(void)
** �������ܣ�LED�弶��������ʼ��
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void LED_Bsp_DeInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LED_RED_CLK_ENABLE();           //ʱ�ӳ�ʼ��
	LED_COMM_CLK_ENABLE();            

	LED_L();

	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED_COMM_PIN;
	HAL_GPIO_Init(LED_COMM_PORT, &GPIO_InitStruct);

	dev_led.isOpen = FALSE;
	dev_ledComm.isOpen = FALSE;
}





/*******************************************************************************
** ����ԭ�ͣ�void LED_Run_Ctrl(bool onoff)
** �������ܣ�LED ���еƿ���
** ���������onoff  TRUE ���� FALSE �ر�
** �����������
** ��    ע��

*******************************************************************************/
void LED_Run_Ctrl(bool onoff)
{
	if(onoff)
		LED_H();
	else
		LED_L();
}





/*******************************************************************************
** ����ԭ�ͣ�void LED_Comm_Ctrl(bool onoff)
** �������ܣ�LED ͨ�ŵƿ���
** ���������onoff  TRUE ���� FALSE �ر�
** �����������
** ��    ע��

*******************************************************************************/
void LED_Comm_Ctrl(bool onoff)
{
	if (onoff)
		LED_COMM_H();
	else
		LED_COMM_L();
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

	if (APP_TIM_ReadDecounterValue(led->timer) != 0)  //�жϼ�ʱ��û�е�
		return;

	HAL_GPIO_TogglePin(led->port, led->pin);

	if (led->mode == eLED_ONE_FLASH)               //�����˸Ϊ������˸����رյ�
	{
		led->isFlash = FALSE;
		return;
	}

	APP_TIM_StartDecounter(led->timer, led->flashingCycle);         //���¿�ʼ��ʱ
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
	LED_Entry(&dev_ledComm);
}



/*--------------------------------�ļ���β------------------------------------*/