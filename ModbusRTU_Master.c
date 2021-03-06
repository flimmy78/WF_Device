#include "ModbusRTU_Master.h"
#include "TypeDefine.h"
#include "wfDefine.h"
#include "Verify.h"
#include "stm32\wfSys.h"
#include "..\ZXJ\DiShengControl3\wf\ModbusRTU_Master_Conf.h"
uint8_t ModbusRTU_Master_RxList[MAX_ModbusRTU_Master_RX];
#ifdef MCU_STM32
	uint32_t ModbusRTU_Master_RxCount;
	uint32_t ModbusRTU_Master_NeedRxCount;
	uint32_t ModbusRTU_Master_TargetAddr;
	uint32_t ModbusRTU_Master_RetryTimes;
	uint32_t ModbusRTU_Master_WaitClientTick;
	uint32_t ModbusRTU_Master_WaitClientTime;
	uint32_t CurCommand;//当前操作的指令号
#else
	uint8_t ModbusRTU_Master_RxCount;
	uint8_t ModbusRTU_Master_NeedRxCount;
	uint8_t ModbusRTU_Master_TargetAddr;
	uint8_t ModbusRTU_Master_RetryTimes;
	uint16_t ModbusRTU_Master_WaitClientTick;
	uint16_t ModbusRTU_Master_WaitClientTime;
	uint8_t CurCommand;//当前操作的指令号
#endif

#ifdef ModbusRTU_Master_UseTxList
	uint8_t ModbusRTU_Master_TxList[MAX_ModbusRTU_Master_RX];
	uint32_t ModbusRTU_Master_TxCount;
#endif


_ModbusRTU_Master_Flags ModbusRTU_Master_Flags;
void Init_ModbusRTU_Master(void)
{
	SetTx_ModbusRTU_Master();
	ModbusRTU_Master_RetryTimes=3;
	ModbusRTU_Master_WaitClientTime=3;
}

