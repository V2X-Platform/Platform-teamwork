#pragma once

#include "stdafx.h"
#include "base_info.h"
#include "system_para.h"
#include "extern.h"


BASE_INFO::BASE_INFO(SCENARIO scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside)
{
    antnum = scenario_data.antnumtotal;
	RBnum = sys_RBnum;
	antnum_pBS = scenario_data.antnum_pBS;
	MT_num = scenario_data.MT_num;

    base_id = baseid+MT_num;
    base_pos= scenario_data.base_vect[baseid];

    Theta = new double [antnum_pBS];
    ant_pos = new pair<double,double> [antnum_pBS];

    for(int ant_index = 0; ant_index<antnum_pBS; ant_index++)
	{
		ant_pos[ant_index] = antpos[ant_index];

		Theta[ant_index] = theta[ant_index];

	}

}

BASE_INFO::BASE_INFO(){}

BASE_INFO::~BASE_INFO(void)
{
   delete [] Theta;
   delete [] ant_pos;
}
