#ifndef __PID_h__
#define __PID_h__

//#define PID_PShift 1
//#define PID_IShift 1
//#define PID_DShift 1
//
//#define PID_DeltaRef 5
//#define PID_BigError 50
// #ifdef PID_Debug
// unsigned char PIDDebug[100];
// #endif
typedef union
{	
	unsigned char AllChar[13];
	struct
	{
		unsigned int Ref;
		unsigned int FeedBack;
		signed int PreError;//ǰһ�����, Ref - FeedBack 
		signed int PreErrorSum;//֮ǰ������;
		signed char Kp;			//�ٶ�PID��Ka = Kp 
		signed char Ki;			//�ٶ�PID��Kb = ( T / Ti ) 
		signed char Kd;			//�ٶ�PID��kc =  ( Td / T ) 
		signed int Out;		//ת�ٵ���������ֵ 
		unsigned int DeltaRef;//����ƫ�Χ
		unsigned int BigError;//�����������ֲ���
	};	
}_PIDParam;
_PIDParam PIDParam;
unsigned char PIDCalc(void);
void PID_Init(void);

#ifdef PID2
_PIDParam PID2Param;
unsigned char PID2Calc(void);
void PID2_Init(void);
#endif
#endif
