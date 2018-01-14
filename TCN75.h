#ifndef __TCN75_h__
#define __TCN75_h__

#include "main.h"
#ifndef TCN75_RetryCount
#define TCN75_RetryCount 2
#endif

#ifndef TCN75_Addr
#define TCN75_Addr 0b10010000
#endif


#ifndef TCN75_MaxPLL
#define TCN75_MaxPLL 0x331b
#endif

#ifndef TCN75_MinPLL
#define TCN75_MinPLL 0x299d
#endif
enum {TCN75_TEMP=0x00,TCN75_T_HYST=0x02,TCN75_T_SET=0x03};
u16_wf TCN75_RegReadResualt;
typedef union   
{
	struct
	{		
		unsigned bShutdown:1;	
		unsigned COMP_INT:1;
		unsigned Polarity:1;//���ԣ�0����Ч��1����Ч
		unsigned FaultQueue:2;//��·������,��INT/CMPTR���������֮ǰ������ͬ����������¶ȵ�����ת������Ŀ
		unsigned Resolution:2;
		unsigned OneShot:1;
	};
	uint8_t AllFlag;
} _TCN75_Config;        // general flags

_TCN75_Config TCN75_Config;
void TCN75_Init(void);
uint8_t TCN75_ReadReg(uint8_t RegPoint);
uint8_t TCN75_SetConfig(void);
uint8_t TCN75_ReadConfig(void);
#endif
