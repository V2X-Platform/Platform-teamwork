#ifndef GAIN_INFO_H_INCLUDED
#define GAIN_INFO_H_INCLUDED

#include "system_para.h"
#include <utility>

using namespace std;

class GAIN_INFO
{
public:

    int send_id;

    int target_id;

	double distloss;//对数值

	double pathloss;

	double pathloss_dB;

	double Atotal;  //对数值

	double Antenna_Gain;

	double delay;

	bool LOS_flag;

	bool bs2mt_flag;

	pair<int,int> dis_vect;

	//double Atotal;

	double Phi_AOA;

	double phi_AOS;

	double PacketSize;


public:

    GAIN_INFO(int s_id,int t_id);
    ~GAIN_INFO(void);

};

#endif // GAIN_INFO_H_INCLUDED
