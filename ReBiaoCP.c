#include "HardwareProfile.h"

_ReBiaoCP_Flags ReBiaoCP_Flags;
uint8_t ReBiaoCP_RxList[MAX_ReBiaoCP_RX];
uint8_t ReBiaoCP_RxCount;
uint8_t ReBiaoCP_NeedRxCount;
uint ReBiaoCP_WaitClientAddr;
uint8_t ReBiaoCP_WaitCommand;
uint16_t ReBiaoCP_WaitClientTick;
//uint8_t ReBiaoCP_RxErrTimes;
uint16_t ReBiaoCP_WaitClientTime;
uint8_t ReBiaoCP_RetryTimes;

void Init_ReBiaoCP(void)
{
	SetTx_ReBiaoCP();
	ReBiaoCP_WaitClientTime=3;
	ReBiaoCP_RetryTimes=3;
	//SetCOM1TX();
//	/while(1)
//	{
//		Uart_PutChar(0xff);
//	}
}
void ProcRx_ReBiaoCP(uint8_t rx)
{
	if(ReBiaoCP_Flags.bRx)//֮ǰû������
		return;
	if(!ReBiaoCP_Flags.bWaitDataFromClient)//��ǰû�ڵȴ�
		return;
	ReBiaoCP_RxList[ReBiaoCP_RxCount++]=rx;
	if(ReBiaoCP_RxCount>7)
	{
		if(rx==0x16 && ReBiaoCP_RxCount==ReBiaoCP_NeedRxCount)
		{			
			ReBiaoCP_Flags.bRx=1;			
		}
		else if(ReBiaoCP_RxCount>ReBiaoCP_NeedRxCount)
		{
			ReBiaoCP_RxCount=0;
			ReBiaoCP_NeedRxCount=0xff;
		}
		else if(ReBiaoCP_RxCount>MAX_ReBiaoCP_RX)
		{
			ReBiaoCP_RxCount=0;
			ReBiaoCP_NeedRxCount=0xff;				
		}
	}
// 	else if(ReBiaoCP_RxCount==7)//������Ϣ�ֶ�
// 	{
// 		
// 	}
// 	else if(ReBiaoCP_RxCount==6)//�жϵ�ַ
// 	{
// 		if(rx!=ReBiaoCP_WaitCommand)
// 		{
// 			ReBiaoCP_RxCount=0;
// 		}
// 	}
// 	else if(ReBiaoCP_RxCount==5)//�ж�����
// 	{
// 		if(rx!=ReBiaoCP_WaitClientAddr.u8L)
// 		{
// 			ReBiaoCP_RxCount=0;
// 		}
// 	}
	else if(ReBiaoCP_RxCount==3)
	{
		if(ReBiaoCP_RxList[1]==ReBiaoCP_RxList[2])
		{
			ReBiaoCP_NeedRxCount=ReBiaoCP_RxList[1]+6;
		}
		else
			ReBiaoCP_RxCount=0;
	}
	else if(ReBiaoCP_RxCount==1)
	{
		if(rx!=0x68)
		{
			ReBiaoCP_RxCount=0;
		}
	}	
}
// void ReBiaoCPSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
// {
// 	uint8_t sum;
// 	uint16_t i;
// 	ReBiaoCP_WaitClientAddr.u16=Addr;
// 	ReBiaoCP_WaitCommand=Command;
// 	SetTx_ReBiaoCP();
// 	sum=0;
// 	ReBiaoCP_AddTxHeader();
// 	ReBiaoCP_TxByteWithVerify(HIGH_BYTE(Count));
// 	ReBiaoCP_TxByteWithVerify(LOW_BYTE(Count));
// 	for(i=0;i<Count;i++)
// 	{
// 		ReBiaoCP_TxByteWithVerify(pBuff[i]);	
// 	}
// 	ReBiaoCP_AddTxEnder();
// 	SetRx_ReBiaoCP();
// 	ReBiaoCP_Flags.bRx=0;
// 	ReBiaoCP_WaitClientTick=SystemTick;
// 	ReBiaoCP_RxCount=0;
// //	ReBiaoCP_RxErrTimes=0;
// 	ReBiaoCP_NeedRxCount=0xff;
// 	ReBiaoCP_Flags.bWaitDataFromClient=1;
// }
// uint8_t ReBiaoCPWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count)
// {	
// 	uint8_t sum,retry;
// 	uint8_t ret;
// 	uint16_t i;
// 	ret=0;
// 	ReBiaoCP_WaitClientAddr.u16=Addr;
// 	ReBiaoCP_WaitCommand=Command;
// 	retry=ReBiaoCP_RetryTimes;
// 	while(retry!=0)
// 	{
// 		SetTx_ReBiaoCP();
// 		sum=0;
// 		ReBiaoCP_AddTxHeader();
// 		ReBiaoCP_TxByteWithVerify(HIGH_BYTE(Count));
// 		ReBiaoCP_TxByteWithVerify(LOW_BYTE(Count));
// 		for(i=0;i<Count;i++)
// 		{
// 			ReBiaoCP_TxByteWithVerify(pBuff[i]);	
// 		}
// 		ReBiaoCP_AddTxEnder();
// 		SetRx_ReBiaoCP();
// 		ReBiaoCP_Flags.bRx=0;
// 		ReBiaoCP_WaitClientTick=SystemTick;
// 		ReBiaoCP_RxCount=0;
// 		//ReBiaoCP_RxErrTimes=0;
// 		ReBiaoCP_NeedRxCount=0xff;
// 		ReBiaoCP_Flags.bWaitDataFromClient=1;
// 		while(1)
// 		{
// 			if(ReBiaoCP_Flags.bRx)
// 				break;
// 			if((SystemTick-ReBiaoCP_WaitClientTick)>ReBiaoCP_WaitClientTime)//200ms�ȴ���ʱ
// 				break;
// 		}
// 		ReBiaoCP_Flags.bWaitDataFromClient=0;
// 		if(ReBiaoCP_Flags.bRx)
// 		{
// 			ret=1;
// 			break;
// 		}
// 		ReBiaoCP_WaitClientInterval();
// 		retry--;
// 	}
// 	SetTx_ReBiaoCP();
// 	return ret;
// }

