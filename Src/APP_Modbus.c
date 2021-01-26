/*******************************************************************************
**              广州中科院沈阳自动化研究所分所 Copyright (c)
**                     物联网技术与应用研发中心
**                        IM(2013-2015)
** 作    者：
** 日    期：
** 文件名称：
** 摘    要：

*******************************************************************************/
/*--------------------------------- 头文件 -----------------------------------*/  
#include "APP_Modbus.h"                                                         // 头文件                                                          






/*******************************************************************************
** 函数原型：float RegValToFloat(uint16_t *reg,uint8_t addr)
** 函数功能：寄存器值转成flaot型数
** 输入参数：reg  寄存器首地址
			 addr 寄存器地址
** 输出参数：float 转化成功的数据
** 备    注：
*******************************************************************************/
float RegValToFloat(uint16_t *reg,uint8_t addr)
{
	uint8_t temp[4] = { 0 };
	float val = 0.0;
	uint32_t u32Val = 0;

	temp[3] = reg[addr] >> 8;
	temp[2] = reg[addr] & 0xFF;
	temp[1] = reg[addr+1] >> 8;
	temp[0] = reg[addr+1] & 0xFF;

	u32Val = ((uint32_t)temp[3] << 24);
	u32Val |= ((uint32_t)temp[2] << 16);
	u32Val |= ((uint32_t)temp[1] << 8);
	u32Val |= temp[0];

	memcpy(&val, &u32Val, 4);

	return val;
}






/*******************************************************************************
** 函数原型：int32_t RegValToInt32(uint16_t *reg,uint8_t addr)
** 函数功能：寄存器值转成int型数
** 输入参数：reg  寄存器首地址
			 addr 寄存器地址
** 输出参数：int32_t 转化成功的数据
** 备    注：
*******************************************************************************/
int32_t RegValToInt32(uint16_t *reg, uint8_t addr)
{
	uint8_t temp[4] = { 0 };
	uint32_t u32Val = 0;

	temp[3] = reg[addr] >> 8;
	temp[2] = reg[addr] & 0xFF;
	temp[1] = reg[addr + 1] >> 8;
	temp[0] = reg[addr + 1] & 0xFF;

	u32Val = ((uint32_t)temp[3] << 24);
	u32Val |= ((uint32_t)temp[2] << 16);
	u32Val |= ((uint32_t)temp[1] << 8);
	u32Val |= temp[0];

	return (int32_t)u32Val;
}






/*******************************************************************************
** 函数原型：void MODBUS_Data_Assignment(void)
** 函数功能：MODBUS寄存器赋值
** 输入参数：无
** 输出参数：无
** 备    注：

*******************************************************************************/
void MODBUS_Data_Assignment(void)
{
	uint8_t temp[4] = { 0 },i = 0;
	float val = 0.0;

	modbusReg[SERIAL_PARA_REG] = Usart_Para_Get(sysConfig.uartPara);
	
	modbusReg[DO0_CHL_REBOOT_STA_REG] = dev_do.reboot_sta[0];

	modbusReg[DO0_CHL_STA_REG] = dev_do.rt_sta[0];

	modbusReg[DI0_CHL_PULSE_CNT_REG] = dev_di.pulse_cnt[0];
	modbusReg[DI1_CHL_PULSE_CNT_REG] = dev_di.pulse_cnt[1];
	modbusReg[DI2_CHL_PULSE_CNT_REG] = dev_di.pulse_cnt[2];
	modbusReg[DI3_CHL_PULSE_CNT_REG] = dev_di.pulse_cnt[3];

	DI_Sta_Get(&dev_di);       //获取当前DI值

	modbusReg[DI0_CHL_STA_REG] = dev_di.rt_sta[0];
	modbusReg[DI1_CHL_STA_REG] = dev_di.rt_sta[1];
	modbusReg[DI2_CHL_STA_REG] = dev_di.rt_sta[2];
	modbusReg[DI3_CHL_STA_REG] = dev_di.rt_sta[3];

	modbusReg[DI_STA_REG] = 0;
	modbusReg[DI_STA_REG] |= dev_di.rt_sta[0];
	modbusReg[DI_STA_REG] |= (dev_di.rt_sta[1] << 1);
	modbusReg[DI_STA_REG] |= (dev_di.rt_sta[2] << 2);
	modbusReg[DI_STA_REG] |= (dev_di.rt_sta[3] << 3);

	//电流赋值
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		val = dev_mcp3208.current[i];
		memcpy(&modbusReg[AI0_CURRENT_REG1 + i * 2], &val, 4);
		temp[0] = modbusReg[AI0_CURRENT_REG2 + i * 2] >> 8;
		temp[1] = modbusReg[AI0_CURRENT_REG2 + i * 2];
		temp[2] = modbusReg[AI0_CURRENT_REG1 + i * 2] >> 8;
		temp[3] = modbusReg[AI0_CURRENT_REG1 + i * 2];

		modbusReg[AI0_CURRENT_REG1 + i * 2] = (((uint16_t)temp[0]) << 8) | temp[1];
		modbusReg[AI0_CURRENT_REG2 + i * 2] = (((uint16_t)temp[2]) << 8) | temp[3];
	}

	//电压赋值
	for (i = 0; i < MCP3208_AI_CHL_NUM; i++)
	{
		val = dev_mcp3208.bat[i];
		memcpy(&modbusReg[AI0_VOLTAGE_REG1 + i * 2], &val, 4);
		temp[0] = modbusReg[AI0_VOLTAGE_REG2 + i * 2] >> 8;
		temp[1] = modbusReg[AI0_VOLTAGE_REG2 + i * 2];
		temp[2] = modbusReg[AI0_VOLTAGE_REG1 + i * 2] >> 8;
		temp[3] = modbusReg[AI0_VOLTAGE_REG1 + i * 2];

		modbusReg[AI0_VOLTAGE_REG1 + i * 2] = (((uint16_t)temp[0]) << 8) | temp[1];
		modbusReg[AI0_VOLTAGE_REG2 + i * 2] = (((uint16_t)temp[2]) << 8) | temp[3];
	}
}







