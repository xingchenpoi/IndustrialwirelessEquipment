#ifndef __INCLUDES_H
#define __INCLUDES_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* APP ------------------------------------------------------------------*/
#include "appdef.h"
#include "typedef.h"
#include "sysram.h"
#include "sys.h"
#include "delay.h"
#include "APP_Scheduler.h"
#include "APP_Timer.h"
#include "APP_Task.h"
#include "APP_Modbus.h"
#include "APP_LORA.h"
#include "APP_Do.h"
#include "APP_Di.h"
#include "APP_Led.h"

/* BSP ------------------------------------------------------------------*/
#include "bsp.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_mcp3208.h"
#include "bsp_switch.h"
#include "bsp_wdg.h"
#include "bsp_Do.h"
#include "bsp_Di.h"
#include "bsp_stmFlash.h"
#include "bsp_led.h"

#ifdef __cplusplus
}
#endif
#endif /*__INCLUDES_H */