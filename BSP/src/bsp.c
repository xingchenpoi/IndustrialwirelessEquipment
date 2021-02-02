/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp.c
** 摘    要：板级驱动处理

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp.h"



//uint16_t size = 0;

/*******************************************************************************
** 函数原型：void ConfigPara_SaveData_Read(s_CONFIG *config)
** 函数功能：参数保存
** 输入参数：config 配置参数首地址
** 输出参数：无
** 备    注：
*******************************************************************************/
void ConfigPara_SaveData_Read(s_CONFIG *config)
{
	STMFLASH_Read(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG)/2);
}




/*******************************************************************************
** 函数原型：void ConfigPara_SaveData_Write(s_CONFIG *config)
** 函数功能：参数保存
** 输入参数：config 配置参数首地址
** 输出参数：无
** 备    注：
*******************************************************************************/
void ConfigPara_SaveData_Write(s_CONFIG *config)
{
	STMFLASH_Write(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG)/2);
}





/*******************************************************************************
** 函数原型：void PARA_Init(s_CONFIG *config)
** 函数功能：参数初始化
** 输入参数：config 配置参数首地址
** 输出参数：无
** 备    注：
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
** 函数原型：void Bsp_Init(void)
** 函数功能：驱动初始化
** 输入参数：无
** 输出参数：无
** 备    注：
 *******************************************************************************/
void Bsp_Init(void)
{
	MX_DMA_Init();
	MX_TIM3_Init();

	delay_init(64);               		//初始化延时函数
	HAL_TIM_Base_Start_IT(&htim3);
	
	PARA_Init(&sysConfig);

	LED_Bsp_Init();                    //LED初始化
	
	MCP3208_Bsp_Init(&dev_mcp3208);    //AI初始化
	RS485_Bsp_Init();                  //RS485初始化
	LORA_Bsp_Init();                   //LoRa初始化

	Switch_Bsp_Init();                 //拨码开关初始化
	devAddr = Switch_DevAddr_Read();   //设备地址读取
	if (devAddr == 0)
		devAddr = 1;
	netAddr = Switch_NetAddr_Read();   //网络地址读取
	if (netAddr == 0)
		netAddr = 1;

	DO_Bsp_Init();                     //DO初始化
	dev_do.reboot_sta[0] = sysConfig.do_Reboot_sta;   //获取初始化状态
	DO_Reboot_Sta_Set(&dev_do);        //DO上电状态设置

	DI_Bsp_Init();                     //DI初始化

	WDG_Bsp_Init();                    //硬件看门狗初始化
}





/*--------------------------------文件结尾------------------------------------*/
