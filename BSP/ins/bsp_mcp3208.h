#ifndef __BSP_MCP3208_H
#define __BSP_MCP3208_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"

	void MCP3208_Bsp_Init(s_MCP3208 *mcp3208);
	void MCP3208_Lanuch(void);

#ifdef __cplusplus
}
#endif
#endif /*__BSP_MCP3208_H */