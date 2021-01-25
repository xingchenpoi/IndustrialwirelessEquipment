#ifndef __SYSRAM_H
#define __SYSRAM_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern	bool isSetupUart;

extern	s_Usart s_usart1;

extern	s_Usart s_usart2;

extern  s_RS485 dev_RS485;

extern  s_MCP3208 dev_mcp3208;

extern  uint16_t modbusReg[MODBUS_HOLDREG_NUM];

extern  uint8_t devAddr;

extern  uint8_t netAddr;

extern  s_LORA dev_lora;

extern DO_TypeDef dev_do;

extern DI_TypeDef dev_di;

extern s_LED dev_led;

extern s_CONFIG sysConfig;

extern KFP KFP_Current[MCP3208_AI_CHL_NUM];

#ifdef __cplusplus
}
#endif
#endif /*__SYSRAM_H */