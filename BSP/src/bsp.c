/* Includes ------------------------------------------------------------------*/
#include "bsp.h"





/*******************************************************************************
** ����ԭ�ͣ�void ConfigPara_SaveData_Read(s_CONFIG *config)
** �������ܣ���������
** ���������config ���ò����׵�ַ
** �����������
** ��    ע��
*******************************************************************************/
void ConfigPara_SaveData_Read(s_CONFIG *config)
{
	//STMFLASH_Read(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG));
}




/*******************************************************************************
** ����ԭ�ͣ�void ConfigPara_SaveData_Write(s_CONFIG *config)
** �������ܣ���������
** ���������config ���ò����׵�ַ
** �����������
** ��    ע��
*******************************************************************************/
void ConfigPara_SaveData_Write(s_CONFIG *config)
{
	//STMFLASH_Write(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG));
}





/*******************************************************************************
** ����ԭ�ͣ�void PARA_Init(s_CONFIG *config)
** �������ܣ�������ʼ��
** ���������config ���ò����׵�ַ
** �����������
** ��    ע��
*******************************************************************************/
void PARA_Init(s_CONFIG *config)
{
	//ConfigPara_SaveData_Read(config);
	//if (config->isSave != TRUE)
	//{
		config->isSave = TRUE;

		config->do_Reboot_sta = 0;

		config->uartPara.BaudRate = 9600;
		config->uartPara.Parity = UART_PARITY_NONE;
		config->uartPara.WordLength = UART_WORDLENGTH_8B;
		config->uartPara.StopBits = UART_STOPBITS_1;

		/*ConfigPara_SaveData_Write(config);*/
	//}

}





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

	PARA_Init(&sysConfig);
	
	MCP3208_Bsp_Init(&dev_mcp3208);
	Usart_Bsp_Init(COM1, sysConfig.uartPara);    //rs485��ʼ��

	devAddr = Switch_DevAddr_Read();   //�豸��ַ��ȡ
	if (devAddr == 0)
		devAddr = 1;
	netAddr = Switch_NetAddr_Read();   //�����ַ��ȡ
	if (netAddr == 0)
		netAddr = 1;

	DO_Reboot_Sta_Set(&dev_do);        //DO�ϵ�״̬����



}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
