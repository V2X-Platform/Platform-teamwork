#ifndef ACKINFO_H_INCLUDED
#define ACKINFO_H_INCLUDED

#pragma once

#include "system_para.h"
#include "scenario_para.h"

class AckInfo
{
public:

	//bool ACK_flag[MT_Max_layernum];

	bool bAck;

	int ACK_num;						// 用户ACK/NACK数,对应传输层数

	int HARQ_No;

	int Feedback_Delay_inTTI;

	/*ACK_INFO(int layer_num,bool *ACK_indicate,int HARQ_n,int Delay_inTTI)
	{
		ACK_num = layer_num;

		for(int L=0;L<(layer_num<=MT_Max_layernum?layer_num:MT_Max_layernum);L++)
		{
			ACK_flag[L] = ACK_indicate[L];
		}

		HARQ_No = HARQ_n;
		Feedback_Delay_inTTI = Delay_inTTI;
	}*/

public:
    AckInfo(bool bAckTemp);
    ~AckInfo();
};
#endif // ACKINFO_H_INCLUDED
