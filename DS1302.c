#include "HardwareProfile.h"
#include "TypeDefine.h"
#include "DS1302.h"

DS1302_TIME DS1302_Time;//��;��;ʱ;��;��;����;��;
void DS1302_WriteCommand(unsigned char cmd,unsigned char data);
void DS1302_WriteByte(unsigned char tx);
unsigned char DS1302_ReadByte(void);
//DS1302��ʼ������
void DS1302_Init()
{
	DS1302_DATA_IO=0;
	DS1302_CLK_IO=0;
	DS1302_CE_IO=0;
	DS1302_CLK_W=0;	//����ʱ���ź�
	__delay_us(1);
	DS1302_CE_W =0;	//��λDS1302
	__delay_us(1);	
}
//д�����л�
void DS1302_WP(unsigned char bWP)
{
	if(bWP==0)//��д
	{
		DS1302_WriteCommand(0x8e,0x00);
	}
	else
	{
		DS1302_WriteCommand(0x8e,0x80);
	}
}
//ʱ�ӿ����л�
void DS1302_Switch(unsigned char bStart)
{
	unsigned char s;
	DS1302_CE_W=1;//ʹ��DS1302
	DS1302_WriteByte(0x81);
	s=DS1302_ReadByte();
	DS1302_CE_W=0;	//��λ
	DS1302_WP(0);//�ر�д����
	if(bStart==1)//����
	{
		s=s&0x7f;
	}
	else
	{
		s=s|0x80;	
	}
	DS1302_WriteCommand(0x80,s);
	DS1302_WP(1);//д����
}
//---------------------------------------------
//����ʱ�亯��
void DS1302_SetTime()
{
	unsigned char i;	//����ѭ������
	DS1302_Time.Hour &= 0x7f;//ǿ��Ϊ24Сʱģʽ
	DS1302_WP(0);//�ر�д����
	DS1302_CE_W=1;	//ʹ��DS1302
	DS1302_WriteByte(0xbe);	//ʱ�Ӷ��ֽ�д����
	for(i=0;i<7;i++)	//����д8���ֽ�����
	{
		DS1302_WriteByte(DS1302_Time.Times[i]);	//����дһ���ֽں���
	}
	DS1302_WP(0);//�ر�д����
	DS1302_CE_W=0;	//��λ
	DS1302_WP(1);//д����
}
void DS1302_SetHour24(unsigned char b24)
{
	DS1302_GetTime();
	if(b24==0x01)
		DS1302_Time.Hour &= 0x7f;//ǿ��Ϊ24Сʱģʽ
	else
		DS1302_Time.Hour |= 0x80;
	DS1302_WP(0);//�ر�д����
	DS1302_CE_W=1;	//ʹ��DS1302
	DS1302_WriteByte(0x84);	//ʱ�Ӷ��ֽ�д����
	DS1302_WriteByte(DS1302_Time.Hour);	//����дһ���ֽں���
	DS1302_WP(0);//�ر�д����
	DS1302_CE_W=0;	//��λ
	DS1302_WP(1);//д����
}
//---------------------------------------------
//��ȡʱ�亯��
//��;��;ʱ;��;��;����;��;
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void DS1302_GetTime()
{
	unsigned char i;//����ѭ������
	DS1302_CE_W=1;//ʹ��DS1302
	DS1302_WriteByte(0xbf);//���Ͷ��ֽڶ�ȡ����
	for(i=0;i<7;i++)//������ȡ7���ֽ�����
	{
		DS1302_Time.Times[i]=DS1302_ReadByte();//���ö�ȡ1���ֽ����ݵĺ���
	}
	DS1302_CE_W=0;//��λDS1302
}
void DS1302_ReadTime(DS1302_TIME* t)
{
	unsigned char i;//����ѭ������
	DS1302_CE_W=1;//ʹ��DS1302
	DS1302_WriteByte(0xbf);//���Ͷ��ֽڶ�ȡ����
	for(i=0;i<7;i++)//������ȡ7���ֽ�����
	{
		(*t).Times[i]=DS1302_ReadByte();//���ö�ȡ1���ֽ����ݵĺ���
	}
	DS1302_CE_W=0;//��λDS1302
}
//--------------------------------------------
//дһ���ֽ����ݺ���
void DS1302_WriteCommand(unsigned char cmd,unsigned char data)
{
	DS1302_CE_W=1;	//ʹ��DS1302
	__delay_us(1);
	DS1302_WriteByte(cmd);	//����������
	DS1302_WriteByte(data);	//������������
	__delay_us(1);
	DS1302_CE_W=0;	//��λ
}
//--------------------------------------------
//дһ���ֽ����ݺ���
void DS1302_WriteByte(unsigned char tx)
{
	unsigned char i;	//����ѭ������
	for(i=0;i<8;i++)	//����д8bit
	{
		__delay_us(1);
		DS1302_DATA_W=0;	//����������Ϊ0
		DS1302_CLK_W=0;	//ʱ���ź�����		
		if(tx&0x01)	//�жϴ����͵�����λ��0��1
		{
			 DS1302_DATA_W=1;	//����������λ��1
		}
		__delay_us(1);
		tx=tx>>1;	//�����͵���������1λ
		DS1302_CLK_W=1;	//����ʱ���ź�
	}
	DS1302_CLK_W=0;	//д��һ���ֽڣ�����ʱ���ź�
}
//---------------------------------------------
//��һ���ֽں���
unsigned char DS1302_ReadByte(void)
{
	unsigned char i,rx=0;//����ѭ������
	DS1302_DATA_IO=1;//�������ݿڷ���Ϊ����
	for(i=0;i<8;i++)//������ȡ8bit
	{
		DS1302_CLK_W=0;//����ʱ���ź�
		__delay_us(1);
		rx=rx>>1;//���ռĴ�������1λ
		if(DS1302_DATA_R)
			rx=rx|0x80;//�ѽ��յ������ݷŵ����ռĴ��������λ
		DS1302_CLK_W=1;//����ʱ���ź�
		__delay_us(1);
	}
	DS1302_DATA_IO=0;//�ָ����ݿڷ���Ϊ���
	DS1302_CLK_W=0;//����ʱ���ź�
	return(rx);//���ض�ȡ��������
}
unsigned char DS1302_GetMonth( void )
{
	unsigned char M;	
	M=DS1302_Time.Month&0x0f;
	if(DS1302_Time.Month>0x0f)
		M=M+10;
	return M;
}
unsigned char DS1302_GetDay( void )
{
	unsigned char D;
	D=DS1302_Time.Day>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	}
	D=D+(DS1302_Time.Day&0x0f);
	return D;
}

