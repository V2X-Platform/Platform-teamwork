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

	int mt_num;                                                            //ϵͳ���û���
	int mt_perline;                                                        //ÿ�����û���
	int line_nums;                                                         //��������
	double ISD;                                                            //��վ����
	pair<double,double> *site_vect;                                        //��վ��λ��

	//for Freeway specially
	int  Freeway_arealength;                                             //�����ĳ�
	int  Freeway_areawidth ;                                             //�����Ŀ�


	double R_max;                                                          //���ѽṹС���У�С�������û����õ�����뾶



public:

	MT_CREATE(pair<double,double> sitevect[]);

	~MT_CREATE(void);

	void Create_newmt(list<MT_INFO*> &mt_list);

private:

	void Output_mtposition(list<MT_INFO*> &mt_list);
};

#endif // MT_CREATE_H_INCLUDED
