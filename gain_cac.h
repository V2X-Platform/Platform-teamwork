#ifndef GAIN_CAC_H_INCLUDED
#define GAIN_CAC_H_INCLUDED

#include "scenario_para.h"
#include "simulation.h"
#include "extern.h"

class GAIN_CAC
{
public:

	double CF;

	double H_MT;


public:
	GAIN_CAC(int x);
	virtual ~GAIN_CAC(void);

    virtual double Cac_distloss(bool LoSflag,double dist)=0;


};

class MT2MTGAIN_CAC:public GAIN_CAC
{
public:

    double mt2mt_gain;
    double D_BP;

public:
    MT2MTGAIN_CAC(int x);
    ~MT2MTGAIN_CAC(void);

    void Cac_pathloss(list<MT_INFO*> &mt_list);
    double Cac_distloss(bool LoSflag,double dist);
    void store_gain(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>>&carrier);   //存储两个用户之间的相关通信信息；
};

class MT2BSGAIN_CAC:public GAIN_CAC
{
public:

    double mt2bs_gain;
    double D_BP;
    double H_BS;

public:
    MT2BSGAIN_CAC(int x);
    ~MT2BSGAIN_CAC(void);

    double Cac_distloss(bool LoSflag,double dist);
    void  Cac_pathloss(list<MT_INFO*> &mt_list,vector<BASE_INFO*> &base_list);
    void  store_gain(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>>&carrier);   //存储两个用户之间的相关通信信息；
};


#endif // GAIN_CAC_H_INCLUDED
