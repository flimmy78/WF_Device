#include "HardwareProfile.h"

// #define LCD_T6963_RD RE2
// #define LCD_T6963_WR RB0
// #define LCD_T6963_CE RE1
// #define LCD_T6963_CD RE4
// #define LCD_T6963_PORT PORTD
// 
// #define LCD_T6963_RD_DIR TRISE2
// #define LCD_T6963_WR_DIR TRISB0
// #define LCD_T6963_CE_DIR TRISE1
// #define LCD_T6963_CD_DIR TRISE4
// #define LCD_T6963_PORT_DIR TRISD
// #define LCD_T6963_LineChar 20  // ���ÿ��

uint8_t LCD_T6963_ReadState();
void LCD_T6963_WriteD(uint8_t dat);
void LCD_T6963_WriteC(uint8_t cmd);
void LCD_T6963_Init(void)
{
	uint16_t x;
#ifdef LCD_T6963_RST_DIR
	LCD_T6963_RST_DIR=0;
	LCD_T6963_RST_W=1;
	__delay_ms(1);
	LCD_T6963_RST_W=0;
	__delay_20ms(20);
	LCD_T6963_RST_W=1;
#endif
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0x00;//���
#else
	LCD_T6963_SetPortWrite();
#endif	
	LCD_T6963_RD_DIR=0;
	LCD_T6963_WR_DIR=0;
	LCD_T6963_CD_DIR=0;
	LCD_T6963_CE_DIR=0;
	LCD_T6963_RD_W=1;
	LCD_T6963_WR_W=1;
	LCD_T6963_CD_W=1;
	LCD_T6963_CE_W=1;

	x=LCD_T6963_LineChar*LCD_T6963_Columns;
	x=x<<3;
	LCD_T6963_WriteCmd2(LOW_BYTE(x),HIGH_BYTE(x),T6963_TextHomeAddr);   //�ı��׵�ַ,0x0a00,�൱��һ��
	LCD_T6963_WriteCmd2(LCD_T6963_LineChar,0x00,T6963_TextArea);   //�ı��������
	LCD_T6963_WriteCmd2(0x00,0x00,T6963_GraHomeAddr);   // ͼ���׵�ַ
	LCD_T6963_WriteCmd2(LCD_T6963_LineChar,0x00,T6963_GraArea);   //����ͼ�ο��  
	//��һ����ʾ��ռ�ֽ���
	LCD_T6963_WriteCmd0(0xa0);             //�������
	LCD_T6963_WriteCmd0(T6963_OrMode);             //��ʾ��ʽ����   �߼����ϳ�
	LCD_T6963_WriteCmd0(T6963_GraOn);             //��ʾ����
	LCD_T6963_ClearScreen(x); 
}
/******************************************************************************** 
������:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LCD_T6963_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
     uint16_t StartAddr; 
     uint8_t i=0;
     //uint8_t* zm=ZM;
     StartAddr=x;
     StartAddr+=((uint16_t)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrI);              // ��벿 ��ַ��һ 
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // �Ұ벿 ��ʾ��ַ����
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
     } 
}
/******************************************************************************** 
������:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LCD_T6963_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
     uint16_t StartAddr; 
     uint8_t i=0;
     //uint8_t* zm=ZM;
     StartAddr=x;
     StartAddr+=((uint16_t)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // �Ұ벿 ��ʾ��ַ����
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
     } 
}
void LCD_T6963_ShowPic(uint16_t Addr,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint16_t StartAddr; 
	uint8_t i,j;
	//uint8_t* zm=ZM;
	StartAddr=Addr;        //��λ��ʼ��
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(*Pic++, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
	} 
}
void LCD_T6963_ShowFull(uint16_t Addr,uint8_t Width,uint8_t Height,uint8_t fc)
{
	uint16_t StartAddr; 
	uint8_t i,j;
	//uint8_t* zm=ZM;
	StartAddr=Addr;        //��λ��ʼ��
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(fc, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
	} 
}
void LCD_T6963_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint16_t StartAddr; 
	uint8_t i,j;
	//uint8_t* zm=ZM;
	StartAddr=x;
	StartAddr+=((uint16_t)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(*Pic++, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
	} 
}
void LCD_T6963_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc)
{
	uint16_t StartAddr; 
	uint8_t i,j;
	//uint8_t* zm=ZM;
	StartAddr=x;
	StartAddr+=((uint16_t)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
	Width=Width>>3;
	for(i=0;i<Height;i++) 
	{ 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		for(j=0;j<Width;j++)
		{
			LCD_T6963_WriteCmd1(fc, T6963_DataWAddrI);
		}
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
	} 
}
/********************************************************************************
������: Void ClearScreen(uint16_t ram)
��������: ���������Ļ
     ram : ��Ҫ����ĵ�Ԫ��
********************************************************************************/
void LCD_T6963_ClearScreen(uint16_t ram)
{
     uint16_t i;
     LCD_T6963_AutoWriteStart(0x0000);          // ����ʾ RAM �� 0000h--2000h (8k)     
     for(i=0x00;i<ram;i++) 
		 LCD_T6963_AutoWriteData(0x00);        // data=0;
     LCD_T6963_AutoWriteEnd();                // �Զ�д����
}
void LCD_T6963_ClearScreenEx(uint16_t start,uint16_t ram)
{
	uint16_t i;
	LCD_T6963_AutoWriteStart(start);          // ����ʾ RAM �� 0000h--2000h (8k)     
	for(i=0x00;i<ram;i++) 
		LCD_T6963_AutoWriteData(0x00);        // data=0;
	LCD_T6963_AutoWriteEnd();                // �Զ�д����
}
/********************************************************************************
������:    Void LCD_T6963_WriteCmd1(uint8_t cmd)
           Void LCD_T6963_WriteCmd2(uint8_t dat1,uint8_t cmd)
           Void LCD_T6963_WriteCmd3(uint8_t dat1,uint8_t dat2,uint8_t cmd)
     Void LCD_T6963_WriteData(uint8_t dat)
��������: дָ���д�����ӳ���
********************************************************************************/
void LCD_T6963_WriteD(uint8_t dat)
{
	while( (LCD_T6963_ReadState()&0x03)!=0x03 );
	LCD_T6963_CD_W=0;    //����
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=dat;//���
#else
	LCD_T6963_SetPortData(dat);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;	
}
void LCD_T6963_WriteC(uint8_t cmd)
{
	while( (LCD_T6963_ReadState()&0x03)!=0x03 );
	LCD_T6963_CD_W=1;    //����
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=cmd;//���
#else
	LCD_T6963_SetPortData(cmd);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;

}
void LCD_T6963_WriteCmd0(uint8_t cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//Ƭѡ
#endif

}
void LCD_T6963_WriteCmd1(uint8_t dat,uint8_t cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteD(dat);
	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//Ƭѡ
#endif

}
void LCD_T6963_WriteCmd2(uint8_t dat1,uint8_t dat2,uint8_t cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteD(dat1);
	LCD_T6963_WriteD(dat2);
	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//Ƭѡ
#endif

}
void LCD_T6963_AutoWriteStart(uint16_t Addr)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteD(LOW_BYTE(Addr));
	LCD_T6963_WriteD(HIGH_BYTE(Addr));
	LCD_T6963_WriteC(T6963_AddrSet);	
	LCD_T6963_WriteC(T6963_DataAutoWrite);  // �����Զ�д״̬
}
void LCD_T6963_AutoWriteData(uint8_t dat)
{
	while( !(LCD_T6963_ReadState()&0x08) );
	LCD_T6963_CD_W=0;    //����
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_W=0x00;//���
#else
	LCD_T6963_SetPortData(dat);
#endif
	LCD_T6963_WR_W=0;
	__delay_us(1);
	LCD_T6963_WR_W=1;	
}
void LCD_T6963_AutoWriteEnd(void)
{
	LCD_T6963_WriteC(T6963_ExitAutoRW);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//Ƭѡ
#endif

}
/********************************************************************************
������:    ReadSdate(void)
��������: IOPORT������ݲ����LCDæ���ݡ�
�������ݣ�checkbusy
/********************************************************************************/
uint8_t LCD_T6963_ReadState()
{
	uint8_t state;
	LCD_T6963_CD_W=1;    //������
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0xff;//����
#else
	LCD_T6963_SetPortRead();
#endif
	LCD_T6963_RD_W=0;    //����Ч
	__delay_us(1);
#ifdef LCD_T6963_PORT_DIR
	state=LCD_T6963_PORT_R;
#else
	state=LCD_T6963_GetPortData();
#endif	
	LCD_T6963_RD_W=1;    //������
#ifdef LCD_T6963_PORT_DIR
	LCD_T6963_PORT_DIR=0x00;//���
#else
	LCD_T6963_SetPortWrite();
#endif
	return ( state );  //����LCD���ݿ�����
}
