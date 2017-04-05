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
	double cellradius;                  //С��֮�߳�a
	double cell_distance;				//С��֮��ľ���d=a*sqrt(3)��site�ı߳�
	//---------------------------------------------------------------------------------

	pair <double,double> *site_vect;		//�о�����area��2/19��site������

	//pair <double,double> *area_vect;		//����wraparound��areaʸ��,��Freeway�в��ã�����ģ��ʱ������

public:

	BASE_CREATE(SCENARIO_PARA scenario_data);

	~BASE_CREATE(void);

	void Create_base(SCENARIO_PARA scenario_data,vector<BASE_INFO*> &base_list);  //������վ�ĺ���

	void Output_sitevect();                                                    //�����վλ�ú���

};

#endif // BASE_CREATE_H_INCLUDED
