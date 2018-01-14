#ifndef __LCD_T6963_H__
#define __LCD_T6963_H__

//���У�˳������
/************************************************************ 

                       ָ����붨�� 

************************************************************/ 
#define   T6963_CursorPointer    0x21          // ����ַ���� 
#define   T6963_OffsetReg        0x22          // CGRAMƫ�Ƶ�ַ���� 
#define   T6963_AddrSet          0x24          // ��ʾ��ַ���� 
#define   T6963_TextHomeAddr     0x40          // �ı��׵�ַ 
#define   T6963_TextArea         0x41          // �ı�������� 
#define   T6963_GraHomeAddr      0x42          // ͼ���׵�ַ���� 
#define   T6963_GraArea          0x43          // ͼ�ο������ 
#define   T6963_OrMode           0x80          // ��ģʽ��ʾ 
#define   T6963_ExorMode         0x81          // ���ģʽ��ʾ 
#define   T6963_AndMode          0x83          // ��ģʽ��ʾ 
#define   T6963_TextAttMode      0x84          // �ı�����ģʽ 
#define   T6963_InterCGROM       0             // �ڲ�CGROM 
#define   T6963_ExCGRAM          0x08          // �ⲿCGRAM 
#define   T6963_DisplayOff       0x90          // ��ʾ�ر� 
#define   T6963_CursorOn         0x92          // �����ʾ��������˸ 
#define   T6963_CursorBlink      0x93          // �����˸ 
#define   T6963_TextOn           0x94          // �ı�ģʽ�� 
#define   T6963_GraOn            0x98          // ͼ��ģʽ�� 
#define   T6963_TGAllOn          0x9c          // �ı�ͼ��ģʽ���� 
#define   T6963_DataAutoWrite    0xb0          // �����Զ�д 
#define   T6963_DataAutoRead     0xb1          // �����Զ��� 
#define   T6963_ExitAutoRW       0xb2          // �˳������Զ���дģʽ 
#define   T6963_DataWAddrI       0xc0          // ����д����ַ��1 
#define   T6963_DataWAddrD       0xc2          // ����д����ַ��1 
#define   T6963_DataWAddrNV      0xc4          // ����д����ַ���� 
#define   T6963_DataRAddrI       0xc1          // ���ݶ�����ַ��1 
#define   T6963_DataRAddrD       0xc3          // ���ݶ�����ַ��1 
#define   T6963_DataRAddrNV      0xc5          // ���ݶ�����ַ���� 
#define   T6963_ScreenPeek       0xe0          // ���� 
#define   T6963_ScreenCopy       0xe1          // ������ 
void LCD_T6963_Init(void);
void LCD_T6963_ClearScreen(uint16_t ram);
void LCD_T6963_WriteCmd0(uint8_t cmd);
void LCD_T6963_WriteCmd1(uint8_t dat,uint8_t cmd);
void LCD_T6963_WriteCmd2(uint8_t dat1,uint8_t dat2,uint8_t cmd);
void LCD_T6963_AutoWriteStart(uint16_t Addr);
void LCD_T6963_AutoWriteData(uint8_t dat);
void LCD_T6963_AutoWriteEnd(void);
void LCD_T6963_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm);
void LCD_T6963_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm);
void LCD_T6963_ShowPic(uint16_t Addr,uint8_t Width,uint8_t Height,const uint8_t* Pic);
void LCD_T6963_ShowFull(uint16_t Addr,uint8_t Width,uint8_t Height,uint8_t fc);
void LCD_T6963_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc);
void LCD_T6963_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);
#endif
