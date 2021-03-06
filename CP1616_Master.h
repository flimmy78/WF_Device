#ifndef __CP1616_Master_h__
#define __CP1616_Master_h__


typedef union   
{
	struct
	{
		unsigned bRx:1;
		unsigned bWaitDataFromClient:1;	
	};
	uint8_t AllFlag;
} _CP1616_Master_Flags;        // general flags


#ifndef CP1616_Master_TxByte_Ex
#define CP1616_Master_TxByteWithVerify(x) Uart1_VerifySumAddTxByte(x)
#define CP1616_Master_TxByte(x) Uart1_PutChar(x)
#endif

#ifndef CP1616_Master_WaitClientInterval_Ex
#define CP1616_Master_WaitClientInterval() __delay_20ms(5);
#endif

#define pCP1616_MasterData 7
#ifndef CheckVerify_CP1616_Master
#define CheckVerify_CP1616_Master()	sum=GetVerify_Sum(CP1616_Master_RxList,CP1616_Master_NeedRxCount-2); \
												if(sum==CP1616_Master_RxList[CP1616_Master_NeedRxCount-2])	\
													sum=1;	\
												else		\
													sum=0;
#endif

#define CP1616_Master_AddTxHeader()	CP1616_Master_TxByteWithVerify(0x16);	\
									CP1616_Master_TxByteWithVerify(0x16);	\
									CP1616_Master_TxByteWithVerify(CP1616_Master_WaitClientAddr.u8H);	\
									CP1616_Master_TxByteWithVerify(CP1616_Master_WaitClientAddr.u8L);	\
									CP1616_Master_TxByteWithVerify(CP1616_Master_WaitCommand);
#define CP1616_Master_AddTxEnder()	CP1616_Master_TxByte(sum);	\
									CP1616_Master_TxByte(0x0d);

#ifndef MAX_CP1616_Master_RX
#define MAX_CP1616_Master_RX 50
#endif

#ifndef SetRx_CP1616_Master_Ex
#define SetRx_CP1616_Master() while(Uart_TRMT==0);__delay_ms(1);CP1616_RS485DE_W=0
#endif

#ifndef SetTx_CP1616_Master_Ex
#define SetTx_CP1616_Master() CP1616_RS485DE_W=1;__delay_ms(1)
#endif

// #ifndef CP1616_Master_RetryTimes
// #define CP1616_Master_RetryTimes 3
// #endif
extern _CP1616_Master_Flags CP1616_Master_Flags;
extern uint8_t CP1616_Master_RxList[MAX_CP1616_Master_RX];
extern uint16_t CP1616_Master_RxCount;
extern uint16_t CP1616_Master_NeedRxCount;
extern uint CP1616_Master_WaitClientAddr;
extern uint8_t CP1616_Master_WaitCommand;
extern uint16_t CP1616_Master_WaitClientTick;
//extern uint8_t CP1616_Master_RxErrTimes;
extern uint16_t CP1616_Master_WaitClientTime;
extern uint8_t CP1616_Master_RetryTimes;

void Init_CP1616_Master(void);
void ProcRx_CP1616_Master(uint8_t rx);
uint8_t CP1616_MasterWaitClientData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
void CP1616_MasterSendData(uint16_t Addr,uint8_t Command,uint8_t* pBuff,uint16_t Count);
#endif
