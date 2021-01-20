/* Includes ------------------------------------------------------------------*/
#include "bsp.h"


/*******************************************************************************
** ����ԭ�ͣ�void Bsp_Init(void)
** �������ܣ�������ʼ��
** �����������
** �����������
** ��    ע��
 *******************************************************************************/
void Bsp_Init(void)
{
	delay_init(64);               		//��ʼ����ʱ����
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	usart_enable(&huart1, s_usart1.RxBuf, USART1_RX_CNT_MAX);
	usart_enable(&huart2, s_usart2.RxBuf, USART2_RX_CNT_MAX);
	
	MCP3208_Bsp_Init(&dev_mcp3208);

	devAddr = Switch_DevAddr_Read();   //�豸��ַ��ȡ
	if (devAddr == 0)
		devAddr = 1;
	netAddr = Switch_NetAddr_Read();   //�����ַ��ȡ
	if (netAddr == 0)
		netAddr = 1;

	DO_Reboot_Sta_Set(&dev_do);        //DO�ϵ�״̬����
}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
