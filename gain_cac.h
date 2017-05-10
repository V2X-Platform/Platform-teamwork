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

	double H_BS;

	double MT_boresight_gain;

	double BS_boresight_gain;

	double cell_distance;

	int antnum_pBS;

public:
	GAIN_CAC(SCENARIO scenario_data);
	virtual ~GAIN_CAC(void);

	double Cac_Antenna_Gain(double angle_H,double angle_V,bool omni,double boresight_gain);
	double Cac_Antenna_Gain_Horizontal(double angle_phi);
    double Cac_Antenna_Gain_Vertical(double angle_phi);
    //double Cac_Phi_AOA(pair<double,double> ant_pos,pair<double,double> mt_pos);
    //double Cac_Phi_AOD(pair<double,double> ant_pos,pair<double,double> mt_pos);
    double Cac_theta(pair<double,double> ant_pos,pair<double,double> mt_pos);
    double Cac_phi(pair<double,double> ant_pos,pair<double,double> mt_pos);


    virtual double Cac_distloss(bool LoSflag,double dist)=0;
    virtual double Cac_delay(double v,double e)=0;
    virtual void   Cac_pathloss(vector<BASE_INFO*>&base_list,list <MT_INFO*>&mt_list)=0;
};

class MT2MTGAIN_CAC:public GAIN_CAC
{
public:

    double mt2mt_gain;
    double D_BP;

public:
    MT2MTGAIN_CAC(SCENARIO scenario_data);
    ~MT2MTGAIN_CAC(void);

    virtual double Cac_distloss(bool LoSflag,double dist);
    virtual double Cac_delay(double v,double E);
    virtual void   Cac_pathloss(vector<BASE_INFO*>&base_list,list <MT_INFO*>&mt_list);
    void   store_gain(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>>&carrier);   //存储两个用户之间的相关通信信息；

};

class MT2BSGAIN_CAC:public GAIN_CAC
{
public:

    double mt2bs_gain;
    double D_BP;

public:
    MT2BSGAIN_CAC(SCENARIO scenario_data);
    ~MT2BSGAIN_CAC(void);

    virtual double Cac_distloss(bool LoSflag,double dist);
    virtual double Cac_delay(double v,double E);
    virtual void   Cac_pathloss(vector<BASE_INFO*>&base_list,list <MT_INFO*>&mt_list);
    void    store_gain(list<MT_INFO*> &mt_list,vector <BASE_INFO*> &base_list,unordered_map<int,vector<GAIN_INFO*>>&carrier);//存储基站用户之间的相关通信信息；
};


#endif // GAIN_CAC_H_INCLUDED
