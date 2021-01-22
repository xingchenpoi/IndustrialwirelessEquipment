#ifndef __BSP_LED_H
#define __BSP_LED_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"

	void LED_Lanuch(void);
	void LED_Bsp_Init(s_LED *dev);
	void LED_Bsp_DeInit(s_LED *dev);
#ifdef __cplusplus
}
#endif
#endif /*__BSP_LED_H */