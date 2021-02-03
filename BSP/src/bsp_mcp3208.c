/*******************************************************************************
**              �����п�Ժ�����Զ����о������� Copyright (c)
**                     ������������Ӧ���з�����
**                        IM(2019-2022)
** ��    �ߣ�viggo
** ��    �ڣ�
** �ļ����ƣ�bsp_mcp3208.c
** ժ    Ҫ��MCP3208 �弶������ʼ��,MCP3208���ݶ�ȡ���������˲�

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_mcp3208.h"






/*******************************************************************************
** ����ԭ�ͣ�void KFP_Init(KFP *kfp)
** �������ܣ��������˲�������ʼ��
** ����������������˲�
** �����������
** ��    ע��
 *******************************************************************************/
void KFP_Init(KFP *kfp)
{
	uint8_t i = 0;

	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		kfp[i].LastP = 0.02;
		kfp[i].Now_P = 0;
		kfp[i].out = 0;
		kfp[i].Kg = 0;
		kfp[i].Q = 0.001;
		kfp[i].R = 0.543;
	}

}



/*******************************************************************************
** ����ԭ�ͣ�void MCP3208_Bsp_Init(s_MCP3208 *mcp3208, s_CONFIG *config)
** �������ܣ��弶������ʼ��
** ���������mcp3208     MCP3208�׵�ַ
			 config      ���ò����׵�ַ
** �����������
** ��    ע��
 *******************************************************************************/
void MCP3208_Bsp_Init(s_MCP3208 *mcp3208, s_CONFIG *config)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	MCP3208_CS_CLK_ENABLE();

	GPIO_InitStruct.Pin = MCP3208_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(MCP3208_CS_PORT, &GPIO_InitStruct);


	MX_SPI2_Init();						//SPI ��ʼ��
	__HAL_SPI_ENABLE(mcp3208->hspi);
	SPI_ReadWriteByte(mcp3208->hspi, 0xff);  //����spi

	MCP3208_CS_HIGH();

	KFP_Init(KFP_Current);

	mcp3208->para.A = config->caliPara.A;
	mcp3208->para.B = config->caliPara.B;
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
** ����ԭ�ͣ�float kalmanFilter(KFP *kfp, float input)
** �������ܣ��������˲�
** ���������kfp     �������ṹ�����
			 input   ��Ҫ�˲��Ĳ����Ĳ���ֵ�����������Ĳɼ�ֵ��
** ����������˲���Ĳ���������ֵ��
** ��    ע��
 *******************************************************************************/
float kalmanFilter(KFP *kfp, uint8_t index,float input)
{
	//Ԥ��Э����̣�kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����
	kfp[index].Now_P = kfp[index].LastP + kfp[index].Q;
	//���������淽�̣����������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���
	kfp[index].Kg = kfp[index].Now_P / (kfp[index].Now_P + kfp[index].R);
	//��������ֵ���̣�kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��
	kfp[index].out = kfp[index].out + kfp[index].Kg * (input - kfp[index].out);//��Ϊ��һ�ε�Ԥ��ֵ������һ�ε����ֵ
	//����Э�����: ���ε�ϵͳЭ����� kfp[index].LastP ����һ������׼����
	kfp[index].LastP = (1 - kfp[index].Kg) * kfp[index].Now_P;
	return kfp[index].out;
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
		MCP3208_CS_LOW();
		MCP3208_Read(mcp3208, i);
		MCP3208_CS_HIGH();
		delay_us(30);
	}

	//�����˲�����
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		//�˲�����
		mcp3208->value[i] = kalmanFilter(KFP_Current, i,(float)mcp3208->value[i]);
		//��ѹ����
		if (mcp3208->value[i] == 0)  //������0��ʱ��������
		{
			mcp3208->bat[i] = 0.996;
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
			continue;
		}
		mcp3208->bat[i] = (float)mcp3208->value[i] * MCP3208_VERF / 4096 * 2;   //�����ѹ�������ѹ��Ҫ����2

		//У׼����
		//mcp3208->bat[i] = 0.000100000001 * (mcp3208->bat[i] * mcp3208->bat[i]) + 1.048300000001 * mcp3208->bat[i] + 0.00310000001;
		if (isSetCailPara == FALSE)
		{
			mcp3208->bat[i] = mcp3208->para.A * mcp3208->bat[i] + mcp3208->para.B;
		}

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


/*--------------------------------�ļ���β------------------------------------*/