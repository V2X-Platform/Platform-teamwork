#pragma once

#include "system_para.h"
#include "scenario_para.h"
#include "gain_info.h"

GAIN_INFO::GAIN_INFO(int s_id,int t_id)

{
    send_id =s_id;

    target_id = t_id;

    distloss = FALSE_VALUE;

    pathloss = FALSE_VALUE;

    Antenna_Gain=FALSE_VALUE;

    pathloss_dB = 0;

    bs2mt_flag = 0;

    PacketSize = 0.0;


}

GAIN_INFO::~GAIN_INFO(){}
