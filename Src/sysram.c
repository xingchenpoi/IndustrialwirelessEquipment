/* Includes ------------------------------------------------------------------*/
#include "sysram.h"

uint8_t Usart1_txbuff[USART1_TX_CNT_MAX];
uint8_t Usart1_rxbuff[USART1_RX_CNT_MAX];

uint8_t Usart2_txbuff[USART2_TX_CNT_MAX];
uint8_t Usart2_rxbuff[USART2_RX_CNT_MAX];

bool isSetupUart = FALSE;             //设置串口参数

s_Usart s_usart1 = {
	.RxBuf = Usart1_rxbuff,
	.TxBuf = Usart1_txbuff,
	.husart = &huart1,
};

s_Usart s_usart2 = {
	.RxBuf = Usart2_rxbuff,
	.TxBuf = Usart2_txbuff,
	.husart = &huart2,
};


s_RS485 dev_RS485 = {
	.com = &s_usart1,
};

s_MCP3208 dev_mcp3208 = {
	.hspi = &hspi2,
};

uint16_t modbusReg[MODBUS_HOLDREG_NUM] = { 0 };

uint8_t devAddr = 0x01;

uint8_t netAddr = 0x01;

s_LORA dev_lora = {
	 .com = &s_usart2,
};

DO_TypeDef dev_do;

DI_TypeDef dev_di;

s_LED dev_led = {
	.isOpen = TRUE,
	.isFlash = TRUE,
	.pin = LED_PIN,
	.port = LED_PORT,
};

s_CONFIG sysConfig;

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/