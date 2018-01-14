#include "HardwareProfile.h"
#include "Si4432.h"

//#define Si4432_NSEL_DIR	TRISA1
//#define Si4432_SCL_DIR	TRISA1
//#define Si4432_SDI_DIR	TRISA2
//#define Si4432_SDO_DIR	TRISA0
//
//#define Si4432_NSEL	RA1
//#define Si4432_SCL	RA1
//#define Si4432_SDI	RA0 //оƬ������
//#define Si4432_SDO	RA2	//оƬ�����
void Si4432_Init(void)
{	
	Si4432_NSEL_DIR=0;
	Si4432_SCL_DIR=0;
	Si4432_SDO_DIR=1;
	Si4432_SDI_DIR=0;
	Si4432_NSEL_W=1;
	Si4432_SCL_W=1;	//����ʱ���ź�
}

void Si4432_WriteRegister(uint8_t reg,uint8_t value)
{
	uint8_t i;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//����ʱ���ź�
	reg=reg|0x80;//д
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((reg&0x80)==0x80)	//�жϴ����͵�����λ��0��1
		{
			Si4432_SDI_W=1;	//����������λ��1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//�жϴ����͵�����λ��0��1
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((value&0x80)==0x80)	//�жϴ����͵�����λ��0��1
		{
			Si4432_SDI_W=1;	//����������λ��1
		}
		NOP();
		Si4432_SCL_W=1;
		value=value<<1;	//�жϴ����͵�����λ��0��1
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	Si4432_NSEL_W=1;
}
uint8_t Si4432_ReadRegister(uint8_t reg)
{
	uint8_t i,value;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//����ʱ���ź�
	value=reg&0x7f;//д
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if((value&0x80)==0x80)	//�жϴ����͵�����λ��0��1
		{
			Si4432_SDI_W=1;	//����������λ��1
		}
		NOP();
		Si4432_SCL_W=1;
		value=value<<1;	//�жϴ����͵�����λ��0��1
		Si4432_SCL_W=0;	//����ʱ���ź�
	}	
#ifdef SI4463
	while(1)
	{
		value=0;
		for(i=0;i<8;i++)
		{

			value=value<<1;
			if(Si4432_SDO_R==1)
				value=value|0x01;
			Si4432_SCL_W=1;
			NOP();		
			Si4432_SCL_W=0;	//����ʱ���ź�
		}
		Si4432_NSEL_W=1;
		if(value==0xff)
			break;
	}
	value=0;
	for(i=0;i<8;i++)
	{

		value=value<<1;
		if(Si4432_SDO_R==1)
			value=value|0x01;
		Si4432_SCL_W=1;
		NOP();		
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	Si4432_NSEL_W=1;
#else
	value=0;
	for(i=0;i<8;i++)
	{

		value=value<<1;
		if(Si4432_SDO_R==1)
			value=value|0x01;
		Si4432_SCL_W=1;
		NOP();		
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	Si4432_NSEL_W=1;
#endif
	
	return value;
}
void Si4432_WriteRegisters(uint8_t reg,uint8_t Count,const uint8_t *p)
{
	uint8_t i,j,v;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//����ʱ���ź�
	reg=reg|0x80;//д
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if(reg&0x80==0x80)	//�жϴ����͵�����λ��0��1
		{
			Si4432_SDI_W=1;	//����������λ��1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//�жϴ����͵�����λ��0��1
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	for(j=0;j<Count;j++)
	{
		v=p[j];
		for(i=0;i<8;i++)
		{
			Si4432_SDI_W=0;
			if(v&0x80==0x80)	//�жϴ����͵�����λ��0��1
			{
				Si4432_SDI_W=1;	//����������λ��1
			}
			NOP();
			Si4432_SCL_W=1;
			v=v<<1;	//�жϴ����͵�����λ��0��1
			Si4432_SCL_W=0;	//����ʱ���ź�
		}
	}
}
void Si4432_ReadRegisters(uint8_t reg,uint8_t Count,uint8_t *p)
{
	uint8_t i,j,value;
	Si4432_NSEL_W=0;
	Si4432_SCL_W=0;	//����ʱ���ź�
	reg=reg&0x7f;//д
	for(i=0;i<8;i++)
	{
		Si4432_SDI_W=0;
		if(reg&0x80==0x80)	//�жϴ����͵�����λ��0��1
		{
			Si4432_SDI_W=1;	//����������λ��1
		}
		NOP();
		Si4432_SCL_W=1;
		reg=reg<<1;	//�жϴ����͵�����λ��0��1
		Si4432_SCL_W=0;	//����ʱ���ź�
	}
	for(j=0;j<Count;j++)
	{
		value=0;
		for(i=0;i<8;i++)
		{
			Si4432_SCL_W=1;
			value=value<<1;
			if(Si4432_SDO_R==1)
				value=value|0x01;	
			Si4432_SCL_W=0;	//����ʱ���ź�
		}
		p[j]=value;
	}
}
