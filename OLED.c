#include "HardwareProfile.h"

// #define OLED_RD RE2
// #define OLED_WR RB0
// #define OLED_CS RE1
// #define OLED_CD RE4
// #define OLED_RST PORTD
// #define OLED_PORT PORTD
// 
// 
// #define OLED_RST_DIR TRISE2
// #define OLED_RD_DIR TRISE2
// #define OLED_WR_DIR TRISB0
// #define OLED_CS_DIR TRISE1
// #define OLED_CD_DIR TRISE4
// #define OLED_PORT_DIR TRISD
uint8_t OLED_ReadState()
{
	uint8_t state;
	OLED_CD_W=1;    //������
#ifdef OLED_PORT_DIR
	OLED_PORT_W=0xff;//����
#else
	OLED_SetPortRead();
#endif
	OLED_RD_W=0;    //����Ч
	__delay_us(1);
#ifdef OLED_PORT_DIR
	state=OLED_PORT;
#else
	state=OLED_GetPortData();
#endif	
	OLED_RD_W=1;    //������
#ifdef OLED_PORT_DIR
	OLED_PORT_DIR=0x00;//���
#else
	OLED_SetPortWrite();
#endif
	return ( state );  //����LCD���ݿ�����
}

void OLED_Init(void)
{
	
#ifdef OLED_RST_DIR
	OLED_RST_DIR=0;
	OLED_RST_W=0;
	__delay_20ms(25);
	OLED_RST_W=1;
	__delay_20ms(25);
#endif

#ifdef OLED_M6800
	OLED_PORT_DIR=0x00;//���
	OLED_E_DIR=0;
	OLED_WR_DIR=0;
	OLED_CD_DIR=0;
	OLED_CS_DIR=0;

	OLED_E_W=1;
	OLED_WR_W=1;
	OLED_CD_W=1;
	OLED_CS_W=1;
#elif defined(OLED_SPI)

#else

#ifdef OLED_PORT_DIR
	OLED_PORT_DIR=0x00;//���
#endif	
	OLED_RD_DIR=0;
	OLED_WR_DIR=0;
	OLED_CD_DIR=0;
	OLED_CS_DIR=0;

	OLED_RD_W=1;
	OLED_WR_W=1;
	OLED_CD_W=1;
	OLED_CS_W=1;
#endif
	
	while(1)
	{
		// �������׵�ַ�Ͱ��ֽڣ�
		OLED_WriteC(0x00);
		// �����е�ַ�ĸ߰��ֽڣ�
		OLED_WriteC(0x10);
		// ���ô洢���ĵ�ַģʽ��
		OLED_WriteC(0x20);
		OLED_WriteC(0x00); /* ѡˮƽ��ַģʽ *///02
		// �����д��ڣ�
		OLED_WriteC(0x21);
		OLED_WriteC(0x00);
		OLED_WriteC(0x7f); /* 128 ��ȵĴ��� */
		// ����ҳ���ڣ�
		OLED_WriteC(0x22);
		OLED_WriteC(0x00);
		OLED_WriteC(0x07); /* 8 ҳ�Ĵ��� */
		// ������ʾ��ʼ��;
		OLED_WriteC(0x40); /* 0*/
		// ����bank0 �Աȶȣ�
		OLED_WriteC(0x81);
		OLED_WriteC(0x80); /* ��256 �� */
		// ���ò�ɫ���ȣ�
		OLED_WriteC(0x82);
		OLED_WriteC(0x80); /* ��256 �� */
		// ����SEG ���棻
		OLED_WriteC(0xA1); /* �ı�SEG ���ַ
						   �Ķ�Ӧ��ϵ */
		// ����ȫ�ԣ�
		OLED_WriteC(0xA4); /* ��ȫ�� */
		// ���÷��ԣ�
		OLED_WriteC(0xA6); /* ������ */
		// ������ʾ�У�
		OLED_WriteC(0xA8);
		OLED_WriteC(0x1f);
		/* 64 �У��ı���ǿ���ʾ��row*/
		// Vcc ��Դ��
		OLED_WriteC(0xAD);
		OLED_WriteC(0x8E); /* 8E=�ⲿ */
		// ����ҳ�׵�ַ��
		OLED_WriteC(0xB0); /* ��0 ҳ */
		// ����COM ɨ�跽��
		OLED_WriteC(0xC8); /* COM ���� */
		// ������ʾ��֧��
		OLED_WriteC(0xD3);
		OLED_WriteC(0x00); /* 0 */
		// ����D ��Fosc;
		OLED_WriteC(0xD5);
		OLED_WriteC(0xD1); /* F=D D=2 */ //a0
		// ��ɫ��ʡ��ģʽѡ��
		OLED_WriteC(0xD8);
		OLED_WriteC(0); /* 48 Ϊ��ɫ��5 Ϊʡ�� */
		// ���� P1 P2��
		OLED_WriteC(0xD9);
		OLED_WriteC(0x22); /* P1=2 P2=2 */
		//����COM ��Ӳ���ӷ���
		OLED_WriteC(0xDA);
		OLED_WriteC(0x12);
		//����Vcomh;
		OLED_WriteC(0xDB);
		OLED_WriteC(0x00);
		OLED_ClearScreen();
		OLED_WriteC(0xAF);
		/* AF=ON, AE=Sleep Mode��AC=Dim */
		if((OLED_ReadState()&0x40)==0x00)
			break;
	}
}
//x:0~15,y:0,1
void OLED_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{
     uint8_t i=0;
	 i=(x<<3)+4;
	 OLED_WriteC(0x21);
	 OLED_WriteC(i);
	 OLED_WriteC(i+15);
	 OLED_WriteC(0x22);
	 if(y==0)//������
	 {		 
		 OLED_WriteC(0);
		 OLED_WriteC(1);
	 }
	 else//������ 
	 {
		 OLED_WriteC(2);
		 OLED_WriteC(3);
	 }
     for(i=0;i<32;i++) 
     { 
		OLED_WriteD(*zm++);
     } 
}
//x:0~15,y:0,1
void OLED_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
	uint8_t i=0;
	i=(x<<3)+4;
	OLED_WriteC(0x21);
	OLED_WriteC(i);
	OLED_WriteC(i+7);
	OLED_WriteC(0x22);
	if(y==0)//������
	{		 
		OLED_WriteC(0);
		OLED_WriteC(1);
	}
	else//������ 
	{
		OLED_WriteC(2);
		OLED_WriteC(3);
	}
	for(i=0;i<16;i++) 
	{ 
		OLED_WriteD(*zm++);
	}
}
void OLED_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint16_t n,ii;
	n=Width*Height;
	n=n>>3;
	x=x<<3;
	x=x+4;
	OLED_WriteC(0x21);
	OLED_WriteC(x);
	Width=Width+x;
	Width=Width-1;
	OLED_WriteC(Width);
	OLED_WriteC(0x22);
	OLED_WriteC(y);
	Height=Height>>3;
	Height=Height+y;
	Height--;
	OLED_WriteC(Height);	
	for(ii=0;ii<n;ii++) 
	{ 
		OLED_WriteD(Pic[ii]);
	}
}
void OLED_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc)
{
	uint16_t n,ii;
	n=Width*Height;
	n=n>>3;
	x=x<<3;
	x=x+4;
	OLED_WriteC(0x21);
	OLED_WriteC(x);
	Width=Width+x;
	Width=Width-1;
	OLED_WriteC(Width);
	OLED_WriteC(0x22);
	OLED_WriteC(y);
	Height=Height>>3;
	Height=Height+y;
	Height--;
	OLED_WriteC(Height);	
	for(ii=0;ii<n;ii++) 
	{ 
		OLED_WriteD(fc);
	}
}
/********************************************************************************
������: Void ClearScreen(uint16_t ram)
��������: ���������Ļ
     ram : ��Ҫ����ĵ�Ԫ��
********************************************************************************/
void OLED_ClearScreen(void)
{
	uint16_t i=0;
	OLED_WriteC(0x21);
	OLED_WriteC(4);
	OLED_WriteC(131);
	OLED_WriteC(0x22);
	OLED_WriteC(0);
	OLED_WriteC(3);
	for(i=0;i<512;i++) 
	{ 
		OLED_WriteD(0x00);
	}
}
void OLED_WriteD(uint8_t dat)
{
	OLED_RD_W=1;
	OLED_CS_W=0;
	OLED_CD_W=1;    //����	
	OLED_WR_W=0;
#ifdef OLED_PORT_DIR
	OLED_PORT_W=dat;
#else
	OLED_SetPortData(dat);
#endif
	OLED_WR_W=1;	
	OLED_CS_W=1;
}
void OLED_WriteC(uint8_t cmd)
{	
	OLED_RD_W=1;
	OLED_CS_W=0;
	OLED_CD_W=0;    //����	
	OLED_WR_W=0;
#ifdef OLED_PORT_DIR
	OLED_PORT_W=cmd;
#else
	OLED_SetPortData(cmd);
#endif
	OLED_WR_W=1;	
	OLED_CS_W=1;
}
