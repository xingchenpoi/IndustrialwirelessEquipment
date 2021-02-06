/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2013-2015)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�APP_Modbus.c
** ժ    Ҫ��modbus ������ڣ�֧��03��06��16������

*******************************************************************************/
/*--------------------------------- ͷ�ļ� -----------------------------------*/
#include "APP_DebugProtocol.h"											// ͷ�ļ�  





/*******************************************************************************
** ����ԭ�ͣ�void Protolcol_Parse(s_Usart *com, s_CONFIG *config)
** �������ܣ�Э�����
** ���������com    �����׵�ַ
             config ���ò����׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void Protolcol_Parse(s_Usart *com, s_CONFIG *config)
{
	if (strstr((char *)com->RxBuf, "\r\n") == NULL)          //������ǻس����У����˳�
		return;

	if (strstr((char *)com->RxBuf, "AT\r\n") != NULL)        //AT����ָ��
	{
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+VER?\r\n") != NULL)  //��ѯ�汾��
	{
		com->TxNum = sprintf((char *)com->TxBuf, "AT+VER?=%s", VERSION);
	}
	else if (strstr((char *)com->RxBuf, "AT+CAIL?\r\n") != NULL) //��ѯ�Ƿ����У׼ģʽ
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
	else if (strstr((char *)com->RxBuf, "AT+CAIL=1\r\n") != NULL)//���ý���У׼ģʽ
	{
		isSetCailPara = TRUE;
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+CAIL=0\r\n") != NULL) //�����˳�У׼ģʽ
	{
		isSetCailPara = FALSE;
		strcpy((char *)com->TxBuf, "OK\r\n");
		com->TxNum = strlen("OK\r\n");
	}
	else if (strstr((char *)com->RxBuf, "AT+CAILPARA") != NULL)  
	{
		if (strstr((char *)com->RxBuf, "?\r\n") != NULL) //��ѯУ׼����
		{
			com->TxNum = sprintf((char *)com->TxBuf, "AT+CAILPARA=%f,%f\r\n", config->caliPara.A, config->caliPara.B);
		}
		else if (strstr((char *)com->RxBuf, "AT+CAILPARA=") != NULL)  //����У׼����
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
		com->RxCnt = 0;   //������ɺ�����
		HAL_UART_Transmit_DMA(com->husart, com->TxBuf, com->TxNum);
		delay_ms(1);
	}

}

/*--------------------------------�ļ���β------------------------------------*/