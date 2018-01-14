/*************
���ֵ�λ����������
���ֵ�λ������ֵ10K��
*************/
#include "HardwareProfile.h"

void X9C103_Init(void)
{
	X9C103_CS_IO = 0;
	X9C103_UD_IO = 0;
	X9C103_CLK_IO = 0;
	X9C103_CS_W = 0;
	X9C103_UD_W = 0;
	X9C103_CLK_W = 0;
	
	//X9C103_R_Change_Step(X9C103_R_DOWN,99);
}

void X9C103_R_Change_Step(uint8_t Mode,uint8_t N)
{
   	uint8_t i=0; 
   	if(Mode==1)	
   	{
   		X9C103_UD_W = 1;	//���ӵ���
   	}
   	else
   	{
   		X9C103_UD_W = 0;//��С����
   	}
   	__delay_us(3);         // ��ʱ��Լ2us
   	X9C103_CS_W = 0; 	 // CS  ����
   	for(i=N;i>0;i--) 
  	{ 
     	X9C103_CLK_W = 1;  // ����INC    ��ΪINC��������Ч
     	__delay_us(2);         // ��ʱ2us����
     	X9C103_CLK_W = 0;   // INC ����;  // ����һ������
     	__delay_us(100);       // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
  	}
  	X9C103_CLK_W = 1;	//����ģʽ
   	X9C103_CS_W = 1;	// ���CS���� //store
}

