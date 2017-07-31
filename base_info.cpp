#pragma once

#include "stdafx.h"
#include "base_info.h"
#include "system_para.h"
#include "extern.h"
#include "mt_info.h"

BASE_INFO::BASE_INFO(SCENARIO scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside)
{
    antnum = scenario_data.antnumtotal;
	RBnum = sys_RBnum;
	antnum_pBS = scenario_data.antnum_pBS;
	MT_num = scenario_data.MT_num;

    base_id = baseid+MT_num;
    base_pos= scenario_data.base_vect[baseid];

    Theta = new double [antnum_pBS];
    ant_pos = new pair<double,double> [antnum_pBS];

    for(int ant_index = 0; ant_index<antnum_pBS; ant_index++)
	{
		ant_pos[ant_index] = antpos[ant_index];

		Theta[ant_index] = theta[ant_index];

	}

    sendpacket_num = 0;

	sendblock_num = 0;

	sendbit_num = 0;

	discardpacket_num = 0;

	discardbit_num  = 0;

}

BASE_INFO::BASE_INFO(){}

BASE_INFO::~BASE_INFO(void)
{
   delete [] Theta;
   delete [] ant_pos;
}


/*void BASE_INFO::Sending_data(double simultime)
{
	double send_bnum;

	list<MT_INFO*>::iterator MtPtr;

	vector<GAIN_INFO*>:: iterator PacketPtr;

	for(PacketPtr = comm_mt_list.begin();PacketPtr!=comm_mt_list.end();PacketPtr++)
    {
        (*MtPtr)->Sending_data(simultime);

        //send_bnum = (*MtPtr)->Get_sendingbitnum();

        //ant_sendbitnum[ant_index]  = ant_sendbitnum[ant_index] + send_bnum;

        sendbit_num = sendbit_num + send_bnum;

        //discardbit_num = discardbit_num + (*MtPtr)->Get_discardingbitnum();

        //sendpacket_num = sendpacket_num + (*MtPtr)->sending_packetnum;

        //discardpacket_num = discardpacket_num + (*MtPtr)->discarding_packetnum;

        //(*MtPtr)->DiscardBitTotal = 0;

        //(*MtPtr)->sending_packetnum = 0;

        //(*MtPtr)->discarding_packetnum = 0;

        //(*MtPtr)->sendblock_num = 0;
			//----------------------------------------------------------
        //vec_change += (*MtPtr)->change;

        //vec_unchange += (*MtPtr)->unchange;

        //(*MtPtr)->change = 0;

        //(*MtPtr)->unchange = 0;

    }

	for(int ant_index = 0; ant_index<bp_antnum; ant_index++)
	{
		for(MtPtr = AP_list[ant_index]->ap_mtlist.begin(); MtPtr != AP_list[ant_index]->ap_mtlist.end(); MtPtr++)

		{
			(*MtPtr)->Sending_data(simultime);

			send_bnum = (*MtPtr)->Get_sendingbitnum();

			ant_sendbitnum[ant_index]  = ant_sendbitnum[ant_index] + send_bnum;

			sendbit_num = sendbit_num + send_bnum;

			discardbit_num = discardbit_num + (*MtPtr)->Get_discardingbitnum();

			sendpacket_num = sendpacket_num + (*MtPtr)->sending_packetnum;

			discardpacket_num = discardpacket_num + (*MtPtr)->discarding_packetnum;

			(*MtPtr)->discarding_bitnum = 0;

			(*MtPtr)->sending_packetnum = 0;

			(*MtPtr)->discarding_packetnum = 0;

			(*MtPtr)->sendblock_num = 0;
			//----------------------------------------------------------
			//vec_change += (*MtPtr)->change;

			//vec_unchange += (*MtPtr)->unchange;

			//(*MtPtr)->change = 0;

			//(*MtPtr)->unchange = 0;
		}
	}

}*/
