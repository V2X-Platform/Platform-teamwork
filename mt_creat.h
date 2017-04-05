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

	int MT_num;//ϵͳ���û���
	int mt_perline; //ÿ�����û���

	//-------------------------------------------------------
	double ISD;

	pair <double,double> *site_vect;

	//------------------------------------------------------/*/

	//for Freeway case
	double Freeway_arealength;
	double Freeway_areawidth ;

	double R_max;   //���ѽṹС���У�С�������û����õ�����뾶

	double Min_dist;//MT ����������֮�����С����

public:

	MT_CREATE(SCENARIO_PARA scenario_data,complex<double> sitevect[],complex<double> areavect[]);

	~MT_CREATE(void);

	void Create_newmt_YTY(SCENARIO_PARA scenario_data,list<MT_INFO*> &mt_list, MT_INFO* mt_trace, int &mt_num,int &new_mtnum,int &mt_topnum,int mt_traceid,int simul_step,int loop_index,int mt_perline,int nums_line);

private:

	void MT_Redrop(list<MT_INFO*> &mt_list);//added 20091226 �����û�λ�ü�Indoor��Ϣ�����������Ϣ

	complex<double>  Uniform_position(int scenario);

	complex<double>  Uniform_position_YTY(int line);//����·���û�������

	void Output_mtposition(list<MT_INFO*> &mt_list);
};


#endif // MT_CREAT_H_INCLUDED
