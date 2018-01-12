#ifndef __ST7565R_h__
#define __ST7565R_h__

//���У�˳������
/*
#define ST7565R_CS_DIR	TRISF2
#define ST7565R_CS_W	LATF2

#define ST7565R_CD_DIR	TRISF3
#define ST7565R_CD_W	LATF3

#define ST7565R_SCL_DIR	TRISF5
#define ST7565R_SCL_W	LATF5

#define ST7565R_DATA_DIR TRISF6
#define ST7565R_DATA_W	 LATF6
#define ST7565R_DATA_R	 RF6
*/
#ifndef ST7565R_ComTable_Ex
const unsigned char ST7565R_ComTable[]={7,6,5,4,3,2,1,0}; 
#endif
#ifndef ST7565R_ColOffset_Ex
#define ST7565R_ColOffset(x) NOP()
#endif
void ST7565R_Init(void);
void ST7565R_WriteData(unsigned char dat);
void ST7565R_WriteCommand(unsigned char com);
void ST7565R_ShowHZ16x16(unsigned char x,unsigned char y,const unsigned char* zm) ;
void ST7565R_SetVop(unsigned char vop);
 /******************************************************************************** 
 ������:Void ShowHZ16x16(unsigned Addr,unsigned int hzcode) 
 �������ܣ���ʾһ������(16*16����)
            Addr: ��ʾλ��
         hzcode: ���ִ���(�Զ����) 
 ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
 ********************************************************************************/ 
 void ST7565R_ShowHZ8x16(unsigned char x,unsigned char y,const unsigned char* zm) ;
 void ST7565R_ShowPicByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,const unsigned char* Pic);
 void ST7565R_ShowFullByXY(unsigned char x,unsigned char y,unsigned char Width,unsigned char Height,unsigned char fc);
void ST7565R_ClearScreen(void);
#endif // __ST7565R_h__
