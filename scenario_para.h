#ifndef SCENARIO_PARA_H_INCLUDED
#define SCENARIO_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include "system_para.h"

class SCENARIO_PARA
{
public:
   	//int sys_scenario;

	//---------------------- System Configuration Parameters ------------------------
	// see M.2135 Table 8-2,4,5
	// System parameter
	double CF;	                    // System main Carrier frequency in Hz
	double BW;                      // FDD system bandwidth

	int    sectnum_pBS;
	int    antnum;         		    // Base Station distributed antenna Number
	int    basenum;			        // Base station number
	int    antnumtotal;
	int    MT_num;                  // 总用户数量
	//int  area_num;                // area 数量

	int    mt_perline;              //每个道路上的用户数量
	int    line_nums;               //道路数量

	//for Freeway case
	double Freeway_arealength;      //高速路的长
	double Freeway_areawidth ;      //高速路的宽

	// BS & MT parameter
	double ISD;                     // inter-site distance
	double BS_Power;                // Base power mW
	double BS_antgain;              //dBi
	double MT_antgain;              //dBi
	double Min_dist;
	double H_BS ;                   //基站天线高度
	double H_MT;                    //用户天线高度

	//------------------------------------------------------------------------------------
public:
	SCENARIO_PARA(int data);            //构造函数；
	~SCENARIO_PARA(void){}          //析构函数；
};

#endif // SCENARIO_H_INCLUDED
