#ifndef BASE_INFO_H_INCLUDED
#define BASE_INFO_H_INCLUDED

/*������Ż�վ��Ϣ����*/
#include <list>
#include <utility>
#include <iostream>
#include "scenario_para.h"
#include "system_para.h"
#include "gain_info.h"
#include <vector>

using namespace std;

class BASE_INFO
{
public:
    int antnum;
    int RBnum;
    int base_id;

    double BS_array_broadside;//�������еĴ�ֱ����ǣ���Χ[180,180)
    pair <double,double> *ant_pos;			//the base ants' position
    pair <double,double>  base_pos;			//the base ants' position
    double *Theta;//�����������x������ļнǣ���Χ[180,180)
    vector<GAIN_INFO*> comm_mt_list;



public:
    BASE_INFO(SCENARIO_PARA scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside);
    ~BASE_INFO(void);
};

#endif // BASE_INFO_H_INCLUDED
