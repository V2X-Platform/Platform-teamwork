#pragma once

#include "stdafx.h"
#include "base_info.h"
#include "system_para.h"
#include "extern.h"


BASE_INFO::BASE_INFO(SCENARIO_PARA scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside)
{
    antnum = scenario_data.antnum;
	RBnum = sys_RBnum;

    base_id = baseid;
    base_pos=sys_base_vect[baseid];


}

BASE_INFO::~BASE_INFO(void)
{


}
