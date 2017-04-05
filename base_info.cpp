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
	//linkmt_num = 0;
	//linkmt_list.clear();

    //LoS_mtlist.clear();
	//NLoS_mtlist.clear();

	//ANT_list = new ANT_INFO* [antnum];                    //可以用list替代吗？
	//base_resource = new RUNIT_INFO* [RBnum];              //存放基站资源信息

    //for(int RB_index = 0; RB_index<RBnum; RB_index++)     //RUNIT_INFO这个类还有没有存在的必要不一定；
	{
		//base_resource[RB_index] = new RUNIT_INFO(RB_index);
	}
}

BASE_INFO::~BASE_INFO(void)
{
    /*删除分配资源信息*/
    //RUNIT_INFO* temp_ptr(NULL);
	/*for(int RB_index = 0; RB_index<sys_RBnum; RB_index++)
	{
		temp_ptr = base_resource[RB_index];
		delete temp_ptr;
		temp_ptr = NULL;
	}
	delete [] base_resource;

	/*删除天线列表信息*/
    /*for(int ant_index = 0; ant_index<bp_antnum; ant_index++)
	{
		delete (ANT_list[ant_index]);
	}

	delete [] ANT_list;*/

}
