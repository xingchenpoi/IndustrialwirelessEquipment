/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：typedef.h
** 摘    要：数据类型定义

*******************************************************************************/
#ifndef __TYPEDEF_H
#define __TYPEDEF_H
#ifdef __cplusplus
extern "C" {
#endif

/* Typedef ------------------------------------------------------------------*/
#include "appdef.h"


//定义一些常用的数据类型短关键字 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;


/* ----------------------------------枚举-------------------------------------*/
typedef enum
{
	FALSE = 0,
	TRUE = 1
}bool;

typedef enum
{
	TIM_MCP3208 = 0,     
	TIM_LORA_COM_TO,
	TIM_WDG,
	TIM_DI_INTERVAL,
	TIM_LED,                 //运行灯
	TIM_LED_COMM,            //通信灯
	TIM_TANK_INTERVAL,
	end_of_table_cnt_decnt
}e_TIM_TABLE_ID;

typedef enum
{
	COUNT = 0,
	DECOUNT
} e_TYPE_USE_TIMER;

typedef union
{
	uint8_t  byte;
	struct
	{
		uint8_t  RxDealFlg : 1;													//接收处理标志
		uint8_t  TxDoFlg : 1;														//发送进行标志
		uint8_t  TaskDealFlg : 1;													//线程任务处理标志
		uint8_t  unuse : 3;														//备用
	}bits;
}UART_STA;


typedef enum
{
	COM1= 0,
	COM2
}UART_INDEX;


typedef enum
{
	eLORA_STATRUP = 0,
	eLORA_SOFT_INIT,
	eLORA_WORK,
	eLORA_RST,
}e_TYPE_LORA_STA;


typedef enum
{
	LORA_AT_CMD_AT = 0,
	LORA_AT_CMD_BRATE,
	LORA_AT_CMD_NET,
	LORA_AT_CMD_AK,
	LORA_AT_CMD_MODE,                        
	LORA_AT_CMD_TPREM,                       
	LORA_AT_CMD_RPREM,                       
	LORA_AT_CMD_LDR,                       
	LORA_AT_CMD_SYNC,                        
	LORA_AT_CMD_POW,                       
	LORA_AT_CMD_BW,                         
	LORA_AT_CMD_CR,                         
	LORA_AT_CMD_CRC,                         
	LORA_AT_CMD_TFREQ,                       
	LORA_AT_CMD_RFREQ,                       
	LORA_AT_CMD_TSF,                        
	LORA_AT_CMD_RSF,                        
	LORA_AT_CMD_TIQ,                       
	LORA_AT_CMD_RIQ,                       
	LORA_AT_CMD_SIP,                        
	LORA_AT_CMD_LCP,                       
	LORA_AT_CMD_TYPE,                                           						                      
	LORA_AT_CMD_RX_OFF,
}e_TYPE_LORA_AT_CMD;


typedef enum
{
	COM_NONE = 0,    /* 初始化状态*/
	COM_TX,          /* 发送模式 */
	COM_RX,          /* 接收状态*/
	COM_TIMEOUT,	  /* 超时状态*/
}e_COM_STATE_Enum;

typedef enum
{
	DI_CHL0 = 0,
	DI_CHL1,
	DI_CHL2,
	DI_CHL3,
}eDI_CHL;

typedef enum
{
	eLED_FLASH = 0,
	eLED_ON,
	eLED_OFF,
	eLED_ONE_FLASH,      //一次闪烁
	eLED_End_Of_Table
}e_TYPE_LED_MODE;

/* ---------------------------------结构体------------------------------------*/

//定时器结构体
typedef struct
{
	bool	 activate;
	uint16_t type;
	uint32_t value;
}t_TIM_TAB_DEF_ELEMENT;

//调度任务
typedef struct
{
	void(*task_main_func_ptr)(void);
}tab_ptr_function;


//串口结构体
typedef struct
{
	UART_STA Status;											//状态标志字节
	uint8_t  RxCnt;												//接收长度
	uint8_t  TxNum;												//发送长度
	uint8_t  *RxBuf;											//接收缓存
	uint8_t  *TxBuf;											//发送缓存
	UART_HandleTypeDef *husart;
}s_Usart;

typedef struct
{
	float A;
	float B;
}s_CalibrationPara;


//RS485结构体
typedef struct 
{
	s_Usart *com;
}s_RS485;


//MCP3208
typedef struct
{
	SPI_HandleTypeDef *hspi;
	uint16_t value[MCP3208_AI_CHL_NUM];
	uint16_t currentHex[MCP3208_AI_CHL_NUM];
	float bat[MCP3208_AI_CHL_NUM];
	float current[MCP3208_AI_CHL_NUM];
	s_CalibrationPara para;
}s_MCP3208;

//LORA
typedef struct
{
	e_TYPE_LORA_STA state;
	e_TYPE_LORA_AT_CMD at_cmd;
	e_COM_STATE_Enum com_state;
	uint8_t TO_cnt;
	s_Usart *com;
}s_LORA;

//DO
typedef struct
{
	uint8_t reboot_sta[DO_CHL_NUM];
	uint8_t rt_sta[DO_CHL_NUM];
}DO_TypeDef;

//DI
typedef struct
{
	uint8_t rt_sta[DI_CHL_NUM];
	uint16_t pulse_cnt[DI_CHL_NUM];
}DI_TypeDef;

typedef struct
{
	bool isOpen;            //是否初始化
	bool isFlash;           //是否闪烁
	e_TYPE_LED_MODE mode;   //LED模式
	e_TIM_TABLE_ID timer;   //闪烁计时
	uint16_t pin;           //LED引脚
	uint32_t flashingCycle;    //闪烁周期
	GPIO_TypeDef * port;    //LED 端口
	void(*Ctrl)(bool onoff);
}s_LED;


typedef struct
{
	uint32_t BaudRate;
	uint32_t StopBits;
	uint32_t Parity;
	uint32_t WordLength;
}s_Uart_Para;


//配置参数

typedef struct
{
	bool isSave;
	uint8_t do_Reboot_sta;   //上电状态
	s_Uart_Para uartPara;    //串口参数
	s_CalibrationPara caliPara;  //校验参数
}s_CONFIG;   


typedef struct
{
	float LastP;//上次估算协方差 初始化值为0.02
	float Now_P;//当前估算协方差 初始化值为0
	float out;//卡尔曼滤波器输出 初始化值为0
	float Kg;//卡尔曼增益 初始化值为0
	float Q;//过程噪声协方差 初始化值为0.001
	float R;//观测噪声协方差 初始化值为0.543
}KFP;//Kalman Filter parameter

#ifdef __cplusplus
}
#endif
#endif /*__TYPEDEF_H */

/*--------------------------------文件结尾------------------------------------*/
