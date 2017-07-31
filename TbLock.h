#ifndef TBLOCK_H_INCLUDED
#define TBLOCK_H_INCLUDED

#include "system_para.h"
#include "scenario_para.h"

class TBLOCK_INFO
{
public:

	int paket_id;//L3数据包

	int TB_id;// L2数据

	int TB_size;

	int Modulation;//当前传输块的调制方式

	double code_rate;//码率

	double Generate_times;//包产生的时间

	int transmit_times;//已传输次数

	TBLOCK_INFO(int paket_i,int TB_i,double gen_time);

	TBLOCK_INFO();

	~TBLOCK_INFO();

	void Clear();

	void Increase_TransTimes();

	int Get_TransTimes();

	void Set_MCS(int CQI_index);

	void Set_TBsize(int RB_num);
};

#endif // TBLOCK_H_INCLUDED
