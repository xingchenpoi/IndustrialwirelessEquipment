#ifndef __APP_LED_H
#define __APP_LED_H
#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	void APP_LED_Set(s_LED *led, e_TYPE_LED_MODE mode);
	void APP_LED_Comm_OneFlash(void);

#ifdef __cplusplus
}
#endif
#endif /*__APP_LED_H */