#ifndef __BSP_SWITCH_H
#define __BSP_SWITCH_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	uint8_t Switch_DevAddr_Read(void);
	uint8_t Switch_NetAddr_Read(void);

#ifdef __cplusplus
}
#endif
#endif /*__BSP_SWITCH_H */