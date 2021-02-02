/* Includes ------------------------------------------------------------------*/
#include "bsp_switch.h"




/*******************************************************************************
** ����ԭ�ͣ�uint8_t Switch_DevAddr_Read(void)
** �������ܣ��豸��ַ��ȡ
** �����������
** ����������豸��ַ
** ��    ע��

*******************************************************************************/
uint8_t Switch_DevAddr_Read(void)
{
	uint8_t addr_tmp = 0;								// ��ʱ��ַ

	// ����    	
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) ;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) << 1;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)  << 2;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) << 3;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) << 4;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)  << 5;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)  << 6;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)  << 7;

	return (uint8_t)~addr_tmp;          // ���ص�ֵַ��0-255
}





/*******************************************************************************
** ����ԭ�ͣ�uint8_t Switch_NetAddr_Read(void)
** �������ܣ������ַ��ȡ
** �����������
** ��������������ַ
** ��    ע��

*******************************************************************************/
uint8_t Switch_NetAddr_Read(void)
{
	uint8_t addr_tmp = 0xF0;								// ��ʱ��ַ

		// ����
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) << 1;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) << 2;
	addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) << 3;

	return (uint8_t)~addr_tmp;          // ���ص�ֵַ��0-255
}
