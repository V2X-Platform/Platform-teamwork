#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED


/*此头文件是用来记录一些仿真数据，目前大概是起到一个全局变量的作用*/
#pragma once

#include "base_info.h"
#include "mt_info.h"
#include "scenario_para.h"
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include "extern.h"


class SIMULATION
{
public:

	int mt_num;						 // active mt number

	int mt_perline;                  // 每个道路的用户数；
	int line_nums;                   // 道路总数

	int mt_newnum;					 // the new generate MT number

	int basenum;                     //基站数目
	int antnum;                      //天线数目
	double BW;                       //天线带宽


    vector<BASE_INFO*> base_list;                            //基站列表
    list <MT_INFO*> mt_list;                                 //用户列表
    unordered_map<int,vector<GAIN_INFO*>>  carrier;          //业务列表

    SIMULATION(SCENARIO_PARA &scenario_data);
	~SIMULATION();
};

#endif // SIMULATION_H_INCLUDED
