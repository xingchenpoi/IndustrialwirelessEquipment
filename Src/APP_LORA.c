/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�APP_LORA.c
** ժ    Ҫ��LORA�弶������ʼ����LORA��������

*******************************************************************************/
/*--------------------------------- ͷ�ļ� -----------------------------------*/  
#include "APP_LORA.h"                                                                // ϵͳ�װ����ú���ͷ�ļ�                                                          



//=========================�궨��==================================
#define LORA_AT                          "AT\r\n\0"                             //AT����ָ��
#define LORA_BRATE                       "AT+BRATE=03\r\n\0"                    //���ô��ڲ����� 9600bps
#define LORA_NET                         "AT+NET=00\r\n\0"                      //��������ģʽ ��Ե�
#define LORA_AK                          "AT+AK=11223344556677889900112233445500\r\n\0" //���� AES ��Կ:11223344556677889900112233445566
#define LORA_MODE                        "AT+MODE=01\r\n\0"                     //���õ���ģʽ
#define LORA_TPREM                       "AT+TPREM=0008\r\n\0"                  //���÷���ǰ���볤��Ϊ8 
#define LORA_RPREM                       "AT+RPREM=01F4\r\n\0"                  //���ý���ǰ���볤��Ϊ500 
#define LORA_LDR                         "AT+LDR=00\r\n\0"                      //���õ������Ż�
#define LORA_SYNC                        "AT+SYNC=12\r\n\0"                     //����ͬ����
#define LORA_POW                         "AT+POW=14\r\n\0"                      //���÷��͹���
#define LORA_BW                          "AT+BW=07\r\n\0"                       //���ô��� 125K
#define LORA_CR                          "AT+CR=01\r\n\0"                       //���ñ�������  4/5
#define LORA_CRC                         "AT+CRC=00\r\n\0"                       //��CRC
#define LORA_TFREQ                       "AT+TFREQ=18AA1640\r\n\0"              //���÷���Ƶ�� 472MHz
#define LORA_RFREQ                       "AT+RFREQ=18AA1640\r\n\0"              //���ý���Ƶ�� 472MHz
#define LORA_TSF                         "AT+TSF=09\r\n\0"                      //���÷�����Ƶ���� 9
#define LORA_RSF                         "AT+RSF=09\r\n\0"                      //���ý�����Ƶ���� 9
#define LORA_TIQ                         "AT+TIQ=00\r\n\0"                      //���÷����ز�����ת 00:OFF
#define LORA_RIQ                         "AT+RIQ=00\r\n\0"                      //���ý����ز�����ת 00:OFF    
#define LORA_SIP                         "AT+SIP=00\r\n\0"                      //������ż�Э�鹦�� 00:�ر�
#define LORA_LCP                         "AT+LCP=0000\r\n\0"                    //������·�������  �ر�
#define LORA_TYPE                        "AT+TYPE=00\r\n\0"                     //����������ݸ�ʽ   00:͸��
#define LORA_RX_ON						 "AT+RX=01\r\n\0"                       //�������ղ���ģʽ
#define LORA_RX_OFF						 "AT+RX=00\r\n\0"                       //�رս��ղ���ģʽ

#define LORA_CFG                         "AT+CFG?\r\n\0"

#define LORA_AT_AK						 "AT+AK=112233445566778899001122334455" // ���÷�����Կ
#define LORA_AT_TFREQ                    "AT+TFREQ="                            // ���÷���Ƶ��ָ��
#define LORA_AT_RFREQ                    "AT+RFREQ="                            // ���ý���Ƶ��ָ��



