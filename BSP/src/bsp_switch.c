/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�bsp_switch.c
** ժ    Ҫ�����뿪�س�ʼ�����豸��ַ��ȡ�������ַ��ȡ

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_switch.h"



/*******************************************************************************
** ����ԭ�ͣ�void Switch_Bsp_Init(void)
** �������ܣ����뿪�س�ʼ��
** �����������
** �����������
** ��    ע��

*******************************************************************************/
void Switch_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : PA7 PA8 PA11 PA12
						 PA15 */
	//GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12
	//	| GPIO_PIN_15;
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB10 PB11
							 PB3 PB4 PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11
		| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}





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
	//addr_tmp |= (uint8_t)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) << 3;
	addr_tmp |= 1 << 3;

	return (uint8_t)~addr_tmp;          // ���ص�ֵַ��0-255
}


/*--------------------------------�ļ���β------------------------------------*/