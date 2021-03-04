/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：APP_LORA.c
** 摘    要：LORA板级驱动初始化，LORA启动程序

*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/  
#include "APP_LORA.h"                                                                // 系统底板配置函数头文件                                                          



//=========================宏定义==================================
#define LORA_AT                          "AT\r\n\0"                             //AT测试指令
#define LORA_BRATE                       "AT+BRATE=03\r\n\0"                    //设置串口波特率 9600bps
#define LORA_NET                         "AT+NET=00\r\n\0"                      //设置网络模式 点对点
#define LORA_AK                          "AT+AK=11223344556677889900112233445500\r\n\0" //设置 AES 秘钥:11223344556677889900112233445566
#define LORA_MODE                        "AT+MODE=01\r\n\0"                     //设置调制模式
#define LORA_TPREM                       "AT+TPREM=0008\r\n\0"                  //设置发送前导码长度为8 
#define LORA_RPREM                       "AT+RPREM=01F4\r\n\0"                  //设置接收前导码长度为500 
#define LORA_LDR                         "AT+LDR=00\r\n\0"                      //设置低速率优化
#define LORA_SYNC                        "AT+SYNC=12\r\n\0"                     //设置同步字
#define LORA_POW                         "AT+POW=14\r\n\0"                      //设置发送功率
#define LORA_BW                          "AT+BW=07\r\n\0"                       //设置带宽 125K
#define LORA_CR                          "AT+CR=01\r\n\0"                       //设置编码速率  4/5
#define LORA_CRC                         "AT+CRC=00\r\n\0"                       //无CRC
#define LORA_TFREQ                       "AT+TFREQ=18AA1640\r\n\0"              //设置发送频率 472MHz
#define LORA_RFREQ                       "AT+RFREQ=18AA1640\r\n\0"              //设置接收频率 472MHz
#define LORA_TSF                         "AT+TSF=09\r\n\0"                      //设置发送扩频因子 9
#define LORA_RSF                         "AT+RSF=09\r\n\0"                      //设置接收扩频因子 9
#define LORA_TIQ                         "AT+TIQ=00\r\n\0"                      //设置发送载波不反转 00:OFF
#define LORA_RIQ                         "AT+RIQ=00\r\n\0"                      //设置接收载波不反转 00:OFF    
#define LORA_SIP                         "AT+SIP=00\r\n\0"                      //设置序号及协议功能 00:关闭
#define LORA_LCP                         "AT+LCP=0000\r\n\0"                    //设置链路检测周期  关闭
#define LORA_TYPE                        "AT+TYPE=00\r\n\0"                     //设置输出数据格式   00:透传
#define LORA_RX_ON						 "AT+RX=01\r\n\0"                       //开启接收测试模式
#define LORA_RX_OFF						 "AT+RX=00\r\n\0"                       //关闭接收测试模式

#define LORA_CFG                         "AT+CFG?\r\n\0"

#define LORA_AT_AK						 "AT+AK=112233445566778899001122334455" // 设置发送密钥
#define LORA_AT_TFREQ                    "AT+TFREQ="                            // 设置发送频率指令
#define LORA_AT_RFREQ                    "AT+RFREQ="                            // 设置接收频率指令



//lora模块的频点定义，470.1,470.3,...  ,489.9MHz ，每个频点间隔200kHz
//第一个信道是升级信道  99个通信信道，1个升级信道(0)
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







/*----------------------------- 内部函数声明 ---------------------------------*/ 




/*******************************************************************************
** 函数原型：void LORA_Bsp_Init(void)
** 函数功能：LORA板级驱动初始化
** 输入参数：无
** 输出参数：无
** 备    注：

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
** 函数原型：void LORA_StartUp_Handle(s_LORA *lora)
** 函数功能：LORA启动处理
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LORA_StartUp_Handle(s_LORA *lora)
{
	LORA_RST_HIGH();          //复位脚拉高
	delay_ms(10);

	LORA_AT_MODE();           // AT脚拉高，AT设置模式

	LORA_WP_HIGH();
	delay_ms(10);
	LORA_WP_LOW();
	delay_ms(10);

	delay_ms(50);

	lora->state = eLORA_SOFT_INIT;
	lora->com_state = COM_NONE;
}





/*******************************************************************************
** 函数原型：void LORA_AtCmd_Pack(s_LORA *lora)
** 函数功能：AT命令数据打包
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

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
** 函数原型：void LORA_AtCmd_Pack(s_LORA *lora)
** 函数功能：AT命令接收数据处理
** 输入参数：lora  LORA结构体首地址
** 输出参数：TRUE  返回数据正确
		     FALSE 返回数据错误
** 备    注：

*******************************************************************************/
bool LORA_SoftInit_AtRxHandle(s_LORA *lora)
{
	if (strstr((char *)lora->com->RxBuf, "OK") != NULL)
		return TRUE;
	else
		return FALSE;
}





