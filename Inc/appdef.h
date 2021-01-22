#ifndef __APPDEF_H
#define __APPDEF_H
#ifdef __cplusplus
extern "C" {
#endif

/* define ------------------------------------------------------------------*/


//0,��֧��ucos
//1,֧��ucos
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��UCOS


/*-------------------------------�ⲿ��������--------------------------------*/
#define EMPTY 0
#define NO_FUNCTION 1

//��������
#define cSETUP_NUMBER_OF_TASKS 4


/* Definition des TASK_ID */
#define TASK_1             1
#define TASK_2             2
#define TASK_3             4
#define TASK_4             8
#define TASK_5            16
#define TASK_6            32
#define TASK_7            64
#define TASK_8 	   	  	 128
#define TASK_9     	     256
#define TASK_10    	     512
#define TASK_11   	    1024
#define TASK_12   	    2048
#define TASK_13   	    4096
#define TASK_14   	    8192
#define TASK_15  	   16384
#define TASK_16  	   32768
#define TASK_17      1*65536
#define TASK_18      2*65536
#define TASK_19      4*65536
#define TASK_20      8*65536
#define TASK_21     16*65536
#define TASK_22     32*65536
#define TASK_23     64*65536
#define TASK_24    128*65536
#define TASK_25    256*65536
#define TASK_26    512*65536
#define TASK_27   1024*65536
#define TASK_28   2048*65536
#define TASK_29   4096*65536
#define TASK_30   8192*65536

/****************************** tache 1 *******************************/
#define DIS_TASK TASK_1
#define TASK_1_MAIN_FUNC APP_Display_Task_Lanuch
/****************************** tache 2 ******************************/
#define COLLECT_TASK TASK_2
#define TASK_2_MAIN_FUNC APP_Collect_Task_Lanuch
/****************************** tache 3 ******************************/
#define SET_TASK TASK_3
#define TASK_3_MAIN_FUNC APP_Set_Task_Lanuch
/****************************** tache 4 ******************************/
#define SERVER_TASK TASK_4
#define TASK_4_MAIN_FUNC APP_Communication_Lanuch
/****************************** tache 5 ******************************/
#define TACHE5 TASK_5
#define TASK_5_MAIN_FUNC NO_FUNCTION
/****************************** tache 6 ******************************/
#define TACHE6 TASK_6  
#define TASK_6_MAIN_FUNC NO_FUNCTION
/****************************** tache 7 ******************************/
#define TACHE7 TASK_7
#define TASK_7_MAIN_FUNC NO_FUNCTION
/****************************** tache 8 ******************************/
#define TACHE8 TASK_8
#define TASK_8_MAIN_FUNC NO_FUNCTION
/****************************** tache 9 ******************************/
#define TACHE9 TASK_9
#define TASK_9_MAIN_FUNC NO_FUNCTION
/****************************** tache 10 ******************************/
#define TACHE10 TASK_10   
#define TASK_10_MAIN_FUNC NO_FUNCTION
/****************************** tache 11 ******************************/
#define TACHE11 TASK_11
#define TASK_11_MAIN_FUNC NO_FUNCTION
/****************************** tache 12 ******************************/
#define TACHE12 TASK_12
#define TASK_12_MAIN_FUNC NO_FUNCTION
/****************************** tache 13 ******************************/
#define TACHE13 TASK_13
#define TASK_13_MAIN_FUNC NO_FUNCTION
/****************************** tache 14 ******************************/
#define TACHE14 TASK_14
#define TASK_14_MAIN_FUNC NO_FUNCTION
/****************************** tache 15 ******************************/
#define TACHE15 TASK_15
#define TASK_15_MAIN_FUNC NO_FUNCTION
/****************************** tache 16 ******************************/
#define TACHE16 TASK_16
#define TASK_16_MAIN_FUNC NO_FUNCTION
/****************************** tache 17 ******************************/
#define TACHE17 TASK_17
#define TASK_17_MAIN_FUNC NO_FUNCTION
/****************************** tache 18 ******************************/
#define TACHE18 TASK_18
#define TASK_18_MAIN_FUNC NO_FUNCTION
/****************************** tache 19 ******************************/
#define TACHE19 TASK_19
#define TASK_19_MAIN_FUNC NO_FUNCTION
/****************************** tache 20 ******************************/
#define TACHE20 TASK_20
#define TASK_20_MAIN_FUNC NO_FUNCTION
/****************************** tache 21 ******************************/
#define TACHE21 TASK_21
#define TASK_21_MAIN_FUNC NO_FUNCTION
/****************************** tache 22 ******************************/
#define TACHE22 TASK_22
#define TASK_22_MAIN_FUNC NO_FUNCTION
/****************************** tache 23 ******************************/
#define TACHE23 TASK_23
#define TASK_23_MAIN_FUNC NO_FUNCTION
/****************************** tache 24 ******************************/
#define TACHE24 TASK_24
#define TASK_24_MAIN_FUNC NO_FUNCTION
/****************************** tache 25 ******************************/
#define TACHE25 TASK_25
#define TASK_25_MAIN_FUNC NO_FUNCTION
/****************************** tache 26 ******************************/
#define TACHE26 TASK_26
#define TASK_26_MAIN_FUNC NO_FUNCTION
/****************************** tache 27 ******************************/
#define TACHE27 TASK_27
#define TASK_27_MAIN_FUNC NO_FUNCTION
/****************************** tache 28 ******************************/
#define TACHE28 TASK_28
#define TASK_28_MAIN_FUNC NO_FUNCTION
/****************************** tache 29 ******************************/
#define TACHE29 TASK_29
#define TASK_29_MAIN_FUNC NO_FUNCTION
/****************************** tache 30 ******************************/
#define TACHE30 TASK_30
#define TASK_30_MAIN_FUNC NO_FUNCTION

#define cSETUP_SCHED1_STEP_NUMBER 1

/* step 1 */
#define SCHED1_STEP_1_ACTIVABLE_TASKS  DIS_TASK+COLLECT_TASK+SET_TASK+SERVER_TASK


/************************** ��ʱ���жϼ������ ************************/
#define PERIOD_OF_TIM_LAUNCH_CALL 1 

/***************************** ���ڻ��泤�� ***************************/
#define USART1_RX_CNT_MAX	256
#define USART1_TX_CNT_MAX	256

#define USART2_RX_CNT_MAX	256
#define USART2_TX_CNT_MAX	256

#define IS_USART_COM(COM)   (((COM) == COM1)||((COM) == COM2))

/******************************** MCP3208 *****************************/
#define MCP3208_CS_PIN      GPIO_PIN_12
#define MCP3208_CS_PORT		GPIOB

#define MCP3208_CS_HIGH		HAL_GPIO_WritePin(MCP3208_CS_PORT, MCP3208_CS_PIN,GPIO_PIN_SET)
#define MCP3208_CS_LOW		HAL_GPIO_WritePin(MCP3208_CS_PORT, MCP3208_CS_PIN,GPIO_PIN_RESET)

#define MCP3208_AI_CHL_NUM	2            //AIͨ��
#define MCP3208_VERF        2.5          //�ο���ѹ
#define MCP3208_FILTER_NUM  11           //�˲���
#define MCP3208_CURRENT_MIN 0.004        //�������ֵ
#define MCP3208_CURRENT_MAX 0.020        //������Сֵ


/****************************** MODBUS��ַ ****************************/
#define MB_FUNC_READ_HOLDING_ENABLED			1     //��������ּĴ���������
#define MB_FUNC_WRITE_HOLDING_ENABLED           1     //���д�����Ĵ�����ʹ�� 
#define MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED  1     //���д����Ĵ�����ʹ��

#if MB_FUNC_READ_HOLDING_ENABLED
#define  MODBUS_REG_READ_START_ADDR   0    //MODBUS ���Ĵ�����ʼ��ַ
#define  MODBUS_REG_READ_END_ADDR     19    //MODBUS ���Ĵ�����ʼ��ַ
#endif // MB_FUNC_READ_HOLDING_ENABLED


#if MB_FUNC_WRITE_HOLDING_ENABLED || MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED
#define  MODBUS_REG_WRITE_START_ADDR  0    //MODBUS д�Ĵ�����ʼ��ַ
#define  MODBUS_REG_WRITE_END_ADDR    2   //MODBUS д�Ĵ�����ʼ��ַ
#define IS_WRTER_REG_RANG(reg)       (reg >= MODBUS_REG_WRITE_START_ADDR \
										&& MODBUS_REG_WRITE_END_ADDR >= reg)
