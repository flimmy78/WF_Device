#ifndef __HT9200_h__
#define __HT9200_h__
// #define HT9200_CE_IO TRISB1 //Ƭѡ
// #define HT9200_CE_W TRISB1  

// #define HT9200_CLK_IO RB1 //ʱ��
// #define HT9200_CLK_W RB1     

// #define HT9200_DATA_IO   RB1 //��������/���
// #define HT9200_DATA_W   RB1   
#ifndef HT9200_Serial_Delay
#define HT9200_Serial_Delay()
#endif  
void HT9200_Init(void);
void HT9200_PhoneCall(const char* pPhoneNumber);
void HT9200_CallNum(char Number);
#endif // HT9200_h__