/*******************************************************************************
** 函数原型：void LORA_SoftInit_Handle(s_LORA *lora)
** 函数功能：LORA软件初始化
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LORA_SoftInit_Handle(s_LORA *lora)
{
	switch (lora->com_state)
	{
		case COM_NONE:  //发送数据打包
			memset(lora->com->TxBuf, 0, USART2_TX_CNT_MAX);
			memset(lora->com->RxBuf, 0, USART2_RX_CNT_MAX);
			LORA_AtCmd_Pack(lora);
			lora->com_state = COM_TX;
			break;

		case COM_TX:   //数据发送
			if (lora->com->TxNum > 0)
			{
				HAL_UART_Transmit_DMA(lora->com->husart,
					lora->com->TxBuf,
					lora->com->TxNum);
				delay_ms(1);
				APP_TIM_StartDecounter(TIM_LORA_COM_TO,1000); //开始计时
				lora->com_state = COM_RX;
			}
			else
				lora->com_state = COM_NONE;
			break;

		case COM_RX:
			if (APP_TIM_ReadDecounterValue(TIM_LORA_COM_TO) == 0)  //判断是否超时
			{
				lora->com_state = COM_TIMEOUT;
			}

			if (lora->com->Status.bits.TaskDealFlg == 1)
			{
				lora->com->Status.bits.TaskDealFlg = 0;

				if (LORA_SoftInit_AtRxHandle(lora) && (lora->com->RxCnt > 0))  //接收处理
				{
					if (lora->at_cmd == LORA_AT_CMD_RX_OFF)  //判断有没有处理完成
					{
						lora->state = eLORA_WORK;
						LORA_TX_MODE();   //进入传透模式
						delay_ms(100);

						memcpy(lora->com->TxBuf, LORA_AT, strlen(LORA_AT)); //激活串口
						lora->com->TxNum = strlen(LORA_AT);
						HAL_UART_Transmit_DMA(lora->com->husart,
							lora->com->TxBuf,
							lora->com->TxNum);
						delay_ms(1);

						APP_TIM_StartDecounter(TIM_LORA_TO, LORA_COMM_TO_TIME);   //开始通信超时检测
					}
					else
						lora->at_cmd++;  //下一条AT指令

					lora->com_state = COM_NONE;
				}
			}				
			break;

		case COM_TIMEOUT:  //超时处理
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
** 函数原型：void LORA_Wrok_Handle(s_LORA *lora)
** 函数功能：LORA工作模式
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

*******************************************************************************/
void LORA_Wrok_Handle(s_LORA *lora)
{
	if (lora->com->Status.bits.TaskDealFlg == 1)
	{
		APP_TIM_StartDecounter(TIM_LORA_TO, LORA_COMM_TO_TIME);   //收到一次数据刷新一次计时

		lora->com->Status.bits.TaskDealFlg = 0;   //清除接收完成标志位
		APP_LED_Comm_OneFlash();                  //通信灯闪烁一次
		//MODBUS处理
		lora->com->TxNum = MODBUS_RTU_Handle(lora->com->RxBuf,
											 lora->com->RxCnt,
											 lora->com->TxBuf);

		if (lora->com->TxNum > 0)//判断字节数是否大于0
		{
			HAL_UART_Transmit_DMA(lora->com->husart, lora->com->TxBuf, lora->com->TxNum);
			delay_ms(1);
		}
	}

	if (APP_TIM_ReadDecounterValue(TIM_LORA_TO) == 0)  
	{
		lora->state = eLORA_RST;  //若超时，切换到复位处理
	}
}





/*******************************************************************************
** 函数原型：void LORA_Restart_Handle(s_LORA *lora)
** 函数功能：LORA复位处理
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

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
** 函数原型：void LORA_Entry(s_LORA *lora)
** 函数功能：LORA处理入口
** 输入参数：lora  LORA结构体首地址
** 输出参数：无
** 备    注：

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
** 函数原型：void LORA_Lanuch(void)
** 函数功能：LORA启动程序
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void LORA_Lanuch(void)
{
	LORA_Entry(&dev_lora);
}

/*--------------------------------文件结尾------------------------------------*/
