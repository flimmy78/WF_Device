#include "HardwareProfile.h"

// 
// #define LCD160X_PORT_DIR TRISE
// #define LCD160X_CD_DIR TRISD2    //����
// #define LCD160X_WR_DIR TRISD1    //��
// #define LCD160X_E_DIR  TRISD0
// 
// #define LCD160X_PORT PORTE
// #define LCD160X_CD RD2    //����
// #define LCD160X_WR RD1    //��
// #define LCD160X_E RD0
#ifndef LCD160X_LineStart_Ex
const uint8_t LCD160X_LineStart[4]={0x80,0x90,0x88,0x98};
const uint8_t LCD160X_RowStart[4]={0x80,0x80,0x88,0x88};
const uint8_t LCD160X_ColStart[4]={0x80,0x90,0x80,0x90};
#endif
#ifdef LCD160X_Serial

#define LCD160X_WRITE_COMMAND   0xF8 
#define LCD160X_WRITE_DATA      0xFA 
#define LCD160X_READ_STATUS     0xFC 
#define LCD160X_READ_DATA       0xFE

uint8_t LCD160X_ReadByte(void) 
{    
	uint8_t temp=0;      
	uint8_t i,temp1=0;
	LCD160X_SID_DIR=1; 
	for(i=0; i<8; i++) 
	{ 
		temp1<<=1; 
		//send clk 
		LCD160X_CLK_W=0;
		__delay_us(1);
		LCD160X_CLK_W=1; 
		//wait pin steady 
		__delay_us(1); 
		temp1 |= LCD160X_SID_R; 
	} 
 	temp = temp1 & 0xF0; 
 	for(i=0; i<8; i++) 
 	{ 
 		temp1<<=1; 
 		//send clk 
 		LCD160X_CLK_W=0;
 		__delay_us(1);
 		LCD160X_CLK_W=1; 
 		//wait pin steady 
 		__delay_us(1); 
 		temp1 |= LCD160X_SID_R; 
 	}
 	temp = ((temp1 & 0xF0)>>4) + temp; 
	LCD160X_SID_DIR=0; 
	return(temp);     
}
void LCD160X_WriteByte(uint8_t b)
{
	uint8_t i; 
	for(i=0; i<8; i++) 
	{   
		if(b & 0x80) 
			LCD160X_SID_W=1; 
		else 
			LCD160X_SID_W=0; 
		LCD160X_CLK_W=0; 
		//wait pin steady 
		__delay_us(1); 
		//send clk 
		LCD160X_CLK_W=1;  
		__delay_us(1);  
		b<<=1; 
	}  
	LCD160X_CLK_W=0;
}
#endif
#ifndef LCD160X_FuncEx
	uint8_t LCD160X_IsBusy(void)
	{ 
		uint8_t Ret;
	#ifdef LCD160X_Parallel8
		#ifdef LCD160X_PORT_DIR
			LCD160X_PORT_DIR=0xff;
		#else 
			LCD160X_SetPortRead();
		#endif	
		LCD160X_CD_W=0;     //����
		LCD160X_WR_W=1;     //��
		LCD160X_E_W=1; 
		__delay_us(1);
		#ifdef LCD160X_PORT_DIR
			Ret=LCD160X_PORT_R;	
		#else
			Ret=LCD160X_GetPortData();
		#endif	
		Ret=Ret&0x80;
		LCD160X_E_W=0;		
		#ifdef LCD160X_PORT_DIR
			LCD160X_PORT_DIR=0x00;
		#else
			LCD160X_SetPortWrite();
		#endif		
		if(Ret==0)	
			return 0;
		else
			return 1;
	#elif defined(LCD160X_Serial)
		LCD160X_WriteByte(LCD160X_READ_STATUS);
		Ret=LCD160X_ReadByte();
		Ret=Ret&0x80;
		if(Ret==0)	
			return 0;
		else
			return 1;
	#endif
		return 0;
	}
	void LCD160X_Write(uint8_t dat_comm,uint8_t content)
	{
	#ifdef LCD160X_Parallel8
		#ifdef Proteus
			__delay_ms(10);
		#else
			while(LCD160X_IsBusy());
		#endif	
		if(dat_comm)
		{
			LCD160X_CD_W=1;   //data
			LCD160X_WR_W=0;   //write	
		}
		else
		{
			LCD160X_CD_W=0;   //command
			LCD160X_WR_W=0;   //write
		}
		#ifdef LCD160X_PORT_DIR
			LCD160X_PORT_W=content;
		#else
			LCD160X_SetPortData(content);
		#endif	
		LCD160X_E_W=1;
		NOP();
		NOP();
		LCD160X_E_W=0;
	#elif defined(LCD160X_Serial)
		LCD160X_CS_W=1;
		#ifdef Proteus
			__delay_ms(10);
		#else
			while(LCD160X_IsBusy());
		#endif	
		if(dat_comm)
		{
			LCD160X_WriteByte(LCD160X_WRITE_DATA);	
		}
		else
		{
			LCD160X_WriteByte(LCD160X_WRITE_COMMAND);
		}
		LCD160X_WriteByte(content & 0xF0); 
		//write lower 4 bits 
		LCD160X_WriteByte((content<<4) & 0xF0); 
		LCD160X_CS_W=0;
	#endif
	}
	void LCD160X_IOInit(void)
	{
	#ifdef LCD160X_Parallel8
		#ifdef LCD160X_PORT_DIR
			LCD160X_PORT_DIR=0x00;
		#else
			LCD160X_SetPortWrite();
		#endif		
			LCD160X_CD_DIR=0;	
			LCD160X_WR_DIR=0;		
			LCD160X_E_DIR=0;
			LCD160X_E_W=0;	
	#elif defined(LCD160X_Serial)
		LCD160X_CS_DIR=0;
		LCD160X_SID_DIR=0;	
		LCD160X_CLK_DIR=0;
		LCD160X_CS_W=0;
	#endif
	#ifdef LCD160X_RST_W
		LCD160X_RST_DIR=0;
		LCD160X_RST_W=0;
		__delay_ms(20);
		LCD160X_RST_W = 1;   //��λ�ź�
		__delay_ms(5);
	#endif
	}
