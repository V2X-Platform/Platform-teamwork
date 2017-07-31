#include "StdAfx.h"
#include "mt_info.h"
#include "scenario_para.h"

MT_INFO::MT_INFO(int id)

{
	mt_id = id;

	DiscardPacketTotal = 0;

	DiscardBitTotal = 0;

	SendPacketTotal = 0;

	SendBlockTotal = 0;

	SendBitTotal = 0;
}

MT_INFO::MT_INFO(){}

void MT_INFO::Sending_data(double simultime)
{
	Tn = Tn + sending_bitnum;

	sendbit_num = sendbit_num + sending_bitnum;

	//sending_bitnum = 0;

	//res_num = 0;

	//serving_state = FALSE;
}

MT_INFO::~MT_INFO(void){}