void ProcRx_ModbusRTU_Master(uint8_t rx)
{
	if(ModbusRTU_Master_Flags.bRx)//之前没处理完
		return;
	if(!ModbusRTU_Master_Flags.bWaitClient)//当前没在等待
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
	else if(ModbusRTU_Master_RxCount==3)//对于读来讲是字节数量
	{
		switch(CurCommand)
		{
		case 0x03://读入从机寄存器，接收时应接收rx+5个字节
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		case 0x04://读输入寄存器，接收时应接收rx+5个字节
			ModbusRTU_Master_NeedRxCount=rx+5;
			if(ModbusRTU_Master_NeedRxCount>MAX_ModbusRTU_Master_RX)
				ModbusRTU_Master_RxCount=0;
			break;
		}
	}
	else if(ModbusRTU_Master_RxCount==2)//命令号
	{
		if(rx!=CurCommand)
		{
			ModbusRTU_Master_RxCount=0;
		}
		else
		{
			switch(CurCommand)
			{
			case 0x10://写入从机寄存器，接收时应接收8个字节
				ModbusRTU_Master_NeedRxCount=8;
				break;
			}
		}
	}
	else if(ModbusRTU_Master_RxCount==1)//从机地址
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
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x10;
	SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
	ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
	ModbusRTU_Master_TxList[1]=0x10;
	ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
	ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
	i=count>>1;
	ModbusRTU_Master_TxList[4]=0;
	ModbusRTU_Master_TxList[5]=i;
	ModbusRTU_Master_TxList[6]=count;
	for(i=0;i<count;i++)
	{
		ModbusRTU_Master_TxList[7+i]=pBuff[i];
	}
	crc=GetVerify_CRC16(ModbusRTU_Master_TxList,7+count);
	ModbusRTU_Master_TxList[7+count]=crc.u8H;
	ModbusRTU_Master_TxList[7+count+1]=crc.u8L;
	ModbusRTU_Master_TxDataBuf(7+count+2);
#else
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
#endif  	
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand16(uint16_t RegAddr,uint8_t* pBuff,uint16_t count)
{	
	uint8_t i;
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x10;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
		ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
		ModbusRTU_Master_TxList[1]=0x10;
		ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
		ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
		i=count>>1;
		ModbusRTU_Master_TxList[4]=0;
		ModbusRTU_Master_TxList[5]=i;
		ModbusRTU_Master_TxList[6]=count;
		for(i=0;i<count;i++)
		{
			ModbusRTU_Master_TxList[7+i]=pBuff[i];
		}
		crc=GetVerify_CRC16(ModbusRTU_Master_TxList,7+count);
		ModbusRTU_Master_TxList[7+count]=crc.u8H;
		ModbusRTU_Master_TxList[7+count+1]=crc.u8L;
		ModbusRTU_Master_TxDataBuf(7+count+2);
#else
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
#endif  		
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=wfGetTick();
		ModbusRTU_Master_RxCount=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if(GetDeltaTick(ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)
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
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x03;
	SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
	ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
	ModbusRTU_Master_TxList[1]=0x03;
	ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
	ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
	ModbusRTU_Master_TxList[4]=0;
	ModbusRTU_Master_TxList[5]=count;	
	crc=GetVerify_CRC16(ModbusRTU_Master_TxList,6);
	ModbusRTU_Master_TxList[6]=crc.u8H;
	ModbusRTU_Master_TxList[7]=crc.u8L;
	ModbusRTU_Master_TxDataBuf(8);
#else
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x03);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
#endif 
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand03(uint16_t RegAddr,uint8_t count)
{
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x03;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
		ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
		ModbusRTU_Master_TxList[1]=0x03;
		ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
		ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
		ModbusRTU_Master_TxList[4]=0;
		ModbusRTU_Master_TxList[5]=count;	
		crc=GetVerify_CRC16(ModbusRTU_Master_TxList,6);
		ModbusRTU_Master_TxList[6]=crc.u8H;
		ModbusRTU_Master_TxList[7]=crc.u8L;
		ModbusRTU_Master_TxDataBuf(8);
#else
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x03);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
#endif 
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=wfGetTick();
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if(GetDeltaTick(ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms等待超时
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
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	crc.u16=0xffff;
	CurCommand=0x04;
	SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
	ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
	ModbusRTU_Master_TxList[1]=0x04;
	ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
	ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
	ModbusRTU_Master_TxList[4]=0;
	ModbusRTU_Master_TxList[5]=count;	
	crc=GetVerify_CRC16(ModbusRTU_Master_TxList,6);
	ModbusRTU_Master_TxList[6]=crc.u8H;
	ModbusRTU_Master_TxList[7]=crc.u8L;
	ModbusRTU_Master_TxDataBuf(8);
#else
	ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
	ModbusRTU_Master_VerifyTxByte(0x04);
	ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
	ModbusRTU_Master_VerifyTxByte(0);
	ModbusRTU_Master_VerifyTxByte(count);
	ModbusRTU_Master_TxByte(crc.u8H);
	ModbusRTU_Master_TxByte(crc.u8L);
#endif 	
	SetRx_ModbusRTU_Master();
}
uint8_t ModbusRTU_Master_ProcCommand04(uint16_t RegAddr,uint8_t count)
{
	u16_wf crc;	
	uint8_t uIndex ; /* CRC循环中的索引 */
	uint8_t retry;
	uint8_t ret;	
	CurCommand=0x04;
	retry=ModbusRTU_Master_RetryTimes;
	ret=0;
	while(retry!=0)
	{
		crc.u16=0xffff;
		SetTx_ModbusRTU_Master();
#ifdef ModbusRTU_Master_UseTxList
		ModbusRTU_Master_TxList[0]=ModbusRTU_Master_TargetAddr;
		ModbusRTU_Master_TxList[1]=0x04;
		ModbusRTU_Master_TxList[2]=HIGH_BYTE(RegAddr);
		ModbusRTU_Master_TxList[3]=LOW_BYTE(RegAddr);
		ModbusRTU_Master_TxList[4]=0;
		ModbusRTU_Master_TxList[5]=count;	
		crc=GetVerify_CRC16(ModbusRTU_Master_TxList,6);
		ModbusRTU_Master_TxList[6]=crc.u8H;
		ModbusRTU_Master_TxList[7]=crc.u8L;
		ModbusRTU_Master_TxDataBuf(8);
#else
		ModbusRTU_Master_VerifyTxByte(ModbusRTU_Master_TargetAddr);
		ModbusRTU_Master_VerifyTxByte(0x04);
		ModbusRTU_Master_VerifyTxByte(HIGH_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(LOW_BYTE(RegAddr));
		ModbusRTU_Master_VerifyTxByte(0);
		ModbusRTU_Master_VerifyTxByte(count);
		ModbusRTU_Master_TxByte(crc.u8H);
		ModbusRTU_Master_TxByte(crc.u8L);
#endif
		SetRx_ModbusRTU_Master();
		ModbusRTU_Master_Flags.bRx=0;
		ModbusRTU_Master_Flags.bWaitClient=1;
		ModbusRTU_Master_WaitClientTick=wfGetTick();
		ModbusRTU_Master_RxCount=0;
		//ModbusRTU_Master_RxErrTimes=0;
		ModbusRTU_Master_NeedRxCount=0xff;
		while(1)
		{
			if(ModbusRTU_Master_Flags.bRx)
				break;
			if(GetDeltaTick(ModbusRTU_Master_WaitClientTick)>ModbusRTU_Master_WaitClientTime)//200ms等待超时
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
