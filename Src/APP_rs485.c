/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�APP_rs485.c
** ժ    Ҫ��RS485��������,RS485�������������ӿ�

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "APP_rs485.h"





/*******************************************************************************
** ����ԭ�ͣ�void RS485_Lanuch(void)
** �������ܣ�RS485��������
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void RS485_Lanuch(void)
{
	if (dev_RS485.com->Status.bits.TaskDealFlg == 1)
	{
		dev_RS485.com->Status.bits.TaskDealFlg = 0;

		APP_LED_Comm_OneFlash();                                //ͨ�ŵ���˸һ��

		Protolcol_Parse(dev_RS485.com, &sysConfig);

		if (dev_RS485.com->RxCnt == 0)
			return;

		dev_RS485.com->TxNum = MODBUS_RTU_Handle(dev_RS485.com->RxBuf,
			dev_RS485.com->RxCnt,
			dev_RS485.com->TxBuf);                              //modbus ����
		if (dev_RS485.com->TxNum > 0)
		{
			HAL_UART_Transmit_DMA(dev_RS485.com->husart, dev_RS485.com->TxBuf, dev_RS485.com->TxNum);
			delay_ms(1);
		}
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void RS485_SetUartPara_Lanuch(void)
** �������ܣ�RS485�������������ӿ�
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void RS485_SetUartPara_Lanuch(void)
{
	if (isSetupUart != TRUE)         //���Ҫ���ô���
		return;

	isSetupUart = FALSE;

	Usart_Bsp_Init(COM1, sysConfig.uartPara);  //���ô���
}

/*--------------------------------�ļ���β------------------------------------*/