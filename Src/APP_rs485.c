/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_rs485.c
** 摘    要：RS485启动程序,RS485串口设置启动接口

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "APP_rs485.h"





/*******************************************************************************
** 函数原型：void RS485_Lanuch(void)
** 函数功能：RS485启动程序
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void RS485_Lanuch(void)
{
	if (dev_RS485.com->Status.bits.TaskDealFlg == 1)
	{
		dev_RS485.com->Status.bits.TaskDealFlg = 0;

		APP_LED_Comm_OneFlash();                                //通信灯闪烁一次

		dev_RS485.com->TxNum = MODBUS_RTU_Handle(dev_RS485.com->RxBuf,
			dev_RS485.com->RxCnt,
			dev_RS485.com->TxBuf);                              //modbus 解析
		if (dev_RS485.com->TxNum > 0)
		{
			HAL_UART_Transmit_DMA(dev_RS485.com->husart, dev_RS485.com->TxBuf, dev_RS485.com->TxNum);
			delay_ms(1);
		}
	}
}





/*******************************************************************************
** 函数原型：void RS485_SetUartPara_Lanuch(void)
** 函数功能：RS485串口设置启动接口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void RS485_SetUartPara_Lanuch(void)
{
	if (isSetupUart != TRUE)         //如果要设置串口
		return;

	isSetupUart = FALSE;

	Usart_Bsp_Init(COM1, sysConfig.uartPara);  //设置串口
}

/*--------------------------------文件结尾------------------------------------*/