#endif // MB_FUNC_WRITE_HOLDING_ENABLED || MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED

#define  MODBUS_HOLDREG_NUM			  20           //���ּĴ�������

#define  SERIAL_PARA_REG			  0			   //��������  
   
#define  DO0_CHL_REBOOT_STA_REG       1			   //DO0ͨ���ϵ�״̬

#define  DO0_CHL_STA_REG			  2			   //DO0ͨ��״̬

#define  DI0_CHL_PULSE_CNT_REG	      3			   //DI0��������� 
#define  DI1_CHL_PULSE_CNT_REG		  4			   //DI1���������
#define  DI2_CHL_PULSE_CNT_REG		  5			   //DI2��������� 
#define  DI3_CHL_PULSE_CNT_REG		  6			   //DI3���������

#define  DI0_CHL_STA_REG			  7			   //DI0ͨ��״̬
#define  DI1_CHL_STA_REG			  8			   //DI1ͨ��״̬  
#define  DI2_CHL_STA_REG			  9		       //DI2ͨ��״̬  
#define  DI3_CHL_STA_REG			  10		   //DI3ͨ��״̬

#define  DI_STA_REG				      11		   //4·DI״̬

#define  AI0_CURRENT_REG1			  12		   //AI0����ֵ�Ĵ���1   
#define  AI0_CURRENT_REG2			  13		   //AI0����ֵ�Ĵ���2

