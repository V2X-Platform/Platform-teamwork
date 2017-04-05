#ifndef MT2MTGAIN_H_INCLUDED
#define MT2MTGAIN_H_INCLUDED

#include "scenario_para.h"
#include "simulation.h"
#include "extern.h"

class MT2MTGAIN_CAC
{
private:

	double CF;

	double H_BS,H_MT;

	double mt2mt_gain;

	double D_BP;


public:
	MT2MTGAIN_CAC(int x);
	~MT2MTGAIN_CAC(void);

	void Cac_pathloss(list<MT_INFO*> &mt_list);
    double Cac_distloss(bool LoSflag,double mt2mt_dist);
    void store_gain(list<MT_INFO*> &mt_list,unordered_map<int,unordered_set<GAIN_INFO*>>&carrier);   //存储两个用户之间的相关通信信息；

};

#endif // MT2MTGAIN_H_INCLUDED


