#ifndef __LC160160B_h__
#define __LC160160B_h__

void LC160160B_Init(void);
void LC160160B_WriteD(unsigned char dat);
void LC160160B_WriteC(unsigned char cmd);
/******************************************************************************** 
������:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LC160160B_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm); 

/******************************************************************************** 
������:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
�������ܣ���ʾһ������(16*16����)
           Addr: ��ʾλ��
        hzcode: ���ִ���(�Զ����) 
ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
********************************************************************************/ 
void LC160160B_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm);

void LC160160B_ShowPic(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);

/********************************************************************************
������: Void ClearScreen(unsigned int ram)
��������: ���������Ļ
     ram : ��Ҫ����ĵ�Ԫ��
********************************************************************************/
void LC160160B_ClearScreen(void);

void LC160160B_Write8Dots2LCD(unsigned char uc_dat);

#endif // __LC160160B_h__
