
#ifndef TRANSPOTBLOCK_H_INCLUDED
#define TRANSPOTBLOCK_H_INCLUDED

#pragma once

#include "system_para.h"
#include "scenario_para.h"

class TransportBlock
{
public:

	int paket_id;//L3数据包

	int TB_id;// L2数据

	int TB_size;

	int Modulation;//当前传输块的调制方式

	double code_rate;//码率

	double Generate_times;//包产生的时间

	int transmit_times;//已传输次数

	TransportBlock(int paket_i,int TB_i,double gen_time);

	TransportBlock();

	~TransportBlock();

	void Clear();

	void Increase_TransTimes();

	int Get_TransTimes();

	void Set_MCS(int CQI_index);

	void Set_TBsize(int RB_num);
};

#endif // TRANSPOTBLOCK_H_INCLUDED
