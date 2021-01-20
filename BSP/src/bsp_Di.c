/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�
** ��    �ڣ�
** �ļ����ƣ�
** ժ    Ҫ��

*******************************************************************************/
/*--------------------------------- ͷ�ļ� -----------------------------------*/
#include "bsp_Di.h"  

/*-------------------------------- ȫ�ֱ��� ----------------------------------*/



/*******************************************************************************
** ����ԭ�ͣ�void DI_Bsp_Init(void)
** �������ܣ�DI��ʼ��
** �����������
** �����������
** ��    ע��


*******************************************************************************/
void DI_Bsp_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	DI0_CLK_ENABLE;
	DI1_CLK_ENABLE;
	DI2_CLK_ENABLE;
	DI3_CLK_ENABLE;

	GPIO_InitStruct.Pin = DI0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DI0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI1_PIN;
	HAL_GPIO_Init(DI1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI2_PIN;
	HAL_GPIO_Init(DI2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = DI3_PIN;
	HAL_GPIO_Init(DI3_PORT, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 3);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
/*******************************************************************************
*    ��������           ������            ���Խ��          ������
*
*******************************************************************************/





