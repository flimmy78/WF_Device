#include "HardwareProfile.h"
#include "GPS_GPRMC.h"
#include <string.h>
     
_GPS_GPRMC GPS_GPRMC;
unsigned char GPS_GPRMC_DataProc( char* data )
{
	unsigned char dotIndex[12];
	unsigned char dotCount=0;
	unsigned char i,j;
	if(data[0]!='$')
		return 0;
	if(data[1]!='G')
		return 0;
	if(data[2]!='P')
		return 0;
	if(data[3]!='R')
		return 0;
	if(data[4]!='M')
		return 0;
	if(data[5]!='C')
		return 0;
	for(i=0;;i++)
	{
		if(data[i]=='*')
			break;
		if(data[i]==',')
		{
			dotIndex[dotCount++]=i;
			if(dotCount>11)
				return 0;
		}		
	}
	if(dotCount!=11 && dotCount!=12)
		return 0;
	//$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh
	//$GPRMC
	for(i=0;i<dotIndex[0];i++)
	{
		GPS_GPRMC.Header[i]=data[i];
	}
	//<1> UTCʱ�䣬hhmmss.sss(ʱ����.����)��ʽ
	for(j=0;j<10;j++)
	{
		GPS_GPRMC.UTCTime[j]=0;
	}
	for(i=dotIndex[0]+1,j=0;i<dotIndex[1];i++,j++)
	{
		GPS_GPRMC.UTCTime[j]=data[i];
	}
	//<2> ��λ״̬��A=��Ч��λ��V=��Ч��λ
	for(i=dotIndex[1]+1,j=0;i<dotIndex[2];i++,j++)
	{
		GPS_GPRMC.AV=data[i];
	}
	//<3> γ��ddmm.mmmm(�ȷ�)��ʽ(ǰ���0Ҳ��������)
	for(i=dotIndex[2]+1,j=0;i<dotIndex[3];i++,j++)
	{
		GPS_GPRMC.Latitude[j]=data[i];
	}
	//<4> γ�Ȱ���N(������)��S(�ϰ���)
	for(i=dotIndex[3]+1,j=0;i<dotIndex[4];i++,j++)
	{
		GPS_GPRMC.NS=data[i];
	}
	//<5> ����dddmm.mmmm(�ȷ�)��ʽ(ǰ���0Ҳ��������)
	for(i=dotIndex[4]+1,j=0;i<dotIndex[5];i++,j++)
	{
		GPS_GPRMC.Longitude[j]=data[i];
	}
	//<6> ���Ȱ���E(����)��W(����)
	for(i=dotIndex[5]+1,j=0;i<dotIndex[6];i++,j++)
	{
		GPS_GPRMC.EW=data[i];
	}
	//<7> ��������(000.0~999.9�ڣ�ǰ���0Ҳ��������)
	for(i=dotIndex[6]+1,j=0;i<dotIndex[7];i++,j++)
	{
		GPS_GPRMC.GPSSpeed[j]=data[i];
	}
	//<8> ���溽��(000.0~359.9�ȣ�������Ϊ�ο���׼��ǰ���0Ҳ��������)
	for(i=dotIndex[7]+1,j=0;i<dotIndex[8];i++,j++)
	{
		GPS_GPRMC.Course[j]=data[i];
	}
	//<9> UTC���ڣ�ddmmyy(������)��ʽ
	for(i=dotIndex[8]+1,j=0;i<dotIndex[9];i++,j++)
	{
		GPS_GPRMC.UTCDate[j]=data[i];
	}
	//<10> ��ƫ��(000.0~180.0�ȣ�ǰ���0Ҳ��������)
	for(i=dotIndex[9]+1,j=0;i<dotIndex[10];i++,j++)
	{
		GPS_GPRMC.CPJ[j]=data[i];
	}
	if(dotCount==12)
	{
		//<11> ��ƫ�Ƿ���E(��)��W(��)
		for(i=dotIndex[10]+1,j=0;i<dotIndex[11];i++,j++)
		{
			GPS_GPRMC.CPJFX=data[i];
		}
		//<12> ģʽָʾ(��NMEA0183 3.00�汾�����A=������λ��D=��֣�E=���㣬N=������Ч)
		for(i=dotIndex[11]+1,j=0;;i++,j++)
		{
			if(data[i]=='*')
				break;
			GPS_GPRMC.UTCTime[j]=data[i];
		}
	}
	else
	{
		//<11> ��ƫ�Ƿ���E(��)��W(��)
		for(i=dotIndex[10]+1,j=0;;i++,j++)
		{
			if(data[i]=='*')
				break;
			GPS_GPRMC.CPJFX=data[i];
		}		
	}
	return 1;
}
