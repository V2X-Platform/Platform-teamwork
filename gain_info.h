#ifndef GAIN_INFO_H_INCLUDED
#define GAIN_INFO_H_INCLUDED

#pragma once
#include "system_para.h"
#include <utility>

using namespace std;

class GAIN_INFO
{
public:

    int send_id;

    int target_id;

	double distloss;

	double pathloss;

	double pathloss_dB;

	double coupling_loss;

	bool LOS_flag;

	pair<int,int> dis_vect;

public:

    GAIN_INFO(int s_id,int t_id);
    ~GAIN_INFO(void);

};

#endif // GAIN_INFO_H_INCLUDED
