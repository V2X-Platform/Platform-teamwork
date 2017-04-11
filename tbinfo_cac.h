#ifndef TBINFO_CAC_H_INCLUDED
#define TBINFO_CAC_H_INCLUDED

#pragma once

#include "mt_info.h"
#include "simulation.h"
#include "bler_curve.h"


class TBINFO_CAC
{
public:

	double noise_power;

	int realsubnum;

	double RB_Txpower;

public:

	TBINFO_CAC(int x);

	~TBINFO_CAC(void);

	virtual void Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)=0;
	virtual bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)=0;
};

class MT2MT_TB:public TBINFO_CAC
{
public:


    double MT_Power;

    int success[MT_num];

	int s_rate[MT_num];

public:

    void Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data);
    bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr);
    MT2MT_TB(int x);
    ~MT2MT_TB(void);

};

class MT2BS_TB:public TBINFO_CAC
{
public:

    double BS_Power;

public:

    void Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data);
    bool Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr);
    MT2BS_TB(int x);
    ~MT2BS_TB(void);

};


#endif // TBINFO_CAC_H_INCLUDED