#endif
/*---------------------------------------*/



/*------------------��ʼ��-----------------*/
void LCD160X_Init(void)
{
	LCD160X_IOInit();
	__delay_ms(2);
	LCD160X_Write(LCD160X_COMMAND,LCD160X_DisplayMode);  //8λ�ӿڣ�����ָ���
	__delay_ms(2);
	LCD160X_Write(LCD160X_COMMAND,LCD160X_DisplayMode);  //8λ�ӿڣ�����ָ���
	__delay_ms(2);   
  	LCD160X_Write(LCD160X_COMMAND,0x08);  //����ʾ
  	__delay_ms(1);
  	LCD160X_Write(LCD160X_COMMAND,0x01);  //��������ַָ��ָ��00H
  	__delay_ms(15);
  	LCD160X_Write(LCD160X_COMMAND,0x06);  //�����ƶ�����
  	__delay_ms(1);
  	LCD160X_Write(LCD160X_COMMAND,0x0c);  //����ʾ�����α�
  	__delay_ms(1);
}
/*---------------��ʾ���ֻ��ַ�----------------*/

void LCD160X_DispString(uint8_t X,uint8_t Y,const char  *pString)
{
#ifdef LCD160X_LineMax
	uint8_t x=0;
#endif
	LCD160X_Write(LCD160X_COMMAND, LCD160X_LineStart[Y] + X);
	while((*pString)!='\0')		 //�ַ���δ������һֱд
	{
		LCD160X_Write(LCD160X_DATA, *pString++);
#ifdef LCD160X_LineMax
		x++;
		if(x>=LCD160X_LineMax)
			break;
#endif
	}
}
void LCD160X_DispOneCharByXY(uint8_t X,uint8_t Y,uint8_t c)
{
	LCD160X_Write(LCD160X_COMMAND, LCD160X_LineStart[Y] + X);
	LCD160X_Write(LCD160X_DATA,c);
}
void LCD160X_DispOneChar(uint8_t Addr,uint8_t c)
{
	Addr |= 0x80; //���ָ����
	LCD160X_Write(LCD160X_COMMAND, Addr);
	LCD160X_Write(LCD160X_DATA,c);
}
/*--------------��DDRAM------------------*/
void LCD160X_ClrRam(void)
{
	LCD160X_Write(LCD160X_COMMAND,0x01);
}
#ifdef LCD160X_CGRAMADDR
void Lcd1602_InitCGRAM(const char  *pC,uint8_t count)
{
	uint8_t i;
	LCD160X_Write(LCD160X_COMMAND, LCD160X_CGRAMADDR);  //д��CGRAM�׵�ַ
	for (i = 0; i < count; i++)		  //д��64���ֽڵ�CGRAM����
	{
		LCD160X_Write(LCD160X_DATA,pC[i]);
	}
}
void LCD160X_DispCGRAM(uint8_t X,uint8_t Y,uint8_t nIndex)
{
	LCD160X_Write(LCD160X_COMMAND, LCD160X_LineStart[Y] + X);
	LCD160X_Write(LCD160X_DATA, nIndex);
}	
#endif

