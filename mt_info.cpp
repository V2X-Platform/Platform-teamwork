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

	ACK_list.clear();
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

void MT_INFO::Add_block(int Block_num,double simul_time)
{
	for(int k=0;k<Block_num;k++)
	{
		TransportBlock* m_pTransporBlock= new TransportBlock(packet_topid,block_topid,simul_time);

		TBQueue.push_back(m_pTransporBlock);

		block_topid++;
		block_num++;
	}
}

MT_INFO::~MT_INFO(void){}

