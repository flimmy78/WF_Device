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
// const uint8_t LCD160X_LineStart[4]={0x80,0x90,0x88,0x98};
// #endif

#define LCD160X_OFF() LCD160X_Write(LCD160X_COMMAND,0x08)  //����ʾ

/*------------------��ʼ��-----------------*/
void LCD160X_Init(void);
/*---------------��ʾ���ֻ��ַ�----------------*/
void LCD160X_DispString(uint8_t X,uint8_t Y,const char *pString);
void LCD160X_DispOneChar(uint8_t Addr,uint8_t c);
void LCD160X_DispOneCharByXY(uint8_t X,uint8_t Y,uint8_t c);
/************************************************************************/
/* ��궯��                                                             */
/************************************************************************/
void LCD160X_CurLeft(void);
void LCD160X_CurRight(void);
void LCD160X_CurShowByAddr(uint8_t Addr,uint8_t bFlicker);
void LCD160X_CurShowByXY(uint8_t X,uint8_t Y,uint8_t bFlicker );
void LCD160X_CurHide(void);
/*--------------��DDRAM------------------*/
void LCD160X_ClrRam(void);

#ifdef LCD160X_CGRAMADDR
void LCD160X_DispCGRAM(uint8_t X,uint8_t Y,uint8_t nIndex);
void Lcd1602_InitCGRAM(const char  *pC);
#endif

void LCD160X_Write(uint8_t dat_comm,uint8_t content);

/************************************************************************/
/* ��ͼ���                                                             */
/************************************************************************/
void LCD160X_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm);
void LCD160X_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm1,const uint8_t* zm2);
void LCD160X_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);
void LCD160X_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc);
#endif

