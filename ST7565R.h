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
const uint8_t ST7565R_ComTable[]={7,6,5,4,3,2,1,0}; 
#endif
#ifndef ST7565R_ColOffset_Ex
#define ST7565R_ColOffset(x) NOP()
#endif
void ST7565R_Init(void);
void ST7565R_WriteData(uint8_t dat);
void ST7565R_WriteCommand(uint8_t com);
void ST7565R_ShowHZ16x16(uint8_t x,uint8_t y,const uint8_t* zm) ;
void ST7565R_SetVop(uint8_t vop);
 /******************************************************************************** 
 ������:Void ShowHZ16x16(unsigned Addr,uint16_t hzcode) 
 �������ܣ���ʾһ������(16*16����)
            Addr: ��ʾλ��
         hzcode: ���ִ���(�Զ����) 
 ע:������Χ�Ľ�ֱ��д��RAM��,����ʵ�־���Ч��????????
 ********************************************************************************/ 
 void ST7565R_ShowHZ8x16(uint8_t x,uint8_t y,const uint8_t* zm) ;
 void ST7565R_ShowPicByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,const uint8_t* Pic);
 void ST7565R_ShowFullByXY(uint8_t x,uint8_t y,uint8_t Width,uint8_t Height,uint8_t fc);
void ST7565R_ClearScreen(void);
#endif // __ST7565R_h__
