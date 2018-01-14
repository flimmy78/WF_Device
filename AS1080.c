#include "HardwareProfile.h"

#ifdef SimI2C
void AS1080_Init(void)
{
	SimI2C_Init();
	uint8_t i;
	AS1080_SendByte(0x0F, 0x80);     	// Write Enable. The WR_EN register in bit 7 needs to be set to ��1�� before writing to any of the RW registers.
	__delay_ms(2);
	AS1080_SendByte(0x0C, 0x1F);        //set Register 0Ch = 1Fh (default is 09h) and 0Dh = 7Fh (default is 29h).  �����ڿ��ټ��״̬
	__delay_ms(2);
	AS1080_SendByte(0x0D, 0x7F);
	__delay_ms(2);

	for(i=0x10;i<0x1c;i++)
	{
		AS1080_SendByte(i, 0x19);          // adjusts the detection threshold for each individual key. ����ÿ��������������
		__delay_ms(2);
	}
	AS1080_SendByte(0x0F, 0x00);     		// Write disable. The WR_EN register in bit 7 needs to be set to ��1�� before writing to any of the RW registers.
	__delay_ms(20);
}

void AS1080_SendByte(uint8_t addr,uint8_t dat)
{
	while(1)
	{
		SimI2C_Start();
		SimI2C_SendByte(AS1080Addr);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		SimI2C_SendByte(addr);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		SimI2C_SendByte(dat);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		SimI2C_Stop();
		break;
	}
}

uint8_t AS1080_ReadByte(uint8_t addr)
{
	uint8_t dat;
	while(1)
	{
		SimI2C_Start();
		SimI2C_SendByte(AS1080Addr);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		SimI2C_SendByte(addr);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		SimI2C_Start();
		dat=AS1080Addr|0x01;
		SimI2C_SendByte(dat);
		if(SimI2C_RecAck())
			continue;//��Ӧ�𷵻ص�ѭ��,��ʾ����
		dat = SimI2C_ReadByte();
		SimI2C_NoAck();
		SimI2C_Stop();
		break;
	}
	return dat;
}
#endif



