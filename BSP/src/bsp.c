/* Includes ------------------------------------------------------------------*/
#include "bsp.h"





/*******************************************************************************
** 函数原型：void ConfigPara_SaveData_Read(s_CONFIG *config)
** 函数功能：参数保存
** 输入参数：config 配置参数首地址
** 输出参数：无
** 备    注：
*******************************************************************************/
void ConfigPara_SaveData_Read(s_CONFIG *config)
{
	//STMFLASH_Read(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG));
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
	//STMFLASH_Write(FLASH_SAVE_ADDR, (uint16_t *)config, sizeof(s_CONFIG));
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
** 函数原型：void Bsp_Init(void)
** 函数功能：驱动初始化
** 输入参数：无
** 输出参数：无
** 备    注：
 *******************************************************************************/
void Bsp_Init(void)
{
	delay_init(64);               		//初始化延时函数
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	usart_enable(&huart1, s_usart1.RxBuf, USART1_RX_CNT_MAX);
	usart_enable(&huart2, s_usart2.RxBuf, USART2_RX_CNT_MAX);

	PARA_Init(&sysConfig);
	
	MCP3208_Bsp_Init(&dev_mcp3208);
	Usart_Bsp_Init(COM1, sysConfig.uartPara);    //rs485初始化

	devAddr = Switch_DevAddr_Read();   //设备地址读取
	if (devAddr == 0)
		devAddr = 1;
	netAddr = Switch_NetAddr_Read();   //网络地址读取
	if (netAddr == 0)
		netAddr = 1;

	DO_Reboot_Sta_Set(&dev_do);        //DO上电状态设置



}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
