#ifndef __CH45x_h__
#define __CH45x_h__

#include "main.h"
//CH45xW4
// #define CH45x_DCLK_W TRISB1  //��������ʱ�������Ӽ���
// #define CH45x_DIN_W RB1      //���������������CH45x����������
// #define CH45x_LOAD_W   RB1   //����������أ������Ӽ���
// #define CH45x_DOUT_R   RB1   //INT1�������жϺͼ�ֵ�������룬��CH45x���������
// #define CH45x_RST_W   RB1   //INT1�������жϺͼ�ֵ�������룬��CH45x���������
// 
// 
// #define CH45x_DCLK_IO TRISB1
// #define CH45x_DIN_IO RB1
// #define CH45x_LOAD_IO   RB1  
// #define CH45x_DOUT_IO   RB1 
// #define CH45x_RST_IO   RB1   //INT1�������жϺͼ�ֵ�������룬��CH45x���������

#define CH45x_RESET      0X0201    //��λ
#define CH45x_LEFTMOV    0X0300    //����
#define CH45x_LEFTCYC    0X0301    //��ѭ
#define CH45x_RIGHTMOV   0X0302   //����
#define CH45x_RIGHTCYC   0X0303   //��ѭ
#define CH45x_SYSOFF     0x0400     //����ʾ�����̡����Ź�
#define CH45x_SYSON1     0x0401     //����ʾ
#define CH45x_SYSON2     0x0403     //����ʾ������
#define CH45x_SYSON3     0x0407     //����ʾ�����̡����Ź�����
#define CH45x_DSP        0x0500     //����Ĭ����ʾ��ʽ
#define CH45x_BCD        0x0580     //����BCD���뷽ʽ
#define CH45x_TWINKLE    0x0600     //������˸����

#ifdef CH45x_noINT
#define CH45x_CloseINT()
#define CH45x_OpenINT() 
#endif
void CH45x_Init(void);
uint8_t CH45x_Read(void);
void CH45x_Write(uint16_t command);
#endif // __CH45x_h__
