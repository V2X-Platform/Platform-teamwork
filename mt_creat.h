#ifndef MT_CREAT_H_INCLUDED
#define MT_CREAT_H_INCLUDED

#pragma once

#include "base_create.h"
#include "MT_INFO.h"
#include "scenario_para.h"
#include <utility>

class MT_CREATE
{
public:

	int scenario;
	int  bp_basenum,area_num;

	int MT_num;//系统总用户数
	int mt_perline; //每车道用户数

	//-------------------------------------------------------
	double ISD;

	pair <double,double> *site_vect;

	//------------------------------------------------------/*/

	//for Freeway case
	double Freeway_arealength;
	double Freeway_areawidth ;

	double R_max;   //蜂窝结构小区中，小区内撒用户所用的区域半径

	double Min_dist;//MT 与连接天线之间的最小距离

public:

	MT_CREATE(SCENARIO_PARA scenario_data,complex<double> sitevect[],complex<double> areavect[]);

	~MT_CREATE(void);

	void Create_newmt_YTY(SCENARIO_PARA scenario_data,list<MT_INFO*> &mt_list, MT_INFO* mt_trace, int &mt_num,int &new_mtnum,int &mt_topnum,int mt_traceid,int simul_step,int loop_index,int mt_perline,int nums_line);

private:

	void MT_Redrop(list<MT_INFO*> &mt_list);//added 20091226 重撒用户位置及Indoor信息，清除其他信息

	complex<double>  Uniform_position(int scenario);

	complex<double>  Uniform_position_YTY(int line);//按道路撒用户呜呜呜

	void Output_mtposition(list<MT_INFO*> &mt_list);
};


#endif // MT_CREAT_H_INCLUDED
