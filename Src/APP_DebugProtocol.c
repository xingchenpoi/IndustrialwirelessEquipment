/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2013-2015)
** 作    者：viggo
** 日    期：
** 文件名称：APP_Modbus.c
** 摘    要：modbus 处理入口，支持03、06、16功能码

*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/
#include "APP_DebugProtocol.h"											// 头文件  





/*******************************************************************************
** 函数原型：void Protolcol_Parse(s_Usart *com, s_CONFIG *config)
** 函数功能：协议解析
** 输入参数：com    串口首地址
             config 配置参数首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void Protolcol_Parse(s_Usart *com, s_CONFIG *config)
{
	if (strstr((char *)com->RxBuf, "\r\n") == NULL)          //如果不是回车换行，先退出
		return;

	if (strstr((char *)com->RxBuf, "AT\r\n") != NULL)        //AT测试指令
	{
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+VER?\r\n") != NULL)  //查询版本号
	{
		com->TxNum = sprintf((char *)com->TxBuf, "AT+VER?=%s", VERSION);
	}
	else if (strstr((char *)com->RxBuf, "AT+CAIL?\r\n") != NULL) //查询是否进入校准模式
	{
		if (isSetCailPara)
		{
			strcpy((char *)com->TxBuf, "AT+CAIL=1\r\n");      
			com->TxNum = strlen("AT+CAIL=1\r\n");
		}
		else
		{
			strcpy((char *)com->TxBuf, "AT+CAIL=0\r\n");
			com->TxNum = strlen("AT+CAIL=0\r\n");
		}			
	}
	else if (strstr((char *)com->RxBuf, "AT+CAIL=1\r\n") != NULL)//设置进入校准模式
	{
		isSetCailPara = TRUE;
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+CAIL=0\r\n") != NULL) //设置退出校准模式
	{
		isSetCailPara = FALSE;
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+CAILPARA") != NULL)  
	{
		if (strstr((char *)com->RxBuf, "?\r\n") != NULL) //查询校准参数
		{
			com->TxNum = sprintf((char *)com->TxBuf, "AT+CAILPARA=%f,%f\r\n", config->caliPara.A, config->caliPara.B);
		}
		else if (strstr((char *)com->RxBuf, "AT+CAILPARA=") != NULL)  //设置校准参数
		{
			sscanf((char *)com->RxBuf, "AT+CAILPARA=%f,%f\r\n", &config->caliPara.A, &config->caliPara.B);

			dev_mcp3208.para.A = config->caliPara.A;
			dev_mcp3208.para.B = config->caliPara.B;
			ConfigPara_SaveData_Write(config);

			strcpy((char *)com->TxBuf, "OK\r\n");
			com->TxNum = strlen("OK\r\n");
		}	
	}
	else if(strstr((char *)com->RxBuf, "AT+VOLTAGE=") != NULL)
	{
		if (strstr((char *)com->RxBuf, "1") != NULL)
		{
			com->TxNum = sprintf((char *)com->TxBuf, "AT+VOLTAGE=1,%f\r\n", dev_mcp3208.bat[0]);
		}
		else if (strstr((char *)com->RxBuf, "2") != NULL)
		{
			com->TxNum = sprintf((char *)com->TxBuf, "AT+VOLTAGE=2,%f\r\n", dev_mcp3208.bat[1]);
		}
	}


	if (com->TxNum > 0)	
	{
		com->RxCnt = 0;   //解析完成后置零
		HAL_UART_Transmit_DMA(com->husart, com->TxBuf, com->TxNum);
		delay_ms(1);
	}

}

/*--------------------------------文件结尾------------------------------------*/