void LCD160X_CurShowByXY(uint8_t X,uint8_t Y,uint8_t bFlicker )
{	
	LCD160X_Write(LCD160X_COMMAND, LCD160X_LineStart[Y] + X);
	if(bFlicker)
		LCD160X_Write(LCD160X_COMMAND,0x0f);
	else
		LCD160X_Write(LCD160X_COMMAND,0x0e);  
}
void LCD160X_CurShowByAddr( uint8_t Addr,uint8_t bFlicker )
{	
	Addr |= 0x80; //���ָ����
	LCD160X_Write(LCD160X_COMMAND, Addr);
	if(bFlicker==0)
		LCD160X_Write(LCD160X_COMMAND,0x0e);
	else
		LCD160X_Write(LCD160X_COMMAND,0x0f);  
}

void LCD160X_CurLeft( void )
{
	LCD160X_Write(LCD160X_COMMAND,0x10); 
}

void LCD160X_CurRight( void )
{
	LCD160X_Write(LCD160X_COMMAND,0x14); 
}

void LCD160X_CurHide( void )
{
	LCD160X_Write(LCD160X_COMMAND,0x0c);
}
/************************************************************************/
/* ��ͼ���                                                             */
/************************************************************************/
void LCD160X_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) 
{ 
	uint8_t i=0;
	LCD160X_Write(LCD160X_COMMAND,0x34);//�رջ�ͼ��ʾ
	for(i=0;i<16;i++)
	{
		LCD160X_Write(LCD160X_COMMAND,LCD160X_ColStart[y]+i);//��ʼ��λ��
		LCD160X_Write(LCD160X_COMMAND,LCD160X_RowStart[y]+x);//��ʼ��λ��		
		LCD160X_Write(LCD160X_DATA, *zm++);
		LCD160X_Write(LCD160X_DATA, *zm++);
	}
	LCD160X_Write(LCD160X_COMMAND,0x36);//�򿪻�ͼ��ʾ
}
void LCD160X_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm1,const uint8_t* zm2) 
{ 
	uint8_t i=0;
	LCD160X_Write(LCD160X_COMMAND,0x34);//�رջ�ͼ��ʾ
	for(i=0;i<16;i++)
	{
		LCD160X_Write(LCD160X_COMMAND,LCD160X_ColStart[y]+i);//��ʼ��λ��
		LCD160X_Write(LCD160X_COMMAND,LCD160X_RowStart[y]+x);//��ʼ��λ��		
		LCD160X_Write(LCD160X_DATA, *zm1++);
		LCD160X_Write(LCD160X_DATA, *zm2++);
	}
	LCD160X_Write(LCD160X_COMMAND,0x36);//�򿪻�ͼ��ʾ
}
void LCD160X_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic)
{
	uint8_t i,j,k;
	LCD160X_Write(LCD160X_COMMAND,0x34);//�رջ�ͼ��ʾ
	Width=Width>>3;
	k=0;
	for(i=0;i<Height;i++)
	{
		LCD160X_Write(LCD160X_COMMAND,LCD160X_ColStart[y]+k);//��ʼ��λ��
		LCD160X_Write(LCD160X_COMMAND,LCD160X_RowStart[y]+x);//��ʼ��λ��		
		for(j=0;j<Width;j++)
		{
			LCD160X_Write(LCD160X_DATA, *Pic++);
		}
		k++;
		if(k==16)
		{
			k=0;
			y++;
		}
	}
	LCD160X_Write(LCD160X_COMMAND,0x36);//�򿪻�ͼ��ʾ
}
void LCD160X_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc)
{
	uint8_t i,j,k;
	LCD160X_Write(LCD160X_COMMAND,0x34);//�رջ�ͼ��ʾ
	Width=Width>>3;
	k=0;
	for(i=0;i<Height;i++)
	{
		LCD160X_Write(LCD160X_COMMAND,LCD160X_ColStart[y]+k);//��ʼ��λ��
		LCD160X_Write(LCD160X_COMMAND,LCD160X_RowStart[y]+x);//��ʼ��λ��		
		for(j=0;j<Width;j++)
		{
			LCD160X_Write(LCD160X_DATA, fc);
		}
		k++;
		if(k==16)
		{
			k=0;
			y++;
		}
	}
	LCD160X_Write(LCD160X_COMMAND,0x36);//�򿪻�ͼ��ʾ 
}
