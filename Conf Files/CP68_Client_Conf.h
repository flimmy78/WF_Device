#ifndef __CP68_Client_Conf_h__
#define __CP68_Client_Conf_h__

#include "usart.h"
#include "wfSys.h"
#define CP68_USART_Handle huart1
/************************************************************************/
/* �û������                                                         */
/************************************************************************/
#define CP68_UserCommand_ReadAD 0x21 //��ȡ��ǰ3·ADֵ
#define CP68_UserCommand_WriteTCalc 0x22 //д���¶ȼ���ϵ��
#define CP68_UserCommand_ReadPress 0x23 //д���¶ȼ���ϵ��
#define CP68_UserCommand_WriteQCalc 0x24 //д����������ϵ��
#define CP68_UserCommand_WriteDeviceParams 0x25 //д���¶ȼ���ϵ��
#endif


