#include "HardwareProfile.h"

void CH45x_Init(void)
{
	CH45x_DCLK_IO=0;
	CH45x_DIN_IO=0;
	CH45x_LOAD_IO=0;
	CH45x_DOUT_IO=1;
	CH45x_RST_IO=0;

	__delay_us(10);		
	CH45x_RST_W=1;
	__delay_us(10);
	CH45x_RST_W=0;
	__delay_us(20);
	CH45x_RST_W=1;
	__delay_us(10);
	CH45x_DIN_W=1;             //�ȵͺ�ߣ�ѡ��4�������ɸ߱�Ϊ���ٱ�Ϊ��
	__delay_us(10);
	CH45x_DIN_W=0;             //�ȵͺ�ߣ�ѡ��4������
	__delay_us(10);
	CH45x_DIN_W=1;

	CH45x_Write(CH45x_RESET);
	CH45x_Write(CH45x_SYSON2);
	CH45x_Write(CH45x_DSP);
	CH45x_Write(CH45x_BCD);
}
//��CH45xд����/���ݺ���
void CH45x_Write(unsigned int command)
{
	unsigned char i;
	CH45x_CloseINT();
	CH45x_LOAD_W=0;                //���ʼ       
	for(i=0;i<12;i++)			 //����12λ���ݣ���λ��ǰ
	{      
		if((command&0x01)==0x01)
			CH45x_DIN_W=1;
		else
			CH45x_DIN_W=0;
		NOP();     
		CH45x_DCLK_W=0;			 //�͵�ƽ����
		command>>=1;
		CH45x_DCLK_W=1;            //��������Ч
	}
	CH45x_LOAD_W=1;                //��������
	CH45x_OpenINT();
}

//��CH45x��ȡһ���ֽں���
unsigned char CH45x_Read(void)
{
	unsigned char i;
	unsigned char command,keycode;     //���������֣������ݴ洢��
	CH45x_CloseINT();
	command=0x07;              		   //�����451������ 
	CH45x_LOAD_W=0;
	for(i=0;i<4;i++)
	{
		if((command&0x01)==0x01)
			CH45x_DIN_W=1;
		else
			CH45x_DIN_W=0;
		NOP();
		CH45x_DCLK_W=0;  		
		command>>=1;           //������һλ
		CH45x_DCLK_W=1;          //����ʱ����������֪ͨCH45x����λ����
	}
	CH45x_LOAD_W=1;              //��������������֪ͨCH45x������������

	CH45x_DOUT_IO=1;          //�ⲿ�ж�������
	keycode=0;                 //���keycode
	for(i=0;i<7;i++)
	{
		keycode<<=1;           //��������keycode,��λ��ǰ,��λ�ں�
		CH45x_DCLK_W=1;
		NOP();    	
		CH45x_DCLK_W=0;          //����ʱ��������֪ͨCH45x�����һλ
		keycode|=CH45x_DOUT_R;   //�Ӹߵ��Ͷ���451������
		NOP();
		CH45x_DCLK_W=1;
	}
	CH45x_OpenINT();
	return keycode;      	 //���ؼ�ֵ
}
