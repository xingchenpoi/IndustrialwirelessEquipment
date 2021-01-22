/* Includes ------------------------------------------------------------------*/
#include "APP_Task.h"





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

		dev_RS485.com->TxNum = MODBUS_RTU_Handle(dev_RS485.com->RxBuf,
			dev_RS485.com->RxCnt,
			dev_RS485.com->TxBuf);
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

	Usart_Bsp_Init(COM1,sysConfig.uartPara);  //设置串口
}





/*******************************************************************************
** 函数原型：void APP_Display_Task_Lanuch(void)
** 函数功能：显示任务入口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_Display_Task_Lanuch(void)
{
	LED_Lanuch();
}





/*******************************************************************************
** 函数原型：void APP_Collect_Task_Lanuch(void)
** 函数功能：采集任务处理入口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_Collect_Task_Lanuch(void)
{
	MCP3208_Lanuch();
	DI_Lanuch();
}





/*******************************************************************************
** 函数原型：void APP_Set_Task_Lanuch(void)
** 函数功能：设置任务处理接口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_Set_Task_Lanuch(void)
{
	WDG_Lanuch();
	RS485_SetUartPara_Lanuch();
}





/*******************************************************************************
** 函数原型：void APP_Communication_Lanuch(void)
** 函数功能：通讯处理接口
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void APP_Communication_Lanuch(void)
{
	RS485_Lanuch();
	LORA_Lanuch();
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
