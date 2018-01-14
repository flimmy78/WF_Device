#ifndef __HT162X_h__
#define __HT162X_h__


// #define HT162X_DATA_DIR TRISB1
// #define HT162X_DATA RB1
// #define HT162X_CS   RB1  
// #define HT162X_WR   RB1  
// #define HT162X_RD	RB1
/************************************************************************/
/* �����ֺ궨��                                                         */
/************************************************************************/
#define HT162X_SYS_DIS	0b00000000 // �ر�ϵͳ������LCD ƫѹ������
#define HT162X_SYS_EN	0b00000001 // ��ϵͳ����
#define HT162X_LCD_OFF	0b00000010 // �ر�LCD ƫѹ������
#define HT162X_LCD_ON	0b00000011 // ��LCD ƫѹ������
#define HT162X_TIMER_DIS 0b00000100 // ʱ�����ʧЧ
#define HT162X_WDT_DIS	0b00000101 // WDT �����־���ʧЧ
#define HT162X_TIMER_EN 0b00000110 // ʱ�����ʹ��
#define HT162X_WDT_EN	0b00000111 // WDT �����־�����Ч
#define HT162X_TONE_OFF 0b00001000 // �ر��������
#define HT162X_TONE_ON	0b00001001 // ���������
#define HT162X_CLR_TIMER 0b00001100 // ʱ������������
#define HT162X_CLR_WDT	0b00001110 // ���WDT ״̬
#define HT162X_XTAL_32K	0b00010100 // ϵͳʱ��Դ����
#define HT162X_RC_256K	0b00011000 // ϵͳʱ��ԴƬ��RC ����
#define HT162X_EXT_256K 0b00011100 // ϵͳʱ��Դ�ⲿʱ��Դ
#define HT162X_TONE_4K	0b01000000 // ����Ƶ��4KHz
#define HT162X_TONE_2K	0b01100000 // ����Ƶ��2KHz
#define HT162X_IRQ_DIS	0b10000000 // ʹ/IRQ ���ʧЧ
#define HT162X_IRQ_EN	0b10001000 // ʹ/IRQ �����Ч
#define HT162X_F1	0b10100000 // ʱ��/WDT ʱ�����1Hz
#define HT162X_F2	0b10100001 // ʱ��/WDT ʱ�����2Hz
#define HT162X_F4	0b10100010 // ʱ��/WDT ʱ�����4Hz
#define HT162X_F8	0b10100011 // ʱ��/WDT ʱ�����8Hz
#define HT162X_F16	0b10100100 // ʱ��/WDT ʱ�����16Hz
#define HT162X_F32	0b10100101 // ʱ��/WDT ʱ�����32Hz
#define HT162X_F64	0b10100110 // ʱ��/WDT ʱ�����64Hz
#define HT162X_F128 0b10100111 // ʱ��/WDT ʱ�����128Hz
#define HT162X_TOPT 0b11100000 // ����ģʽ
#define HT162X_TNORMAL 0b11100011 // ��ͨģʽ


void HT162X_Setting(uint8_t x);

void HT162X_WriteData(uint8_t reg,uint8_t data);

void HT162X_WriteDatas(uint8_t reg,const uint8_t* pBuf,uint8_t count);

void HT162X_Init(void);
#endif

