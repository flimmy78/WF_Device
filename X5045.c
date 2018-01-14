#include "HardwareProfile.h"
#include "SimSPI.h"
#include "X5045.h"

//#define X5045_CS_DIR	TRISA2
//#define X5045_WP_DIR	TRISA0
//
//#define X5045_CS	RA1
//#define X5045_WP	RA2
//д����
void X5045_WREN()
{
	X5045_WP=1;//�ر�д����
	X5045_CS=0;
	SimSPI_Proc(0b00000110);
	X5045_CS=1;
}
//д��ֹ
void X5045_WRDI()
{
	X5045_WP=0;//����д����
	X5045_CS=0;
	SimSPI_Proc(0b00000100);
	X5045_CS=1;
}
void X5045_Init()
{
	X5045_CS_DIR=0;
	X5045_WP_DIR=0;
	SimSPI_Init();
	X5045_WP=0;//����д����
	X5045_CS=0;
	NOP();
	X5045_CS=1;
}
//��λ���Ź�
void X5045_RstWDT()
{
	if(X5045_CS==0)//��ǰ���ڹ���״̬
		return;
	X5045_CS=0;
	NOP();
	X5045_CS=1;
}
//5045״̬�Ĵ�����������
//�ȴ�X5045�����ڲ�д����
void X5045_WIPCheck()
{
	uint8_t dat;
	do
	{
		dat=X5045_RDSR();
		dat&=0x01;		
	}
	while(dat);
}
uint8_t X5045_RDSR()
{
	uint8_t x;
	X5045_CS=0;
	SimSPI_Proc(0b00000101);
	x=SimSPI_Proc(0);
	X5045_CS=1;
	return (x);
}
//5045״̬�Ĵ���д�����
void X5045_WRSR(uint8_t x)
{
	X5045_WREN();
	X5045_CS=0;
	SimSPI_Proc(0b00000001);
	SimSPI_Proc(x);
	X5045_CS=1;
	X5045_WIPCheck();	
	X5045_WRDI();
}
//��X5045д�뵥�ֽ�����,���룺x,��д����,address,д�����ݵĵ�ַ
#ifndef X5045_MorePage
void X5045_WriteByte(uint8_t address,uint8_t x)
{
    X5045_WREN();
    X5045_CS=0;
    SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    SimSPI_Proc(x);
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount)
{
    uint8_t i,x;
    X5045_WREN();
    X5045_CS=0;
    SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    for(i=0;i<wCount;i++)
    {
        x=pW[i];
        SimSPI_Proc(x);
    }	
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
uint8_t X5045_ReadByte(uint8_t address)
{
    uint8_t x;
    X5045_CS=0;
    SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    x=SimSPI_Proc(0);
    X5045_CS=1;
    return (x);
}
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount)
{
    uint8_t i,x;
    X5045_CS=0;
    SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    for(i=0;i<rCount;i++)
    {
        x=SimSPI_Proc(0);
        pR[i]=x;
    }	
    X5045_CS=1;
}
#else
void X5045_WriteByte(uint8_t address,uint8_t x,uint8_t page)
{
    X5045_WREN();
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001010);
    else
        SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    SimSPI_Proc(x);
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount,uint8_t page)
{
    uint8_t i,x;
    X5045_WREN();
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001010);
    else
        SimSPI_Proc(0b00000010);
    SimSPI_Proc(address);
    for(i=0;i<wCount;i++)
    {
        x=pW[i];
        SimSPI_Proc(x);
    }	
    X5045_CS=1;
    X5045_WIPCheck();	
    X5045_WRDI();
}
//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
uint8_t X5045_ReadByte(uint8_t address,uint8_t page)
{
    uint8_t x;
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001011);
    else
        SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    x=SimSPI_Proc(0);
    X5045_CS=1;
    return (x);
}
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount,uint8_t page)
{
    uint8_t i,x;
    X5045_CS=0;
    if(page!=0)
        SimSPI_Proc(0b00001011);
    else
        SimSPI_Proc(0b00000011);
    SimSPI_Proc(address);
    for(i=0;i<rCount;i++)
    {
        x=SimSPI_Proc(0);
        pR[i]=x;
    }	
    X5045_CS=1;
}
#endif
