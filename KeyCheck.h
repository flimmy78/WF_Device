#ifndef __KeyCheck_h__
#define __KeyCheck_h__

typedef union   
{
	struct
	{
		unsigned bReKey:1;
	};
	unsigned char AllFlag;
} _KeyCheckFlags;        // general flags

_KeyCheckFlags KeyCheckFlags;

//�����ڼ�⵽�������ⲿ����������⴦��
#ifndef KeyCheckExFun
#define KeyCheck_ExFun()
#endif

//#define KeyCheck_ReadKey(x) x=Key1_R;x|=(Key2_R<<1)
#ifndef KeyCheck_ReKeyTick
#define KeyCheck_ReKeyTick 5
#endif
unsigned char KeyTimes;
unsigned int KeyTick;

#ifdef MatrixKeys
extern unsigned char RowKeyValue;
extern unsigned char ColKeyValue;
#define NoKey 0
#define IsKey 1
//#define ReKey 2
#endif
#ifdef BigKeys
extern unsigned int OldKey;
unsigned int KeyCheck(void);
#else
extern unsigned char OldKey;
unsigned char KeyCheck(void);
#endif
#endif // __Key_h__
