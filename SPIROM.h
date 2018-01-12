#ifndef __SPIROM_h__
#define __SPIROM_h__
//cs��wp���г�ʼ��
//���ⲿ����SPIROM_SPIInit()�����ڳ�ʼ��spi��ص�3������
//���ⲿ����unsigned char SPIROM_SendData(unsigned char c)
/************************************************************************/
/* ����оƬ                                                             */
/* 1. FM25H20  ״̬����WIPδ�ã��趨��SPIROM_Addr24						*/
/************************************************************************/

/************************************************************************
* EEPROM Commands                                                       
************************************************************************/
// #define SPIROM_PAGE_SIZE    (unsigned)64
// #define SPIROM_PAGE_MASK    (unsigned)0x003f
#define SPIROM_CMD_READ     (unsigned)0x03
#define SPIROM_CMD_WRITE    (unsigned)0x02
#define SPIROM_CMD_WRDI     (unsigned)0x04
#define SPIROM_CMD_WREN     (unsigned)0x06
#define SPIROM_CMD_RDSR     (unsigned)0x05
#define SPIROM_CMD_WRSR     (unsigned)0x01
/************************************************************************
* Structure STATREG and union _EEPROMStatus_                            
*                                                                       
* Overview: provide bits and byte access to EEPROM status value      
*                                                                       
************************************************************************/
typedef union   
{
	struct
	{
		unsigned WIP : 1;
		unsigned WEL : 1;
		unsigned BP0 : 1;
		unsigned BP1 : 1;
		unsigned RESERVED : 3;
		unsigned WPEN : 1;
	};
	unsigned char All;
} _SPIROM_Status;        // general flags
extern _SPIROM_Status SPIROM_Status;



void SPIROM_Init(void);

void SPIROM_ReadStatus(void);

#ifdef SPIROM_Addr24
void SPIROM_WriteByte(unsigned long address,unsigned char data);
#else
void SPIROM_WriteByte(unsigned int address,unsigned char data);
#endif

#ifdef SPIROM_Addr24
unsigned char SPIROM_ReadByte(unsigned long address);
#else
unsigned char SPIROM_ReadByte(unsigned int address);
#endif

#ifdef SPIROM_Addr24
void SPIROM_WriteArray(unsigned long address, unsigned char* pData,unsigned int nCount);
#else
void SPIROM_WriteArray(unsigned int address, unsigned char* pData,unsigned int nCount);
#endif
#ifdef SPIROM_Addr24
void SPIROM_Fill(unsigned long address, unsigned char Data,unsigned long nCount);
#else
void SPIROM_Fill(unsigned int address, unsigned char Data,unsigned int nCount);
#endif
#ifdef SPIROM_Addr24
void SPIROM_ReadArray(unsigned long address, unsigned char* pData,unsigned int nCount);
#else
void SPIROM_ReadArray(unsigned int address, unsigned char* pData,unsigned int nCount);
#endif

#endif // __SPIROM_h__
