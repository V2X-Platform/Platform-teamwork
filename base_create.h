#ifndef BASE_CREATE_H_INCLUDED
#define BASE_CREATE_H_INCLUDED

#pragma once
#include <utility>
#include <vector>
#include "base_info.h"
#include "scenario_para.h"


class BASE_CREATE
{
public:

	int antnum;

	int area_num;

	int basenum;

	//----------- Parameters for scenarios including UMi,UMa,RMa,SMa-------------------
	double ISD;
	double cellradius;                  //小区之边长a
	double cell_distance;				//小区之间的距离d=a*sqrt(3)，site的边长
	//---------------------------------------------------------------------------------

	pair <double,double> *site_vect;		//研究区域area中2/19个site的向量

	//pair <double,double> *area_vect;		//用于wraparound的area矢量,在Freeway中不用，城市模型时再启用

public:

	BASE_CREATE(SCENARIO_PARA scenario_data);

	~BASE_CREATE(void);

	void Create_base(SCENARIO_PARA scenario_data,vector<BASE_INFO*> &base_list);  //创建基站的函数

	void Output_sitevect();                                                    //输出基站位置函数

};

#endif // BASE_CREATE_H_INCLUDED
