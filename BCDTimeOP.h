#ifndef TimeOP_h__
#define TimeOP_h__

typedef union
{	
	unsigned char Times[8];
	struct
	{
		unsigned char Year;
		unsigned char Month;
		unsigned char Day;
		unsigned char Hour;
		unsigned char Minute;
		unsigned char Second;
		unsigned char Week;
	};	
}_SystemBCDTime;
unsigned char GetMonthDay_BCD(unsigned char Y,unsigned char M);
unsigned char GetMonthDay(unsigned char Y,unsigned char M);

void BCDDateTimeAdd1M(_SystemBCDTime* dt);

void BCDDateTimeAddMinutes(_SystemBCDTime* dt,unsigned int MS);

unsigned int GetMinutesGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

//�����Сʱ��ʱ����
unsigned int GetHourGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

//��������ʱ����
unsigned int GetDayGap_BCD(_SystemBCDTime dts,_SystemBCDTime dte);

#endif // TimeOP_h__
