/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：sys.h
** 摘    要：

*******************************************************************************/
#ifndef __SYS_H
#define __SYS_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

	uint16_t usMBCRC16(uint8_t * pucFrame, uint16_t usLen);
	uint8_t checkSum(uint8_t *pch, int32_t len);
	uint8_t ascii2BCD(uint8_t byCh);
	uint32_t BCD2String(uint8_t *pDest, const uint8_t *pDataIn, uint16_t len);
	//void RMC_Analyse(s_SYS_PARA *para, uint8_t *location);
	//void UTCToBeijing(rdss21Data* time);
	//void DTU_RSSI_Analyse(s_SYS_PARA *para, uint8_t *rssi);
#ifdef TEST
	unsigned short CRC_16(unsigned char * aData, unsigned long aSize);
#endif // TEST
#ifdef __cplusplus
}
#endif
#endif /*__sys_H */

/*--------------------------------文件结尾------------------------------------*/
