/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2019-2022)
** 作    者：viggo
** 日    期：
** 文件名称：bsp_mcp3208.c
** 摘    要：MCP3208 板级驱动初始化,MCP3208数据读取、卡尔曼滤波

*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "bsp_mcp3208.h"






/*******************************************************************************
** 函数原型：void KFP_Init(KFP *kfp)
** 函数功能：卡尔曼滤波参数初始化
** 输入参数：卡尔曼滤波
** 输出参数：无
** 备    注：
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
** 函数原型：void MCP3208_Bsp_Init(s_MCP3208 *mcp3208, s_CONFIG *config)
** 函数功能：板级驱动初始化
** 输入参数：mcp3208     MCP3208首地址
			 config      配置参数首地址
** 输出参数：无
** 备    注：
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


	MX_SPI2_Init();						//SPI 初始化
	__HAL_SPI_ENABLE(mcp3208->hspi);
	SPI_ReadWriteByte(mcp3208->hspi, 0xff);  //激活spi

	MCP3208_CS_HIGH();

	KFP_Init(KFP_Current);

	mcp3208->para.A = config->caliPara.A;
	mcp3208->para.B = config->caliPara.B;
}





/*******************************************************************************
** 函数原型：void MCP3208_Read(s_MCP3208 *mcp3208,uint8_t ch)
** 函数功能：电压数据读取
** 输入参数：mcp3208    mcp3208结构体指针
		     ch         读取通道
** 输出参数：无
** 备    注：MCP3208 各通道读取指令
			 通道0      06 00 00
			 通道1		06 40 00
			 通道2		06 80 00
			 通道3		06 C0 00
			 通道4		07 00 00
			 通道5		07 40 00
			 通道6		07 80 00
			 通道7		07 C0 00
 *******************************************************************************/
void MCP3208_Read(s_MCP3208 *mcp3208,uint8_t ch)
{
	uint8_t txdata[3] = {0}, rxdata[3] = { 0 };

	txdata[0] = ((ch & 0x07) >> 2) | 0x06;
	txdata[1] = (ch & 0x07) << 6;

	HAL_SPI_TransmitReceive(mcp3208->hspi, txdata, rxdata, 3, 1000);	//发送命令

	rxdata[1] &= 0x0F;
	mcp3208->value[ch] = ((uint16_t)rxdata[1] << 8) | rxdata[2]; //原始数值
}




/*******************************************************************************
** 函数原型：float kalmanFilter(KFP *kfp, float input)
** 函数功能：卡尔曼滤波
** 输入参数：kfp     卡尔曼结构体参数
			 input   需要滤波的参数的测量值（即传感器的采集值）
** 输出参数：滤波后的参数（最优值）
** 备    注：
 *******************************************************************************/
float kalmanFilter(KFP *kfp, uint8_t index,float input)
{
	//预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
	kfp[index].Now_P = kfp[index].LastP + kfp[index].Q;
	//卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
	kfp[index].Kg = kfp[index].Now_P / (kfp[index].Now_P + kfp[index].R);
	//更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
	kfp[index].out = kfp[index].out + kfp[index].Kg * (input - kfp[index].out);//因为这一次的预测值就是上一次的输出值
	//更新协方差方程: 本次的系统协方差付给 kfp[index].LastP 威下一次运算准备。
	kfp[index].LastP = (1 - kfp[index].Kg) * kfp[index].Now_P;
	return kfp[index].out;
}





/*******************************************************************************
** 函数原型：void MCP3208_Enrty(s_MCP3208 *mcp3208)
** 函数功能：mcp3208处理入口
** 输入参数：mcp3208    mcp3208结构体指针
** 输出参数：无
** 备    注：
 *******************************************************************************/
void MCP3208_Enrty(s_MCP3208 *mcp3208)
{
	uint8_t i = 0;

	if (APP_TIM_ReadDecounterValue(TIM_MCP3208) != 0)
		return;
	APP_TIM_StartDecounter(TIM_MCP3208, 5);

	//读取电压数据
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		MCP3208_CS_LOW();
		MCP3208_Read(mcp3208, i);
		MCP3208_CS_HIGH();
		delay_us(30);
	}

	//进行滤波处理
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		//滤波处理
		mcp3208->value[i] = kalmanFilter(KFP_Current, i,(float)mcp3208->value[i]);
		//电压计算
		if (mcp3208->value[i] == 0)  //当处于0的时候不做处理
		{
			mcp3208->bat[i] = 0.996;
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
			continue;
		}
		mcp3208->bat[i] = (float)mcp3208->value[i] * MCP3208_VERF / 4096 * 2;   //计算电压，电阻分压，要乘以2

		//校准函数
		//mcp3208->bat[i] = 0.000100000001 * (mcp3208->bat[i] * mcp3208->bat[i]) + 1.048300000001 * mcp3208->bat[i] + 0.00310000001;
		if (isSetCailPara == FALSE)
		{
			mcp3208->bat[i] = mcp3208->para.A * mcp3208->bat[i] + mcp3208->para.B;
		}

		//电流转化
		mcp3208->current[i] = mcp3208->bat[i] / 249.0;
		//防止超过范围
		if (mcp3208->current[i] < MCP3208_CURRENT_MIN)  //电流最小值判断
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
		if(mcp3208->current[i] > MCP3208_CURRENT_MAX)	//电流最大值判断
			mcp3208->current[i] = MCP3208_CURRENT_MAX;
	}
}





/*******************************************************************************
** 函数原型：void MCP3208_Lanuch(void)
** 函数功能：MCP3208启动程序
** 输入参数：无
** 输出参数：无
** 备    注：
 *******************************************************************************/
void MCP3208_Lanuch(void)
{
	MCP3208_Enrty(&dev_mcp3208);
}


/*--------------------------------文件结尾------------------------------------*/