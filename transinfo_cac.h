#ifndef TRANSINFO_CAC_H_INCLUDED
#define TRANSINFO_CAC_H_INCLUDED

#pragma once

#include "mt_info.h"
#include "simulation.h"
#include "bler_curve.h"

class TRANSINFO_CAC
{
private:

	double noise_power;

	double BS_Power;

	double RB_Txpower;

	int realsubnum; //×ÓÔØ²¨Êý

	int success[MT_num];

	int s_rate[MT_num];


public:

	TRANSINFO_CAC(int x);

	~TRANSINFO_CAC(void);

	void Cac_Transinfo_STEP1A(list<MT_INFO*> &mt_list,unordered_map<int,unordered_set<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data);
	bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr);
	//void Cac_Resinfo_STEP1C_MRC(list<MT_INFO*> &mt_list,vector<BASE_INFO*> &base_list,double simul_time,BLER_CURVE &bler_data);//----20090608---ling lisha
	//void Cac_Resinfo_MMSE_TS(list<MT_INFO*> &mt_list,vector<BASE_INFO*> &base_list,double simul_time,BLER_CURVE &bler_data,CODEBOOK &codebook);
};


#endif // TRANSINFO_CAC_H_INCLUDED
