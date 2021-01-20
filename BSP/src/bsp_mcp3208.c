/* Includes ------------------------------------------------------------------*/
#include "bsp_mcp3208.h"





/*******************************************************************************
** ����ԭ�ͣ�void MCP3208_Bsp_Init(s_MCP3208 *mcp3208)
** �������ܣ�MCP�༶������ʼ��
** ���������mcp3208    mcp3208�ṹ��ָ��
** �����������
** ��    ע��
 *******************************************************************************/
void MCP3208_Bsp_Init(s_MCP3208 *mcp3208)
{
	__HAL_SPI_ENABLE(mcp3208->hspi);
	SPI_ReadWriteByte(mcp3208->hspi, 0xff);  //����spi

	MCP3208_CS_HIGH;
}





/*******************************************************************************
** ����ԭ�ͣ�void MCP3208_Read(s_MCP3208 *mcp3208,uint8_t ch)
** �������ܣ���ѹ���ݶ�ȡ
** ���������mcp3208    mcp3208�ṹ��ָ��
		     ch         ��ȡͨ��
** �����������
** ��    ע��MCP3208 ��ͨ����ȡָ��
			 ͨ��0      06 00 00
			 ͨ��1		06 40 00
			 ͨ��2		06 80 00
			 ͨ��3		06 C0 00
			 ͨ��4		07 00 00
			 ͨ��5		07 40 00
			 ͨ��6		07 80 00
			 ͨ��7		07 C0 00
 *******************************************************************************/
void MCP3208_Read(s_MCP3208 *mcp3208,uint8_t ch)
{
	uint8_t txdata[3] = {0}, rxdata[3] = { 0 };

	txdata[0] = ((ch & 0x07) >> 2) | 0x06;
	txdata[1] = (ch & 0x07) << 6;

	HAL_SPI_TransmitReceive(mcp3208->hspi, txdata, rxdata, 3, 1000);	//��������

	rxdata[1] &= 0x0F;
	mcp3208->value[ch] = ((uint16_t)rxdata[1] << 8) | rxdata[2]; //ԭʼ��ֵ
}





/*******************************************************************************
** ����ԭ�ͣ�uint16_t MCP3208_Filter(s_MCP3208 *mcp3208, uint8_t ch)
** �������ܣ�ԭʼ�����˲�
** ���������mcp3208    mcp3208�ṹ��ָ��
			 ch         AIͨ��ͨ��
** �����������ֵ����
** ��    ע��������ֵ�˲���
 *******************************************************************************/
uint16_t MCP3208_Filter(s_MCP3208 *mcp3208, uint8_t ch)
{
	uint8_t i = 0,j = 0;
	uint16_t temp = 0;

	//ð�ݷ�����
	for (j = 0; j < MCP3208_FILTER_NUM-1; j++)
	{
		for (i = 0; i < MCP3208_FILTER_NUM - 1 - j; i++)
		{
			if (mcp3208->filter[ch].val[i] > mcp3208->filter[ch].val[i + 1])
			{
				temp = mcp3208->filter[ch].val[i];
				mcp3208->filter[ch].val[i] = mcp3208->filter[ch].val[i + 1];
				mcp3208->filter[ch].val[i + 1] = temp;
			}
		}
	}

	return mcp3208->filter[ch].val[(MCP3208_FILTER_NUM - 1) / 2];
}





/*******************************************************************************
** ����ԭ�ͣ�void MCP3208_Enrty(s_MCP3208 *mcp3208)
** �������ܣ�mcp3208�������
** ���������mcp3208    mcp3208�ṹ��ָ��
** �����������
** ��    ע��
 *******************************************************************************/
void MCP3208_Enrty(s_MCP3208 *mcp3208)
{
	uint8_t i = 0;

	if (APP_TIM_ReadDecounterValue(TIM_MCP3208) != 0)
		return;
	APP_TIM_StartDecounter(TIM_MCP3208, 5);

	//��ȡ��ѹ����
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		MCP3208_CS_LOW;
		MCP3208_Read(mcp3208, i);
		mcp3208->filter[i].val[mcp3208->filterIndex] = mcp3208->value[i];
		MCP3208_CS_HIGH;
		delay_us(30);
	}

	//�˲�����
	mcp3208->filterIndex++;
	if (mcp3208->filterIndex < MCP3208_FILTER_NUM)
		return;
	mcp3208->filterIndex = 0;

	//�����˲�����
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		//�˲�����
		mcp3208->value[i] = MCP3208_Filter(mcp3208, i);
		//��ѹ����
		if (mcp3208->value[i] == 0)  //������0��ʱ��������
		{
			mcp3208->bat[i] = 0.996;
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
			continue;
		}
		mcp3208->bat[i] = (float)mcp3208->value[i] * MCP3208_VERF / 4096 * 2;   //�����ѹ�������ѹ��Ҫ����2
		//У׼����
		mcp3208->bat[i] = 1.0489 * mcp3208->bat[i] + 0.0024;
		//����ת��
		mcp3208->current[i] = mcp3208->bat[i] / 249.0;
		//��ֹ������Χ
		if (mcp3208->current[i] < MCP3208_CURRENT_MIN)  //������Сֵ�ж�
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
		if(mcp3208->current[i] > MCP3208_CURRENT_MAX)	//�������ֵ�ж�
			mcp3208->current[i] = MCP3208_CURRENT_MAX;
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void MCP3208_Lanuch(void)
** �������ܣ�MCP3208��������
** �����������
** �����������
** ��    ע��
 *******************************************************************************/
void MCP3208_Lanuch(void)
{
	MCP3208_Enrty(&dev_mcp3208);
}

