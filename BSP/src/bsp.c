/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�bsp.c
** ժ    Ҫ���弶��������

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"



//uint16_t size = 0;

/*******************************************************************************
** ����ԭ�ͣ�void ConfigPara_SaveData_Read(s_CONFIG *config)
** �������ܣ���������
** ���������config ���ò����׵�ַ
** �����������
** ��    ע��
*******************************************************************************/
void ConfigPara_SaveData_Read(s_CONFIG *config)
{
	STMFLASH_Read(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG)/2);
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
	STMFLASH_Write(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG)/2);
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
	ConfigPara_SaveData_Read(config);
	if (config->isSave != TRUE)
	{
		config->isSave = TRUE;

		config->do_Reboot_sta = 0;

		config->uartPara.BaudRate = 9600;
		config->uartPara.Parity = UART_PARITY_NONE;
		config->uartPara.WordLength = UART_WORDLENGTH_8B;
		config->uartPara.StopBits = UART_STOPBITS_1;

		ConfigPara_SaveData_Write(config);
	}
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
	MX_DMA_Init();
	MX_TIM3_Init();

	delay_init(64);               		//��ʼ����ʱ����
	HAL_TIM_Base_Start_IT(&htim3);
	
	PARA_Init(&sysConfig);

	LED_Bsp_Init();                    //LED��ʼ��
	
	MCP3208_Bsp_Init(&dev_mcp3208);    //AI��ʼ��
	RS485_Bsp_Init();                  //RS485��ʼ��
	LORA_Bsp_Init();                   //LoRa��ʼ��

	Switch_Bsp_Init();                 //���뿪�س�ʼ��
	devAddr = Switch_DevAddr_Read();   //�豸��ַ��ȡ
	if (devAddr == 0)
		devAddr = 1;
	netAddr = Switch_NetAddr_Read();   //�����ַ��ȡ
	if (netAddr == 0)
		netAddr = 1;

	DO_Bsp_Init();                     //DO��ʼ��
	dev_do.reboot_sta[0] = sysConfig.do_Reboot_sta;   //��ȡ��ʼ��״̬
	DO_Reboot_Sta_Set(&dev_do);        //DO�ϵ�״̬����

	DI_Bsp_Init();                     //DI��ʼ��

	WDG_Bsp_Init();                    //Ӳ�����Ź���ʼ��
}





/*--------------------------------�ļ���β------------------------------------*/