//loraģ���Ƶ�㶨�壬470.1,470.3,...  ,489.9MHz ��ÿ��Ƶ����200kHz
//��һ���ŵ��������ŵ�  99��ͨ���ŵ���1�������ŵ�(0)
const char LoRa_Freqs[100][9] = { "1C052820\0", "1C083560\0", "1C0B42A0\0", "1C0E4FE0\0",
"1C115D20\0", "1C146A60\0", "1C1777A0\0", "1C1A84E0\0", "1C1D9220\0", "1C209F60\0", "1C23ACA0\0",
"1C26B9E0\0", "1C29C720\0", "1C2CD460\0", "1C2FE1A0\0", "1C32EEE0\0", "1C35FC20\0", "1C390960\0",
"1C3C16A0\0", "1C3F23E0\0", "1C423120\0", "1C453E60\0", "1C484BA0\0", "1C4B58E0\0", "1C4E6620\0",
"1C517360\0", "1C5480A0\0", "1C578DE0\0", "1C5A9B20\0", "1C5DA860\0", "1C60B5A0\0", "1C63C2E0\0",
"1C66D020\0", "1C69DD60\0", "1C6CEAA0\0", "1C6FF7E0\0", "1C730520\0", "1C761260\0", "1C791FA0\0",
"1C7C2CE0\0", "1C7F3A20\0", "1C824760\0", "1C8554A0\0", "1C8861E0\0", "1C8B6F20\0", "1C8E7C60\0",
"1C9189A0\0", "1C9496E0\0", "1C97A420\0", "1C9AB160\0", "1C9DBEA0\0", "1CA0CBE0\0", "1CA3D920\0",
"1CA6E660\0", "1CA9F3A0\0", "1CAD00E0\0", "1CB00E20\0", "1CB31B60\0", "1CB628A0\0", "1CB935E0\0",
"1CBC4320\0", "1CBF5060\0", "1CC25DA0\0", "1CC56AE0\0", "1CC87820\0", "1CCB8560\0", "1CCE92A0\0",
"1CD19FE0\0", "1CD4AD20\0", "1CD7BA60\0", "1CDAC7A0\0", "1CDDD4E0\0", "1CE0E220\0", "1CE3EF60\0",
"1CE6FCA0\0", "1CEA09E0\0", "1CED1720\0", "1CF02460\0", "1CF331A0\0", "1CF63EE0\0", "1CF94C20\0",
"1CFC5960\0", "1CFF66A0\0", "1D0273E0\0", "1D058120\0", "1D088E60\0", "1D0B9BA0\0", "1D0EA8E0\0",
"1D11B620\0", "1D14C360\0", "1D17D0A0\0", "1D1ADDE0\0", "1D1DEB20\0", "1D20F860\0", "1D2405A0\0",
"1D2712E0\0", "1D2A2020\0", "1D2D2D60\0", "1D303AA0\0", "1D3347E0\0" };







/*----------------------------- �ڲ��������� ---------------------------------*/ 