unsigned char DS1302_GetHour24( void )
{
	unsigned char D;
	D=DS1302_Time.Hour>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	}
	D=D+(DS1302_Time.Hour&0x0f);
	return D;
}
unsigned char DS1302_GetMinute( void )
{
	unsigned char D;
	D=DS1302_Time.Minute>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(DS1302_Time.Minute&0x0f);
	return D;
}

unsigned char DS1302_GetSecond( void )
{
	unsigned char D;
	D=DS1302_Time.Second>>4;
	D=D&0x07;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(DS1302_Time.Second&0x0f);
	return D;
}
unsigned char DS1302_GetNum(unsigned char x)
{
	unsigned char D;
	D=x>>4;
	switch(D)
	{
	case 0x00:
		break;
	case 0x01:
		D=10;
		break;
	case 0x02:
		D=20;
		break;
	case 0x03:
		D=30;
		break;
	case 0x04:
		D=40;
		break;
	case 0x05:
		D=50;
		break;
	}
	D=D+(x&0x0f);
	return D;
}
void DS1302_Convert2Char(void)
{
	DS1302_Time.Year=DS1302_GetNum(DS1302_Time.Year);
	DS1302_Time.Month=DS1302_GetNum(DS1302_Time.Month);
	DS1302_Time.Day=DS1302_GetNum(DS1302_Time.Day);
	DS1302_Time.Hour=DS1302_GetNum(DS1302_Time.Hour);
	DS1302_Time.Minute=DS1302_GetNum(DS1302_Time.Minute);
	DS1302_Time.Second=DS1302_GetNum(DS1302_Time.Second&0x7f);
}
