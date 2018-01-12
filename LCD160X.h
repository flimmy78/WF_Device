#ifndef __Lcd1602_H__
#define __Lcd1602_H__

//���У����룬˳��
//#define LCD160X_PORT_DIR
// #define LCD160X_CD     //����
// #define LCD160X_WR     //��
// #define LCD160X_E 
/******************1602Һ������������******************/
#define LCD1602_A_FUNCTION	0x38   	// Һ��ģʽΪ8λ��2�У�5*8�ַ�
#define LCD1602_G_FUNCTION	0x3e   	// Һ��ģʽΪ8λ��2�У�5*8�ַ�
#define LCD1604_A_FUNCTION  0x30	// Һ��ģʽΪ8λ��4�У�5*8�ַ�
#define LCD1604_G_FUNCTION  0x36	// Һ��ģʽΪ8λ��4�У�5*8�ַ�

#define LCD160X_COMMAND  0	//ָ���־
#define LCD160X_DATA     1	//���ݱ�־		

#define LCD160X_A_CLR	0x01		// ����
#define LCD160X_A_HOME	0x02		// ��ַ����ԭ�㣬���ı�DDRAM����
#define LCD160X_A_ENTRY 0x06		// �趨����ģʽ�����ӣ���Ļ���ƶ�
#define LCD160X_A_C2L	0x10		// �������
#define LCD160X_A_C2R	0x14		// �������
#define LCD160X_A_D2L	0x18		// ��Ļ����
#define LCD160X_A_D2R	0x1C		// ��Ļ����

#define LCD160X_A_ON	0x0C		// ����ʾ
#define LCD160X_A_OFF	0x08		// �ر���ʾ
#define LCD160X_A_CURON	0x0E		// ��ʾ���
#define LCD160X_A_CURFLA	0x0F		// �򿪹����˸

// #ifndef LCD160X_LineStart
// const unsigned char LCD160X_LineStart[4]={0x80,0x90,0x88,0x98};
// #endif

#define LCD160X_OFF() LCD160X_Write(LCD160X_COMMAND,0x08)  //����ʾ

/*------------------��ʼ��-----------------*/
void LCD160X_Init(void);
/*---------------��ʾ���ֻ��ַ�----------------*/
void LCD160X_DispString(unsigned char X,unsigned char Y,const char *pString);
void LCD160X_DispOneChar(unsigned char Addr,unsigned char c);
void LCD160X_DispOneCharByXY(unsigned char X,unsigned char Y,unsigned char c);
/************************************************************************/
/* ��궯��                                                             */
/************************************************************************/
void LCD160X_CurLeft(void);
void LCD160X_CurRight(void);
void LCD160X_CurShowByAddr(unsigned char Addr,unsigned char bFlicker);
void LCD160X_CurShowByXY(unsigned char X,unsigned char Y,unsigned char bFlicker );
void LCD160X_CurHide(void);
/*--------------��DDRAM------------------*/
void LCD160X_ClrRam(void);

#ifdef LCD160X_CGRAMADDR
void LCD160X_DispCGRAM(unsigned char X,unsigned char Y,unsigned char nIndex);
void Lcd1602_InitCGRAM(const char  *pC);
#endif

void LCD160X_Write(unsigned char dat_comm,unsigned char content);

/************************************************************************/
/* ��ͼ���                                                             */
/************************************************************************/
void LCD160X_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm);
void LCD160X_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm1,const unsigned char* zm2);
void LCD160X_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);
void LCD160X_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc);
#endif