/*******************************************************************************
** ����ԭ�ͣ�void LORA_Bsp_Init(void)
** �������ܣ�LORA�弶������ʼ��
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void LORA_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LORA_AT_CLK_ENABLE();
	LORA_WP_CLK_ENABLE();
	LORA_RST_CLK_ENABLE();

	GPIO_InitStruct.Pin = LORA_AT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LORA_AT_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LORA_WP_PIN;
	HAL_GPIO_Init(LORA_WP_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LORA_RST_PIN;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(LORA_WP_PORT, &GPIO_InitStruct);


	MX_USART2_UART_Init();
	usart_enable(&huart2, s_usart2.RxBuf, USART2_RX_CNT_MAX);
}




/*******************************************************************************
** ����ԭ�ͣ�void LORA_StartUp_Handle(s_LORA *lora)
** �������ܣ�LORA��������
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_StartUp_Handle(s_LORA *lora)
{
	LORA_RST_HIGH();          //��λ������
	delay_ms(10);

	LORA_AT_MODE();           // AT�����ߣ�AT����ģʽ

	LORA_WP_HIGH();
	delay_ms(10);
	LORA_WP_LOW();
	delay_ms(10);

	delay_ms(50);

	lora->state = eLORA_SOFT_INIT;
	lora->com_state = COM_NONE;
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_AtCmd_Pack(s_LORA *lora)
** �������ܣ�AT�������ݴ��
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_AtCmd_Pack(s_LORA *lora)
{
	char temp[3] = { 0 };

	switch (lora->at_cmd)
	{
		case LORA_AT_CMD_AT:
			memcpy(lora->com->TxBuf, LORA_AT, strlen(LORA_AT));
			lora->com->TxNum = strlen(LORA_AT);
			break;

		case LORA_AT_CMD_BRATE:
			memcpy(lora->com->TxBuf, LORA_BRATE, strlen(LORA_BRATE));
			lora->com->TxNum = strlen(LORA_BRATE);
			break;

		case LORA_AT_CMD_NET:
			memcpy(lora->com->TxBuf, LORA_NET, strlen(LORA_NET));
			lora->com->TxNum = strlen(LORA_NET);
			break;

		case LORA_AT_CMD_AK:
			sprintf(temp, "%02X", netAddr);
			strcpy((char *)lora->com->TxBuf, LORA_AT_AK);
			strcat((char *)lora->com->TxBuf, temp);
			strcat((char *)lora->com->TxBuf, "\r\n");
			lora->com->TxNum = strlen((char *)lora->com->TxBuf);
			break;

		case LORA_AT_CMD_MODE:
			memcpy(lora->com->TxBuf, LORA_MODE, strlen(LORA_MODE));
			lora->com->TxNum = strlen(LORA_MODE);
			break;

		case LORA_AT_CMD_TPREM:
			memcpy(lora->com->TxBuf, LORA_TPREM, strlen(LORA_TPREM));
			lora->com->TxNum = strlen(LORA_TPREM);
			break;

		case LORA_AT_CMD_RPREM:
			memcpy(lora->com->TxBuf, LORA_RPREM, strlen(LORA_RPREM));
			lora->com->TxNum = strlen(LORA_RPREM);
			break;

		case LORA_AT_CMD_LDR:
			memcpy(lora->com->TxBuf, LORA_LDR, strlen(LORA_LDR));
			lora->com->TxNum = strlen(LORA_LDR);
			break;

		case LORA_AT_CMD_SYNC:
			memcpy(lora->com->TxBuf, LORA_SYNC, strlen(LORA_SYNC));
			lora->com->TxNum = strlen(LORA_SYNC);
			break;

		case LORA_AT_CMD_POW:
			memcpy(lora->com->TxBuf, LORA_POW, strlen(LORA_POW));
			lora->com->TxNum = strlen(LORA_POW);
			break;

		case LORA_AT_CMD_BW:
			memcpy(lora->com->TxBuf, LORA_BW, strlen(LORA_BW));
			lora->com->TxNum = strlen(LORA_BW);
			break;

		case LORA_AT_CMD_CR:
			memcpy(lora->com->TxBuf, LORA_CR, strlen(LORA_CR));
			lora->com->TxNum = strlen(LORA_CR);
			break;

		case LORA_AT_CMD_CRC:
			memcpy(lora->com->TxBuf, LORA_CRC, strlen(LORA_CRC));
			lora->com->TxNum = strlen(LORA_CRC);
			break;

		case LORA_AT_CMD_TFREQ:
			strcpy((char *)lora->com->TxBuf, LORA_AT_TFREQ);
			strcat((char *)lora->com->TxBuf, &LoRa_Freqs[devAddr % 100][0]);
			strcat((char *)lora->com->TxBuf, "\r\n");
			lora->com->TxNum = strlen((char *)lora->com->TxBuf);
			break;

		case LORA_AT_CMD_RFREQ:
			strcpy((char *)lora->com->TxBuf, LORA_AT_RFREQ);
			strcat((char *)lora->com->TxBuf, &LoRa_Freqs[devAddr % 100][0]);
			strcat((char *)lora->com->TxBuf, "\r\n");
			lora->com->TxNum = strlen((char *)lora->com->TxBuf);
			break;

		case LORA_AT_CMD_TSF:
			memcpy(lora->com->TxBuf, LORA_TSF, strlen(LORA_TSF));
			lora->com->TxNum = strlen(LORA_TSF);
			break;

		case LORA_AT_CMD_RSF:
			memcpy(lora->com->TxBuf, LORA_RSF, strlen(LORA_RSF));
			lora->com->TxNum = strlen(LORA_RSF);
			break;

		case LORA_AT_CMD_TIQ:
			memcpy(lora->com->TxBuf, LORA_TIQ, strlen(LORA_TIQ));
			lora->com->TxNum = strlen(LORA_TIQ);
			break;

		case LORA_AT_CMD_RIQ:
			memcpy(lora->com->TxBuf, LORA_RIQ, strlen(LORA_RIQ));
			lora->com->TxNum = strlen(LORA_RIQ);
			break;

		case LORA_AT_CMD_SIP:
			memcpy(lora->com->TxBuf, LORA_SIP, strlen(LORA_SIP));
			lora->com->TxNum = strlen(LORA_SIP);
			break;

		case LORA_AT_CMD_LCP:
			memcpy(lora->com->TxBuf, LORA_LCP, strlen(LORA_LCP));
			lora->com->TxNum = strlen(LORA_LCP);
			break;

		case LORA_AT_CMD_TYPE:
			memcpy(lora->com->TxBuf, LORA_TYPE, strlen(LORA_TYPE));
			lora->com->TxNum = strlen(LORA_TYPE);
			break;

		case LORA_AT_CMD_RX_OFF:
			memcpy(lora->com->TxBuf, LORA_RX_OFF, strlen(LORA_RX_OFF));
			lora->com->TxNum = strlen(LORA_RX_OFF);
			break;
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_AtCmd_Pack(s_LORA *lora)
** �������ܣ�AT����������ݴ���
** ���������lora  LORA�ṹ���׵�ַ
** ���������TRUE  ����������ȷ
		     FALSE �������ݴ���
** ��    ע��

*******************************************************************************/
bool LORA_SoftInit_AtRxHandle(s_LORA *lora)
{
	if (strstr((char *)lora->com->RxBuf, "OK") != NULL)
		return TRUE;
	else
		return FALSE;
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_SoftInit_Handle(s_LORA *lora)
** �������ܣ�LORA�����ʼ��
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_SoftInit_Handle(s_LORA *lora)
{
	switch (lora->com_state)
	{
		case COM_NONE:  //�������ݴ��
			memset(lora->com->TxBuf, 0, USART2_TX_CNT_MAX);
			memset(lora->com->RxBuf, 0, USART2_RX_CNT_MAX);
			LORA_AtCmd_Pack(lora);
			lora->com_state = COM_TX;
			break;

		case COM_TX:   //���ݷ���
			if (lora->com->TxNum > 0)
			{
				HAL_UART_Transmit_DMA(lora->com->husart,
					lora->com->TxBuf,
					lora->com->TxNum);
				delay_ms(1);
				APP_TIM_StartDecounter(TIM_LORA_COM_TO,1000); //��ʼ��ʱ
				lora->com_state = COM_RX;
			}
			else
				lora->com_state = COM_NONE;
			break;

		case COM_RX:
			if (APP_TIM_ReadDecounterValue(TIM_LORA_COM_TO) == 0)  //�ж��Ƿ�ʱ
			{
				lora->com_state = COM_TIMEOUT;
			}

			if (lora->com->Status.bits.TaskDealFlg == 1)
			{
				lora->com->Status.bits.TaskDealFlg = 0;

				if (LORA_SoftInit_AtRxHandle(lora) && (lora->com->RxCnt > 0))  //���մ���
				{
					if (lora->at_cmd == LORA_AT_CMD_RX_OFF)  //�ж���û�д������
					{
						lora->state = eLORA_WORK;
						LORA_TX_MODE();   //���봫͸ģʽ
						delay_ms(100);

						memcpy(lora->com->TxBuf, LORA_AT, strlen(LORA_AT)); //�����
						lora->com->TxNum = strlen(LORA_AT);
						HAL_UART_Transmit_DMA(lora->com->husart,
							lora->com->TxBuf,
							lora->com->TxNum);
						delay_ms(1);

						APP_TIM_StartDecounter(TIM_LORA_TO, LORA_COMM_TO_TIME);   //��ʼͨ�ų�ʱ���
					}
					else
						lora->at_cmd++;  //��һ��ATָ��

					lora->com_state = COM_NONE;
				}
			}				
			break;

		case COM_TIMEOUT:  //��ʱ����
			lora->TO_cnt++;
			if (lora->TO_cnt > 5)
			{
				lora->TO_cnt = 0;
				lora->state = eLORA_RST;
			}
			else
				lora->com_state = COM_NONE;
			break;
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_Wrok_Handle(s_LORA *lora)
** �������ܣ�LORA����ģʽ
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_Wrok_Handle(s_LORA *lora)
{
	if (lora->com->Status.bits.TaskDealFlg == 1)
	{
		APP_TIM_StartDecounter(TIM_LORA_TO, LORA_COMM_TO_TIME);   //�յ�һ������ˢ��һ�μ�ʱ

		lora->com->Status.bits.TaskDealFlg = 0;   //���������ɱ�־λ
		APP_LED_Comm_OneFlash();                  //ͨ�ŵ���˸һ��
		//MODBUS����
		lora->com->TxNum = MODBUS_RTU_Handle(lora->com->RxBuf,
											 lora->com->RxCnt,
											 lora->com->TxBuf);

		if (lora->com->TxNum > 0)//�ж��ֽ����Ƿ����0
		{
			HAL_UART_Transmit_DMA(lora->com->husart, lora->com->TxBuf, lora->com->TxNum);
			delay_ms(1);
		}
	}

	if (APP_TIM_ReadDecounterValue(TIM_LORA_TO) == 0)  
	{
		lora->state = eLORA_RST;  //����ʱ���л�����λ����
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_Restart_Handle(s_LORA *lora)
** �������ܣ�LORA��λ����
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_Restart_Handle(s_LORA *lora)
{
	LORA_RST_LOW();           
	delay_ms(1);             
	LORA_RST_HIGH();          
	
	lora->at_cmd = LORA_AT_CMD_AT;

	lora->state = eLORA_STATRUP;
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_Entry(s_LORA *lora)
** �������ܣ�LORA�������
** ���������lora  LORA�ṹ���׵�ַ
** �����������
** ��    ע��

*******************************************************************************/
void LORA_Entry(s_LORA *lora)
{
	switch (lora->state)
	{
		case eLORA_STATRUP:
			LORA_StartUp_Handle(lora);
			break;

		case eLORA_SOFT_INIT:
			LORA_SoftInit_Handle(lora);
			break;

		case eLORA_WORK:
			LORA_Wrok_Handle(lora);
			break;

		case eLORA_RST:
			LORA_Restart_Handle(lora);
			break;
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void LORA_Lanuch(void)
** �������ܣ�LORA��������
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void LORA_Lanuch(void)
{
	LORA_Entry(&dev_lora);
}

/*--------------------------------�ļ���β------------------------------------*/
