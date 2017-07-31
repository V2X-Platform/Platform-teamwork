#ifndef MT_INFO_H_INCLUDED
#define MT_INFO_H_INCLUDED

#pragma once
#include "system_para.h"
#include "scenario_para.h"
#include "gain_info.h"
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class MT_INFO
{
public:
	/********************** mt commen parameter *************/

	int mt_id;								//mt index in the simulation

	pair <int,int> mt_position;		        //mt position

	int x_sort;

	int y_sort;

	double gen_time;						//generate time

	bool LOS_flag;

	int id_inline;

    int total_inline;

	int line_id;                            //当前道路数目

    double Tn;								// user average throughput in a lenght of time

	double arrarray_direction;               //天线朝向

    double DiscardPacketTotal;				//discard packet num

	double DiscardBitTotal;					//discard bit number

    double SendPacketTotal;					//send packet number

	double SendBlockTotal;					//send block number

	double SendBitTotal;						//the throughput of the MT

	double PacketDelayTotal;				//packet delay total



	unordered_set<GAIN_INFO*> comm_mt;

	vector<GAIN_INFO*> comm_mt_list;

public:

	MT_INFO(int id);
	MT_INFO();

    void Sending_data(double simultime);

	~MT_INFO(void);

};

#endif // MT_INFO_H_INCLUDED
