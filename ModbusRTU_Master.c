#include "HardwareProfile.h"
#include "ModbusRTU_Master.h"
uint8_t ModbusRTU_Master_RxList[MAX_ModbusRTU_Master_RX];
uint8_t ModbusRTU_Master_RxCount;
uint8_t ModbusRTU_Master_NeedRxCount;
uint8_t ModbusRTU_Master_TargetAddr;
//uint ModbusRTU_Master_FirstRegAddr;
uint8_t ModbusRTU_Master_RetryTimes;
uint16_t ModbusRTU_Master_WaitClientTick;
uint16_t ModbusRTU_Master_WaitClientTime;

uint8_t CurCommand;//��ǰ������ָ���

_ModbusRTU_Master_Flags ModbusRTU_Master_Flags;
void Init_ModbusRTU_Master(void)
{
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_RetryTimes=3;
	ModbusRTU_Master_WaitClientTime=3;
}

void ProcRx_ModbusRTU_Master(uint8_t rx)
{
	if(ModbusRTU_Master_Flags.bRx)//֮ǰû������
		return;
	if(!ModbusRTU_Master_Flags.bWaitClient)//��ǰû�ڵȴ�
		return;
	ModbusRTU_Master_RxList[ModbusRTU_Master_RxCount++]=rx;
	if(ModbusRTU_Master_RxCount>3)
	{
		if(ModbusRTU_Master_RxCount==ModbusRTU_Master_NeedRxCount)
		{			
			ModbusRTU_Master_Flags.bRx=1;			
		}
		else if(ModbusRTU_Master_RxCount>ModbusRTU_Master_NeedRxCount)
		{
			ModbusRTU_Master_RxCount=0;
			ModbusRTU_Master_NeedRxCount=0xff;
		}
		else if(ModbusRTU_Master_RxCount>MAX_ModbusRTU_Master_RX)
		{
			ModbusRTU_Master_RxCount=0;
			ModbusRTU_Master_NeedRxCount=0xff;				
		}
	}	
	else if(ModbusRTU_Master_RxCount==3)//���ڶ��������ֽ�����
	{
		switch(CurCommand)
		{
		case 0x03://����ӻ��Ĵ���������ʱӦ����rx+5���ֽ�
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		case 0x04://������Ĵ���������ʱӦ����rx+5���ֽ�
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		}
	}
	else if(ModbusRTU_Master_RxCount==2)//�����
	{
		if(rx!=CurCommand)
		{
			ModbusRTU_Master_RxCount=0;
		}
		else
		{
			switch(CurCommand)
			{
			case 0x10://д��ӻ��Ĵ���������ʱӦ����8���ֽ�
				ModbusRTU_Master_NeedRxCount=8;
				break;
			}
		}
	}
	else if(ModbusRTU_Master_RxCount==1)//�ӻ���ַ
	{
		if(rx!=ModbusRTU_Master_TargetAddr)
		{
			ModbusRTU_Master_RxCount=0;
		}
	}	
}
void ModbusRTU_Master_SendCommand16(uint16_t RegAddr,uint8_t *pBuff,uint8_t count)
{
	uint8_t i;
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	crc.u16=0xffff;
	CurCommand=0x10;
	SetTx_ModbusRTU_Master();
  	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
  	ModbusRTU_Master_VerifyTxByte(0x10);
  	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
  	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
  	i=count>>1;
  	ModbusRTU_Master_VerifyTxByte(0);
  	ModbusRTU_Master_VerifyTxByte(i);
  	ModbusRTU_Master_VerifyTxByte(count);
  	for(i=0;i<count;i++)
  	{
  		ModbusRTU_Master_VerifyTxByte(pBuff[i]);
  	}
  	ModbusRTU_Master_TxByte(crc.u8H);
  	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand16(uint16_t RegAddr,uint8_t* pBuff,uint16_t Count)
{	
	uint8_t i;
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x10;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x10);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		i=Count>>1;
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(i);
		ModbusRTU_Master_VerifyTxByte(Count);
		for(i=0;i<Count;i++)
		{
			ModbusRTU_Master_VerifyTxByte(pBuff[i]);
		}
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms�ȴ���ʱ
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
void ModbusRTU_Master_SendCommand03(uint16_t RegAddr,uint8_t count)
{
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	crc.u16=0xffff;
	CurCommand=0x03;
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x03);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand03(uint16_t RegAddr,uint8_t count)
{
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x03;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x03);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms�ȴ���ʱ
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
void ModbusRTU_Master_SendCommand04(uint16_t RegAddr,uint8_t count)
{
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	crc.u16=0xffff;
	CurCommand=0x04;
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x04);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand04(uint16_t RegAddr,uint8_t count)
{
	uint crc;	
	uint8_t uIndex ; /* CRCѭ���е����� */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x04;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x04);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=SystemTick;
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if((SystemTick-ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms�ȴ���ʱ
				break;
		}
		ModbusRTU_Master_Flags.bWaitClient=0;
		if(ModbusRTU_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		ModbusRTU_Master_WaitClientInterval();
		retry--;
	}
	SetTx_ModbusRTU_Master();
	return ret;
}
