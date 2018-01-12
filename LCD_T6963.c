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

unsigned char LCD_T6963_ReadState();
void LCD_T6963_WriteD(unsigned char dat);
void LCD_T6963_WriteC(unsigned char cmd);
void LCD_T6963_Init(void)
{
	unsigned int x;
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
������:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LCD_T6963_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm) 
{ 
     unsigned int StartAddr; 
     unsigned char i=0;
     //unsigned char* zm=ZM;
     StartAddr=x;
     StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrI);              // ��벿 ��ַ��һ 
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // �Ұ벿 ��ʾ��ַ����
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
     } 
}
/******************************************************************************** 
������:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LCD_T6963_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm) 
{ 
     unsigned int StartAddr; 
     unsigned char i=0;
     //unsigned char* zm=ZM;
     StartAddr=x;
     StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
     for(i=0;i<16;i++) 
     { 
		LCD_T6963_WriteCmd2(LOW_BYTE(StartAddr),HIGH_BYTE(StartAddr),T6963_AddrSet);
		LCD_T6963_WriteCmd1(*zm++, T6963_DataWAddrNV);             // �Ұ벿 ��ʾ��ַ����
		StartAddr=StartAddr + LCD_T6963_LineChar;            // ������һ��
     } 
}
void LCD_T6963_ShowPic(unsigned int Addr,unsigned char Width,unsigned char Height,const unsigned char* Pic)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
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
void LCD_T6963_ShowFull(unsigned int Addr,unsigned char Width,unsigned char Height,unsigned char fc)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
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
void LCD_T6963_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=x;
	StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
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
void LCD_T6963_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc)
{
	unsigned int StartAddr; 
	unsigned char i,j;
	//unsigned char* zm=ZM;
	StartAddr=x;
	StartAddr+=((unsigned int)y*LCD_T6963_LineChar)<<3;        //��λ��ʼ��
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
������: Void ClearScreen(unsigned int ram)
��������: ���������Ļ
     ram : ��Ҫ����ĵ�Ԫ��
********************************************************************************/
void LCD_T6963_ClearScreen(unsigned int ram)
{
     unsigned int i;
     LCD_T6963_AutoWriteStart(0x0000);          // ����ʾ RAM �� 0000h--2000h (8k)     
     for(i=0x00;i<ram;i++) 
		 LCD_T6963_AutoWriteData(0x00);        // data=0;
     LCD_T6963_AutoWriteEnd();                // �Զ�д����
}
void LCD_T6963_ClearScreenEx(unsigned int start,unsigned int ram)
{
	unsigned int i;
	LCD_T6963_AutoWriteStart(start);          // ����ʾ RAM �� 0000h--2000h (8k)     
	for(i=0x00;i<ram;i++) 
		LCD_T6963_AutoWriteData(0x00);        // data=0;
	LCD_T6963_AutoWriteEnd();                // �Զ�д����
}
/********************************************************************************
������:    Void LCD_T6963_WriteCmd1(unsigned char cmd)
           Void LCD_T6963_WriteCmd2(unsigned char dat1,unsigned char cmd)
           Void LCD_T6963_WriteCmd3(unsigned char dat1,unsigned char dat2,unsigned char cmd)
     Void LCD_T6963_WriteData(unsigned char dat)
��������: дָ���д�����ӳ���
********************************************************************************/
void LCD_T6963_WriteD(unsigned char dat)
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
void LCD_T6963_WriteC(unsigned char cmd)
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
void LCD_T6963_WriteCmd0(unsigned char cmd)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteC(cmd);

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=1;//Ƭѡ
#endif

}
void LCD_T6963_WriteCmd1(unsigned char dat,unsigned char cmd)
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
void LCD_T6963_WriteCmd2(unsigned char dat1,unsigned char dat2,unsigned char cmd)
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
void LCD_T6963_AutoWriteStart(unsigned int Addr)
{

#ifdef  LCD_T6963_CE_DIR
	LCD_T6963_CE_W=0;//Ƭѡ
#endif

	LCD_T6963_WriteD(LOW_BYTE(Addr));
	LCD_T6963_WriteD(HIGH_BYTE(Addr));
	LCD_T6963_WriteC(T6963_AddrSet);	
	LCD_T6963_WriteC(T6963_DataAutoWrite);  // �����Զ�д״̬
}
void LCD_T6963_AutoWriteData(unsigned char dat)
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
unsigned char LCD_T6963_ReadState()
{
	unsigned char state;
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
