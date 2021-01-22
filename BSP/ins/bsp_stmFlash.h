#ifndef __BSP_STMFLASH_H
#define __BSP_STMFLASH_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);
	void STMFLASH_Write_NoCheck(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite);
	void STMFLASH_Write(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite);
	void STMFLASH_Read(uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead);

#ifdef __cplusplus
}
#endif
#endif /*__BSP_STMFLASH_H */