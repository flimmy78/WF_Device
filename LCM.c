#include "HardwareProfile.h"


// #define LCM_DATA RC1    //Һ������
// #define LCM_WR  RC2    //Һ��ʱ��
// #define LCM_CS 	 RC3	//Һ��Ƭѡ
// 
// #define LCM_DATA_DIR RC1    //Һ������
// #define LCM_WR_DIR  RC2    //Һ��ʱ��
// #define LCM_CS_DIR 	 RC3	//Һ��Ƭѡ
// 
// #define LCM_DATALENGTH 4
// #define LCM_INIT 0b00101001

void LCM_WriteBit(unsigned char wb)   
{  
	if(wb==0)
		LCM_DATA=0;
	else
		LCM_DATA=1;
   	NOP();   
      
   	LCM_WR = 1;   
   	NOP();   
      
   	LCM_WR = 0;   
   	NOP();   
      
   	LCM_WR = 1;   
}   
//�Ϳ�����   
void LCM_WriteCmd(unsigned char cmdcode)      
{  
	unsigned char i;   
	LCM_CS=1;   
	LCM_CS=0;  
	LCM_WriteBit(1);   
	LCM_WriteBit(0);  
	LCM_WriteBit(0);   
	for (i=0;i<8;i++)   
	{  
		if((cmdcode&0x80)==0x80)   
			LCM_WriteBit(1);    
		else
			LCM_WriteBit(0);     
		cmdcode<<=1;   
	}    
	LCM_WriteBit(0);   
	LCM_DATA=1;   
	LCM_CS=1;   
}   
//��ʼ��     
void LCM_Init(void)       
{  
	LCM_DATA_DIR=0;
	LCM_WR_DIR=0;
	LCM_CS_DIR=0;
	__delay_ms(10);
	LCM_WriteCmd(0x00);                  //����0    
   	LCM_WriteCmd(0x02);               //�ر�2    
   	LCM_WriteCmd(0x01);                   //�ϵ�1    
   	LCM_WriteCmd(0x03);                //��ʾ3    
   	LCM_WriteCmd(LCM_INIT);                 //ģʽ����29    
}   
//��6λ��ַ+LCM_DATALENGTHλ����
void LCM_WriteData(unsigned char address,unsigned char data)      
{  
	unsigned char i;   
   	LCM_CS = 1;   
   	LCM_CS = 0;   
   	LCM_WriteBit(1);  
   	LCM_WriteBit(0);   
   	LCM_WriteBit(1);   
   	address<<=2;   
   	for (i=0;i<6;i++)   
   	{  
	   	if((address&0x80)==0x80)   
         	LCM_WriteBit(1); 
      	else 
      		LCM_WriteBit(0);   
      	address<<=1;   
   	}  
  	for (i=0;i<LCM_DATALENGTH;i++)   
   	{  
	   	if((data&0x01)==0x01)   
         	LCM_WriteBit(1);  
      	else 
      		LCM_WriteBit(0);  
            
      	data>>=1;   
   	}   
   	LCM_DATA=1;   
   	LCM_CS=1;   
}   
//����д
void LCM_WriteDatas(unsigned char address,unsigned char len,unsigned char* pData)      
{  
	unsigned char i,j,data;   
	LCM_CS = 1;   
	LCM_CS = 0;   
	LCM_WriteBit(1);  
	LCM_WriteBit(0);   
	LCM_WriteBit(1);   
	address<<=2;   
	for (i=0;i<6;i++)   
	{  
		if((address&0x80)==0x80)   
			LCM_WriteBit(1); 
		else 
			LCM_WriteBit(0);   
		address<<=1;   
	}  
	for(i=0;i<len;i++)
	{
		data=*pData;		pData++;
		
		for (j=0;j<LCM_DATALENGTH;j++)   
		{  
			if((data&0x01)==0x01)   
				LCM_WriteBit(1); 
			else 
				LCM_WriteBit(0); 			  
			data>>=1;   
		}   
	}	
	LCM_DATA=1;   
	LCM_CS=1;   
}
