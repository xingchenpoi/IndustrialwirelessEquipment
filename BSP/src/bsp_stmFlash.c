/* Includes ------------------------------------------------------------------*/
#include "bsp_stmFlash.h"


uint16_t STMFLASH_BUF[STM_SECTOR_SIZE / 2];//�����2K�ֽ�


/*******************************************************************************
** ����ԭ�ͣ�uint16_t STMFLASH_ReadHalfWord(uint32_t faddr)
** �������ܣ���ȡָ����ַ�İ���(16λ����) 
** ���������faddr:����ַ 
** �����������Ӧ����
** ��    ע��

*******************************************************************************/
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr)
{
	return *(vu16*)faddr;
}



#if STM32_FLASH_WREN	//���ʹ����д   

/*******************************************************************************
** ����ԭ�ͣ�void STMFLASH_Write_NoCheck(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)
** �������ܣ�������д��
** ���������WriteAddr:��ʼ��ַ
			 pBuffer:����ָ��
			 NumToWrite:����(16λ)��   
** �����������
** ��    ע��

*******************************************************************************/
void STMFLASH_Write_NoCheck(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)
{
	uint16_t i;
	for (i = 0; i < NumToWrite; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, WriteAddr, pBuffer[i]);
		WriteAddr += 2;//��ַ����2.
	}
}





/*******************************************************************************
** ����ԭ�ͣ�void STMFLASH_Write(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)
** �������ܣ���ָ����ַ��ʼд��ָ�����ȵ�����
** ���������WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
			 pBuffer:����ָ��
			 NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
** �����������
** ��    ע��

*******************************************************************************/
void STMFLASH_Write(uint32_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite)
{
	uint32_t secpos;	   //������ַ
	uint16_t secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	uint16_t secremain; //������ʣ���ַ(16λ�ּ���)	   
	uint16_t i;
	uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ

	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))return;//�Ƿ���ַ

	HAL_FLASH_Unlock();					//����
	offaddr = WriteAddr - STM32_FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos = offaddr / STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff = (offaddr%STM_SECTOR_SIZE) / 2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain = STM_SECTOR_SIZE / 2 - secoff;		//����ʣ��ռ��С   
	if (NumToWrite <= secremain)secremain = NumToWrite;//�����ڸ�������Χ
	while (1)
	{
		STMFLASH_Read(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);//������������������
		for (i = 0; i < secremain; i++)	//У������
		{
			if (STMFLASH_BUF[secoff + i] != 0XFFFF)break;//��Ҫ����  	  
		}
		if (i < secremain)				//��Ҫ����
		{
			FLASH_PageErase(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE);	//�����������
			FLASH_WaitForLastOperation(FLASH_WAITETIME);            	//�ȴ��ϴβ������
			CLEAR_BIT(FLASH->CR, FLASH_CR_PER);							//���CR�Ĵ�����PERλ���˲���Ӧ����FLASH_PageErase()����ɣ�
																		//����HAL�����沢û������Ӧ����HAL��bug��
			for (i = 0; i < secremain; i++)//����
			{
				STMFLASH_BUF[i + secoff] = pBuffer[i];
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);//д����������  
		}
		else
		{
			FLASH_WaitForLastOperation(FLASH_WAITETIME);       	//�ȴ��ϴβ������
			STMFLASH_Write_NoCheck(WriteAddr, pBuffer, secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 
		}
		if (NumToWrite == secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff = 0;				//ƫ��λ��Ϊ0 	 
			pBuffer += secremain;  	//ָ��ƫ��
			WriteAddr += secremain * 2;	//д��ַƫ��(16λ���ݵ�ַ,��Ҫ*2)	   
			NumToWrite -= secremain;	//�ֽ�(16λ)���ݼ�
			if (NumToWrite > (STM_SECTOR_SIZE / 2))secremain = STM_SECTOR_SIZE / 2;//��һ����������д����
			else secremain = NumToWrite;//��һ����������д����
		}
	};
	HAL_FLASH_Lock();		//����
}


#endif





/*******************************************************************************
** ����ԭ�ͣ�void STMFLASH_Read(uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead)
** �������ܣ���ָ����ַ��ʼ����ָ�����ȵ�����
** ���������ReadAddr:��ʼ��ַ
			 pBuffer:����ָ��
			 NumToWrite:����(16λ)��
** �����������
** ��    ע��

*******************************************************************************/
void STMFLASH_Read(uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead)
{
	uint16_t i;
	for (i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr += 2;//ƫ��2���ֽ�.	
	}
}



/********************************END OF FILE***********************************/