/*******************************************************************************
** 函数原型：uint16_t MODBUS_RTU_CMD03_Handle(uint8_t regStartAddr, uint16_t regNum, uint8_t *txData)
** 函数功能：MODBUS 功能码03处理函数
** 输入参数：regStartAddr 寄存器起始地址
			 regNum 寄存器数量
			 txData 发送缓存起始地址
** 输出参数：发送数据长度
** 备    注：

*******************************************************************************/
uint16_t MODBUS_RTU_CMD03_Handle(uint8_t regStartAddr, uint16_t regNum, uint8_t *txData)
{
	uint16_t len = 0, calCRC = 0;
	uint8_t i = 0;

	if (regStartAddr + regNum > MODBUS_HOLDREG_NUM)
		return len;

	//帧头数据填充
	txData[0] = devAddr;
	txData[1] = 0x03;
	txData[2] = regNum * 2;

	//寄存器值赋值
	for (i = 0; i < regNum; i++)
	{
		txData[3 + i * 2] = modbusReg[regStartAddr + i] >> 8 & 0xFF;
		txData[4 + i * 2] = modbusReg[regStartAddr + i] & 0xFF;
	}

	//获取当前长度
	len = regNum * 2 + 3;

	//CRC计算数据
	calCRC = usMBCRC16(txData, len);

	//CRC赋值
	txData[len++] = (calCRC >> 8) & 0xFF;
	txData[len++] = calCRC & 0xFF;

	//返回长度
	return len;
}





#if MB_FUNC_WRITE_HOLDING_ENABLED
/*******************************************************************************
** 函数原型：void MODBUS_RTU_CMD06_Callback(uint8_t regStartAddr, uint16_t regval)
** 函数功能：MODBUS 功能码06处理函数
** 输入参数：regStartAddr 寄存器起始地址
			 val 寄存器值
** 输出参数：无
** 备    注：

*******************************************************************************/
void MODBUS_RTU_CMD06_Callback(uint8_t regStartAddr, uint16_t regval)
{

	modbusReg[regStartAddr] = regval;

	switch (regStartAddr)
	{
		case SERIAL_PARA_REG:
			Usart_Para_Set(regval, &sysConfig.uartPara);
			isSetupUart = TRUE;
			ConfigPara_SaveData_Write(&sysConfig);
			break;

		case DO0_CHL_REBOOT_STA_REG:
			regval = (regval > 0) ? 1 : 0;
			sysConfig.do_Reboot_sta = regval;
			dev_do.reboot_sta[0] = regval;
			ConfigPara_SaveData_Write(&sysConfig);
			break;

		case DO0_CHL_STA_REG:
			regval = (regval > 0) ? 1 : 0;
			DO_Ctrl(&dev_do, 0, regval);
			break;

		default:
			break;
	}

}
#endif // MB_FUNC_WRITE_HOLDING_ENABLED





#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED
/*******************************************************************************
** 函数原型：void MODBUS_RTU_CMD16_Callback(uint8_t regStartAddr, uint8_t regNum)
** 函数功能：MODBUS 功能码16回调函数
** 输入参数：regStartAddr 寄存器起始地址
			 regNum 接收缓存起始地址
** 输出参数：发送数据长度
** 备    注：

*******************************************************************************/
void MODBUS_RTU_CMD16_Callback(uint8_t regStartAddr, uint8_t regNum)
{
	uint8_t i = 0, isSaveFlag = 0;
	for (i = regStartAddr; i < regStartAddr + regNum; i++)
	{
		switch (i)
		{
			case SERIAL_PARA_REG:
				Usart_Para_Set(modbusReg[i], &sysConfig.uartPara);
				isSetupUart = TRUE;
				isSaveFlag = 1;
				break;

			case DO0_CHL_REBOOT_STA_REG:
				modbusReg[i] = (modbusReg[i] > 0) ? 1 : 0;
				sysConfig.do_Reboot_sta = modbusReg[i];
				dev_do.reboot_sta[0] = modbusReg[i];
				isSaveFlag = 1;
				break;

			case DO0_CHL_STA_REG:
				modbusReg[i] = (modbusReg[i] > 0) ? 1 : 0;
				DO_Ctrl(&dev_do, 0, modbusReg[i]);
				break;

			default:
				break;
		}
	}

	if(isSaveFlag)
		ConfigPara_SaveData_Write(&sysConfig);
}