#define  AI1_CURRENT_REG1			  14		   //AI1����ֵ�Ĵ���1   
#define  AI1_CURRENT_REG2			  15		   //AI1����ֵ�Ĵ���2

#define  AI0_VOLTAGE_REG1			  16		   //AI0��ѹֵ�Ĵ���1   
#define  AI0_VOLTAGE_REG2			  17		   //AI0��ѹֵ�Ĵ���2    

#define  AI1_VOLTAGE_REG1			  18		   //AI1��ѹֵ�Ĵ���1   
#define  AI1_VOLTAGE_REG2			  19		   //AI1��ѹֵ�Ĵ���2 


/****************************** LORA ****************************/
#define LORA_AT_PIN      GPIO_PIN_6
#define LORA_AT_PORT	 GPIOA
#define LORA_AT_MODE	 HAL_GPIO_WritePin(LORA_AT_PORT, LORA_AT_PIN,GPIO_PIN_SET)
#define LORA_TX_MODE	 HAL_GPIO_WritePin(LORA_AT_PORT, LORA_AT_PIN,GPIO_PIN_RESET)

#define LORA_WP_PIN      GPIO_PIN_4
#define LORA_WP_PORT	 GPIOA
#define LORA_WP_HIGH	 HAL_GPIO_WritePin(LORA_WP_PORT, LORA_WP_PIN,GPIO_PIN_SET)
#define LORA_WP_LOW		 HAL_GPIO_WritePin(LORA_WP_PORT, LORA_WP_PIN,GPIO_PIN_RESET)

/****************************** WDG *****************************/
#define WDG_PIN			GPIO_PIN_0
#define WDG_PORT		GPIOA

/******************************* D0 *****************************/
#define DO_CHL_NUM       1   

#define DO0_PIN			 GPIO_PIN_1
#define DO0_PORT		 GPIOA
#define DO0_CLK_ENABLE   __HAL_RCC_GPIOA_CLK_ENABLE()
#define DO0_H            HAL_GPIO_WritePin(DO0_PORT, DO0_PIN,GPIO_PIN_SET)
#define DO0_L            HAL_GPIO_WritePin(DO0_PORT, DO0_PIN,GPIO_PIN_RESET)
#define DO0_READ         HAL_GPIO_ReadPin(DO0_PORT, DO0_PIN)


/******************************* DI *****************************/
#define DI_CHL_NUM   4

#define DI0_PIN			GPIO_PIN_6
#define DI0_PORT		GPIOB
#define DI0_CLK_ENABLE  __HAL_RCC_GPIOB_CLK_ENABLE()
#define DI0_READ	    HAL_GPIO_ReadPin(DI0_PORT,DI0_PIN)

#define DI1_PIN			GPIO_PIN_7
#define DI1_PORT		GPIOB
#define DI1_CLK_ENABLE  __HAL_RCC_GPIOB_CLK_ENABLE()
#define DI1_READ	    HAL_GPIO_ReadPin(DI1_PORT,DI1_PIN)

#define DI2_PIN			GPIO_PIN_8
#define DI2_PORT		GPIOB
#define DI2_CLK_ENABLE  __HAL_RCC_GPIOB_CLK_ENABLE()
#define DI2_READ	    HAL_GPIO_ReadPin(DI2_PORT,DI2_PIN)

#define DI3_PIN			GPIO_PIN_9
#define DI3_PORT		GPIOB
#define DI3_CLK_ENABLE  __HAL_RCC_GPIOB_CLK_ENABLE()
#define DI3_READ	    HAL_GPIO_ReadPin(DI3_PORT,DI3_PIN)

/**************************** FLASH ****************************/
#define STM32_FLASH_SIZE 	64 	 		    //��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 	1              	//ʹ��FLASHд��(0��������;1��ʹ��)
#define FLASH_WAITETIME  	50000          	//FLASH�ȴ���ʱʱ��
#define STM32_FLASH_BASE   0x08000000 		//STM32 FLASH����ʼ��ַ
#define FLASH_SAVE_ADDR    0X0800FC00		    //����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)

#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		 

/***************************** LED *****************************/
#define LED_PIN					GPIO_PIN_5
#define LED_PORT				GPIOA
#define LED_L()					HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET)
#define LED_H()					HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET)                
#define LED_RED_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_BLINK_CYCLE    1000

#ifdef __cplusplus
}
#endif
#endif /*__APPDEF_H */