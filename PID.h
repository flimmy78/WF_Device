#ifndef __PID_h__
#define __PID_h__

//#define PID_PShift 1
//#define PID_IShift 1
//#define PID_DShift 1
//
//#define PID_DeltaRef 5
//#define PID_BigError 50
// #ifdef PID_Debug
// uint8_t PIDDebug[100];
// #endif
typedef union
{	
	uint8_t AllChar[13];
	struct
	{
		uint16_t Ref;
		uint16_t FeedBack;
		signed int PreError;//ǰһ�����, Ref - FeedBack 
		signed int PreErrorSum;//֮ǰ������;
		signed char Kp;			//�ٶ�PID��Ka = Kp 
		signed char Ki;			//�ٶ�PID��Kb = ( T / Ti ) 
		signed char Kd;			//�ٶ�PID��kc =  ( Td / T ) 
		signed int Out;		//ת�ٵ���������ֵ 
		uint16_t DeltaRef;//����ƫ�Χ
		uint16_t BigError;//�����������ֲ���
	};	
}_PIDParam;
_PIDParam PIDParam;
uint8_t PIDCalc(void);
void PID_Init(void);

#ifdef PID2
_PIDParam PID2Param;
uint8_t PID2Calc(void);
void PID2_Init(void);
#endif
#endif
