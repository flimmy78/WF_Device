#include "HardwareProfile.h"

_CP1616_Master_Flags CP1616_Master_Flags;
uint8_t CP1616_Master_RxList[MAX_CP1616_Master_RX];
uint16_t CP1616_Master_RxCount;
uint16_t CP1616_Master_NeedRxCount;
uint CP1616_Master_WaitClientAddr;
uint8_t CP1616_Master_WaitCommand;
uint16_t CP1616_Master_WaitClientTick;
//uint8_t CP1616_Master_RxErrTimes;
uint16_t CP1616_Master_WaitClientTime;
uint8_t CP1616_Master_RetryTimes;

void Init_CP1616_Master(void)
{
	SetTx_CP1616_Master();
	CP1616_Master_WaitClientTime=3;
	CP1616_Master_RetryTimes=3;
	//SetCOM1TX();
//	/while(1)
//	{
//		Uart_PutChar(0xff);
//	}
}
void ProcRx_CP1616_Master(uint8_t rx)
{
	if(CP1616_Master_Flags.bRx)//֮ǰû������
		return;
	if(!CP1616_Master_Flags.bWaitDataFromClient)//��ǰû�ڵȴ�
		return;
	CP1616_Master_RxList[CP1616_Master_RxCount++]=rx;
	if(CP1616_Master_RxCount>7)
	{
		if(rx==0x0d && CP1616_Master_RxCount==CP1616_Master_NeedRxCount)
		{			
			CP1616_Master_Flags.bRx=1;			
		}
		else if(CP1616_Master_RxCount>CP1616_Master_NeedRxCount)
		{
			CP1616_Master_RxCount=0;
			CP1616_Master_NeedRxCount=0xffff;
		}
		else if(CP1616_Master_RxCount>MAX_CP1616_Master_RX)
		{
			CP1616_Master_RxCount=0;
			CP1616_Master_NeedRxCount=0xffff;				
		}
	}
	else if(CP1616_Master_RxCount==7)
	{
		CP1616_Master_NeedRxCount=MAKE_INT(CP1616_Master_RxList[5],CP1616_Master_RxList[6])+9;
		if(CP1616_Master_NeedRxCount>MAX_CP1616_Master_RX)
		{
			CP1616_Master_NeedRxCount=0xffff;
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==5)//�ж�����
	{
		if(rx!=CP1616_Master_WaitCommand)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==4)//�жϵ�ַ
	{
		if(rx!=CP1616_Master_WaitClientAddr.u8L)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==3)
	{
		if(rx!=CP1616_Master_WaitClientAddr.u8H)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==2)
	{
		if(rx!=0x16)
		{
			CP1616_Master_RxCount=0;
		}
	}
	else if(CP1616_Master_RxCount==1)
	{
		if(rx!=0x16)
		{
			CP1616_Master_RxCount=0;
		}
	}	
}
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
{
	uint8_t sum;
	uint16_t i;
	CP1616_Master_WaitClientAddr.u16=Addr;
	CP1616_Master_WaitCommand=Command;
	SetTx_CP1616_Master();
	sum=0;
	CP1616_Master_AddTxHeader();
	CP1616_Master_TxByteWithVerify(HIGH_BYTE(Count));
	CP1616_Master_TxByteWithVerify(LOW_BYTE(Count));
	for(i=0;i<Count;i++)
	{
		CP1616_Master_TxByteWithVerify(pBuff[i]);	
	}
	CP1616_Master_AddTxEnder();
	SetRx_CP1616_Master();
	CP1616_Master_Flags.bRx=0;
	CP1616_Master_WaitClientTick=SystemTick;
	CP1616_Master_RxCount=0;
//	CP1616_Master_RxErrTimes=0;
	CP1616_Master_NeedRxCount=0xffff;
	CP1616_Master_Flags.bWaitDataFromClient=1;
}
uint8_t CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
{	
	uint8_t sum,retry;
	uint8_t ret;
	uint16_t i;
	ret=0;
	CP1616_Master_WaitClientAddr.u16=Addr;
	CP1616_Master_WaitCommand=Command;
	retry=CP1616_Master_RetryTimes;
	while(retry!=0)
	{
		SetTx_CP1616_Master();
		sum=0;
		CP1616_Master_AddTxHeader();
		CP1616_Master_TxByteWithVerify(HIGH_BYTE(Count));
		CP1616_Master_TxByteWithVerify(LOW_BYTE(Count));
		for(i=0;i<Count;i++)
		{
			CP1616_Master_TxByteWithVerify(pBuff[i]);	
		}
		CP1616_Master_AddTxEnder();
		SetRx_CP1616_Master();
		CP1616_Master_Flags.bRx=0;
		CP1616_Master_WaitClientTick=SystemTick;
		CP1616_Master_RxCount=0;
		//CP1616_Master_RxErrTimes=0;
		CP1616_Master_NeedRxCount=0xffff;
		CP1616_Master_Flags.bWaitDataFromClient=1;
		while(1)
		{
			if(CP1616_Master_Flags.bRx)
				break;
			if((SystemTick-CP1616_Master_WaitClientTick)>CP1616_Master_WaitClientTime)//200ms�ȴ���ʱ
				break;
		}
		CP1616_Master_Flags.bWaitDataFromClient=0;
		if(CP1616_Master_Flags.bRx)
		{
			ret=1;
			break;
		}
		CP1616_Master_WaitClientInterval();
		retry--;
	}
	SetTx_CP1616_Master();
	return ret;
}

