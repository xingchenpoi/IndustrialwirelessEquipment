#ifndef __BSP_LED_H
#define __BSP_LED_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"

	void LED_Lanuch(void);
	void LED_Bsp_Init(void);
	void LED_Bsp_DeInit(void);
	void LED_Run_Ctrl(bool onoff);
	void LED_Comm_Ctrl(bool onoff);
#ifdef __cplusplus
}
#endif
#endif /*__BSP_LED_H */