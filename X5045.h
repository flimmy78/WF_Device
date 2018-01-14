#ifndef __X5045_H__
#define __X5045_H__

void X5045_Init();
//��λ���Ź�
void X5045_RstWDT();
#ifndef X5045_MorePage
//��X5045д�뵥�ֽ�����,���룺x,��д����,address,д�����ݵĵ�ַ
void X5045_WriteByte(uint8_t address,uint8_t x);
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount);

//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
uint8_t X5045_ReadByte(uint8_t address);
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount);
#else
//��X5045д�뵥�ֽ�����,���룺x,��д����,address,д�����ݵĵ�ַ
void X5045_WriteByte(uint8_t address,uint8_t x,uint8_t page);
void X5045_WriteBytes(uint8_t address,uint8_t* pW,uint8_t wCount,uint8_t page);

//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
uint8_t X5045_ReadByte(uint8_t address,uint8_t page);
void X5045_ReadBytes(uint8_t address,uint8_t* pR,uint8_t rCount,uint8_t page);
#endif

//5045״̬�Ĵ�����������
uint8_t X5045_RDSR();

//5045״̬�Ĵ���д�����
void X5045_WRSR(uint8_t x);

#endif
