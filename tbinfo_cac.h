#ifndef TBINFO_CAC_H_INCLUDED
#define TBINFO_CAC_H_INCLUDED

#pragma once

#include "mt_info.h"
#include "simulation.h"
#include "bler_curve.h"
#include "scenario_para.h"


class TBINFO_CAC
{
public:

	double MT_noise_fig;

	double noise_power;

	int realsubnum;

    int success[300+2];

	int s_rate[300+2];

	double RB_Txpower;

	double RB_Txpower_BS;

	double RB_Txpower_MT;

public:

	TBINFO_CAC(SCENARIO scenario_data);

	~TBINFO_CAC(void);

	//virtual void Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)=0;
	virtual bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)=0;
};

class MT2MT_TB:public TBINFO_CAC
{
public:


public:

    void Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data);
    bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr);
    MT2MT_TB(SCENARIO scenario_data);
    ~MT2MT_TB(void);

};

class MT2BS_TB:public TBINFO_CAC
{
public:


public:

    void Cac_Tbinfo(vector<BASE_INFO*> &base_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data);
    bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr);
    MT2BS_TB(SCENARIO scenario_data);
    ~MT2BS_TB(void);

};


#endif // TBINFO_CAC_H_INCLUDED