uint8_t ReBiaoCP_Read10(uint8_t Addr)
{	
	uint8_t CS,retry;
	uint8_t ret;
	uint16_t i;
	ret=0;
	ReBiaoCP_WaitClientAddr.u16=Addr;
	retry=ReBiaoCP_RetryTimes;
	while(retry!=0)
	{
		//SetTx_ReBiaoCP();
		ReBiaoCP_TxByte(0x10);
		ReBiaoCP_TxByte(0x5b);
		ReBiaoCP_TxByte(Addr);
		CS=(uint8_t)(0x5b+Addr);
		ReBiaoCP_TxByte(CS);
		ReBiaoCP_TxByte(0x16);
		//SetRx_ReBiaoCP();
		ReBiaoCP_Flags.bRx=0;
		ReBiaoCP_WaitClientTick=SystemTick;
		ReBiaoCP_RxCount=0;
		//ReBiaoCP_RxErrTimes=0;
		ReBiaoCP_NeedRxCount=0xff;
		ReBiaoCP_Flags.bWaitDataFromClient=1;
		while(1)
		{
			if(ReBiaoCP_Flags.bRx)
				break;
			if((SystemTick-ReBiaoCP_WaitClientTick)>ReBiaoCP_WaitClientTime)//200ms�ȴ���ʱ
				break;
		}
		ReBiaoCP_Flags.bWaitDataFromClient=0;
		if(ReBiaoCP_Flags.bRx)
		{
			ret=1;
			break;
		}
		ReBiaoCP_WaitClientInterval();
		retry--;
	}
	//SetTx_ReBiaoCP();
	return ret;
}
