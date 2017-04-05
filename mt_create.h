#ifndef MT_CREATE_H_INCLUDED
#define MT_CREATE_H_INCLUDED

#pragma once

#include "base_create.h"
#include "MT_INFO.h"
#include "scenario_para.h"
#include <utility>

class MT_CREATE
{
public:

	int mt_num;                                                            //系统总用户数
	int mt_perline;                                                        //每车道用户数
	int line_nums;                                                         //车道数量
	double ISD;                                                            //基站间间距
	pair<double,double> *site_vect;                                        //基站的位置

	//for Freeway specially
	int  Freeway_arealength;                                             //场景的长
	int  Freeway_areawidth ;                                             //场景的宽


	double R_max;                                                          //蜂窝结构小区中，小区内撒用户所用的区域半径



public:

	MT_CREATE(pair<double,double> sitevect[]);

	~MT_CREATE(void);

	void Create_newmt(list<MT_INFO*> &mt_list);

private:

	void Output_mtposition(list<MT_INFO*> &mt_list);
};

#endif // MT_CREATE_H_INCLUDED
