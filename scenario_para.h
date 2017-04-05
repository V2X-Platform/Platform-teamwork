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
	int    MT_num;                  // ���û�����
	//int  area_num;                // area ����

	int    mt_perline;              //ÿ����·�ϵ��û�����
	int    line_nums;               //��·����

	//for Freeway case
	double Freeway_arealength;      //����·�ĳ�
	double Freeway_areawidth ;      //����·�Ŀ�

	// BS & MT parameter
	double ISD;                     // inter-site distance
	double BS_Power;                // Base power mW
	double BS_antgain;              //dBi
	double MT_antgain;              //dBi
	double Min_dist;
	double H_BS ;                   //��վ���߸߶�
	double H_MT;                    //�û����߸߶�

	//------------------------------------------------------------------------------------
public:
	SCENARIO_PARA(int data);            //���캯����
	~SCENARIO_PARA(void){}          //����������
};

#endif // SCENARIO_H_INCLUDED
