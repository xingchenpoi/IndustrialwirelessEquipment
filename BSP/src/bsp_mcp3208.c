/* Includes ------------------------------------------------------------------*/
#include "bsp_mcp3208.h"





/*******************************************************************************
** 函数原型：void MCP3208_Bsp_Init(s_MCP3208 *mcp3208)
** 函数功能：MCP班级驱动初始化
** 输入参数：mcp3208    mcp3208结构体指针
** 输出参数：无
** 备    注：
 *******************************************************************************/
void MCP3208_Bsp_Init(s_MCP3208 *mcp3208)
{
	__HAL_SPI_ENABLE(mcp3208->hspi);
	SPI_ReadWriteByte(mcp3208->hspi, 0xff);  //激活spi

	MCP3208_CS_HIGH;
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
** 函数原型：uint16_t MCP3208_Filter(s_MCP3208 *mcp3208, uint8_t ch)
** 函数功能：原始数据滤波
** 输入参数：mcp3208    mcp3208结构体指针
			 ch         AI通道通道
** 输出参数：中值数据
** 备    注：采用中值滤波法
 *******************************************************************************/
uint16_t MCP3208_Filter(s_MCP3208 *mcp3208, uint8_t ch)
{
	uint8_t i = 0,j = 0;
	uint16_t temp = 0;

	//冒泡法排序
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
		MCP3208_CS_LOW;
		MCP3208_Read(mcp3208, i);
		mcp3208->filter[i].val[mcp3208->filterIndex] = mcp3208->value[i];
		MCP3208_CS_HIGH;
		delay_us(30);
	}

	//滤波计数
	mcp3208->filterIndex++;
	if (mcp3208->filterIndex < MCP3208_FILTER_NUM)
		return;
	mcp3208->filterIndex = 0;

	//进行滤波处理
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		//滤波处理
		mcp3208->value[i] = MCP3208_Filter(mcp3208, i);
		//电压计算
		if (mcp3208->value[i] == 0)  //当处于0的时候不做处理
		{
			mcp3208->bat[i] = 0.996;
			mcp3208->current[i] = MCP3208_CURRENT_MIN;
			continue;
		}
		mcp3208->bat[i] = (float)mcp3208->value[i] * MCP3208_VERF / 4096 * 2;   //计算电压，电阻分压，要乘以2
		//校准函数
		mcp3208->bat[i] = 1.0489 * mcp3208->bat[i] + 0.0024;
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

