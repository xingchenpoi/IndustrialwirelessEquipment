#ifndef __BSP_H
#define __BSP_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void Bsp_Init(void);
void ConfigPara_SaveData_Write(s_CONFIG *config);

#ifdef __cplusplus
}
#endif
#endif /*__BSP_H */