/*******************************************************************************
** 函数原型：uint16_t MODBUS_RTU_CMD16_Handle(uint8_t regStartAddr, uint8_t regNum, uint8_t *rxData,uint8_t *txData)
** 函数功能：MODBUS 功能码16处理函数
** 输入参数：regStartAddr 寄存器起始地址
			 rxData 接收缓存起始地址
			 txData 发送缓存起始地址
** 输出参数：发送数据长度
** 备    注：

*******************************************************************************/
uint16_t MODBUS_RTU_CMD16_Handle(uint8_t regStartAddr, uint8_t regNum, uint8_t *rxData, uint8_t *txData)
{
	uint16_t len = 0, i = 0, calCRC = 0;

	//如果寄存器数量为0，直接退出
	if (regNum == 0)
		return len;

	//如果写入范围内
	if (regStartAddr >= MODBUS_REG_WRITE_START_ADDR
		&& (regStartAddr + regNum - 1) <= MODBUS_REG_WRITE_END_ADDR)
	{

		//寄存器赋值
		for (i = 0; i < regNum; i++)
		{
			modbusReg[regStartAddr + i] = ((uint16_t)rxData[7 + i * 2]) << 8;
			modbusReg[regStartAddr + i] |= rxData[8 + i * 2];
		}

		MODBUS_RTU_CMD16_Callback(regStartAddr, regNum);

		//回应数据
		memcpy(txData, rxData, 6);
		len = 6;

		//CRC计算数据
		calCRC = usMBCRC16(txData, len);

		//CRC赋值
		txData[len++] = (calCRC >> 8) & 0xFF;
		txData[len++] = calCRC & 0xFF;
	}

	//返回长度
	return len;
}
#endif // MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED





/*******************************************************************************
** 函数原型：uint16_t MODBUS_RTU_Handle(uint8_t *rxData,uint16_t rxLen,uint8_t *txData)
** 函数功能：MODBUS RTU任务处理
** 输入参数：rxData  接收缓存
			 rxLen   接收长度
			 txData  发送缓存
** 输出参数：发送数据长度
** 备    注：

*******************************************************************************/
uint16_t MODBUS_RTU_Handle(uint8_t *rxData, uint8_t rxLen, uint8_t *txData)
{
	uint8_t len = 0;
	uint16_t  regStartAddr = 0, regNum = 0, calCRC = 0, revCRC = 0;

	//不是本机地址
	if (rxData[0] != devAddr)
		return len;

	//数据长度过短
	if (rxLen <= 4)
		return len;

	//CRC比较，若不相等退出
	revCRC = (((uint16_t)rxData[rxLen - 2]) << 8) | rxData[rxLen - 1];
	calCRC = usMBCRC16(rxData, rxLen - 2);
	if (revCRC != calCRC)
		return len;

	//如果起始地址超过长度报错
	regStartAddr = (((uint16_t)rxData[2]) << 8) | rxData[3];
	if (regStartAddr > MODBUS_HOLDREG_NUM)
		return len;

	//数字赋值
	MODBUS_Data_Assignment();

	//根据不同的功能码进行处理
	switch (rxData[1])
	{
#if MB_FUNC_READ_HOLDING_ENABLED
		case 0x03:
			regNum = (((uint16_t)rxData[4]) << 8) | rxData[5];
			len = MODBUS_RTU_CMD03_Handle(regStartAddr, regNum, txData);
			break;
#endif // MB_FUNC_READ_HOLDING_ENABLED

#if MB_FUNC_WRITE_HOLDING_ENABLED
		case 0x06:
			if (IS_WRTER_REG_RANG(regStartAddr))
			{
				memcpy(txData, rxData, rxLen);
				len = rxLen;
				MODBUS_RTU_CMD06_Callback(regStartAddr, ((((uint16_t)rxData[4]) << 8) | rxData[5]));
			}
			break;
#endif // MB_FUNC_WRITE_HOLDING_ENABLED


#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED
		case 0x10:
			regNum = (((uint16_t)rxData[4]) << 8) | rxData[5];
			len = MODBUS_RTU_CMD16_Handle(regStartAddr, regNum, rxData, txData);
			break;
#endif // MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED

	}

	return len;
}
/*******************************************************************************
*    测试日期           测试人            测试结果          处理结果
*
*******************************************************************************/

