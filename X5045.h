#ifndef __X5045_H__
#define __X5045_H__

void X5045_Init();
//��λ���Ź�
void X5045_RstWDT();
#ifndef X5045_MorePage
//��X5045д�뵥�ֽ�����,���룺x,��д����,address,д�����ݵĵ�ַ
void X5045_WriteByte(unsigned char address,unsigned char x);
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount);

//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
unsigned char X5045_ReadByte(unsigned char address);
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount);
#else
//��X5045д�뵥�ֽ�����,���룺x,��д����,address,д�����ݵĵ�ַ
void X5045_WriteByte(unsigned char address,unsigned char x,unsigned char page);
void X5045_WriteBytes(unsigned char address,unsigned char* pW,unsigned char wCount,unsigned char page);

//��X5045���뵥�ֽ�����,���룺address,�������ݵ�ַ,���أ�����������
unsigned char X5045_ReadByte(unsigned char address,unsigned char page);
void X5045_ReadBytes(unsigned char address,unsigned char* pR,unsigned char rCount,unsigned char page);
#endif

//5045״̬�Ĵ�����������
unsigned char X5045_RDSR();

//5045״̬�Ĵ���д�����
void X5045_WRSR(unsigned char x);

#endif
