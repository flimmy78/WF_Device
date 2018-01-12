#include "HardwareProfile.h"
#include "SPI1TxQueue.h"
//#define Uart1_BRGVAL ((FCY/Uart1_BAUDRATE)/4)-1

unsigned char SPI1TxQueue[SPI1TxQueueLen];
unsigned char *pSPI1In, *pSPI1Out;

void SPI1TxStart()
{	
	if(__SPI1TBF==0)   //���ͼĴ���Ϊ��    
	{
		__SPI1TXREG=*pSPI1Out;
		pSPI1Out++;
		if (pSPI1Out == (SPI1TxQueue+SPI1TxQueueLen))
			pSPI1Out = SPI1TxQueue;	
	}		
}
void SPI1AddStr(const char* pt)
{
	const char *p;
	p = pt;
	while (*p != '\0')                         //������뻺����
	{
		SPI1AddByte(*p++);
	}
}
void SPI1AddByte(unsigned char tx)
{
	unsigned char *d;
	d = pSPI1In;
	d++;
	if (d == (SPI1TxQueue+SPI1TxQueueLen))         //����
		d = SPI1TxQueue;
	while(d == pSPI1Out);         //TxBuf��
	*pSPI1In = tx;  //����һ������
	pSPI1In = d;    //inTxBuf����
	SPI1TxStart();
}
void SPI1AddBytes(const void *tx, size_t size, size_t n)
{
	size_t count = size * n;
	unsigned char *s;
	if(count==0)
		return;
	s = (unsigned char*)tx;
	while (count--)                         //������뻺����
	{
		SPI1AddByte(*s++);
	}
}
void SPI1TxQueueInterrupt(void)
{	
	if (pSPI1Out == pSPI1In)             //TxBuf��
	{		
		return;
	}	
	__SPI1TXREG=*pSPI1Out;
	pSPI1Out++;
	if (pSPI1Out == (SPI1TxQueue+SPI1TxQueueLen))
		pSPI1Out = SPI1TxQueue;	
}
void InitSPI1TxQueue(void)
{
	pSPI1Out=pSPI1In=SPI1TxQueue;
}
