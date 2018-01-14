#include "TCN75.h"
#ifdef SimI2C
#include "SimI2C.h"
#endif
//#define TCN75_DATA_W LATC1   
//#define TCN75_WR_W  LATC2   
//#define TCN75_CS_W 	 LATC3	
//
//#define TCN75_DIN_DIR RC1    
//#define TCN75_WR_DIR  RC2    
//#define TCN75_CS_DIR 	 RC3

#ifdef SimI2C
void TCN75_Init(void)
{
	SimI2C_Init();
}
uint8_t TCN75_ReadReg(uint8_t RegPoint)
{
	uint8_t ErrTimes=TCN75_RetryCount;
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //д��ַ
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;
		SimI2C_SendByte(RegPoint);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr|0x01);          //����ַ
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;
		TCN75_RegReadResualt.u8H=SimI2C_ReadByte();
		SimI2C_Ack();
		TCN75_RegReadResualt.u8L=SimI2C_ReadByte();
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
uint8_t TCN75_SetConfig(void)
{
	uint8_t ErrTimes=TCN75_RetryCount;
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //д��ַ
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;		
		SimI2C_SendByte(0x01);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;
		SimI2C_SendByte(TCN75_Config.AllFlag);          //����ַ
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;		
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
uint8_t TCN75_ReadConfig(void)
{
	uint8_t ErrTimes=TCN75_RetryCount;
	uint8_t bRight=0;
	while(ErrTimes--)
	{
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr&0xfe);          //д��ַ
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;		
		SimI2C_SendByte(0x01);
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;
		SimI2C_Start();
		SimI2C_SendByte(TCN75_Addr|0x01);          //����ַ		
		if(SimI2C_RecAck())  //iic_testack())  //ack=0 ��ʾ����������ȷ�������ǳ���
			continue;	
		TCN75_Config.AllFlag=SimI2C_ReadByte();
		SimI2C_NoAck();
		bRight=1;
		break;
	}
	SimI2C_Stop();
	return bRight;
}
#endif
