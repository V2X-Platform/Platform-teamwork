#ifndef BASE_INFO_H_INCLUDED
#define BASE_INFO_H_INCLUDED

/*用来存放基站信息的类*/
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

    double BS_array_broadside;//天线阵列的垂直方向角，范围[180,180)
    pair <double,double> *ant_pos;			//the base ants' position
    pair <double,double>  base_pos;			//the base ants' position
    double *Theta;//扇区天线相对x正半轴的夹角，范围[180,180)
    vector<GAIN_INFO*> comm_mt_list;



public:
    BASE_INFO(SCENARIO_PARA scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside);
    ~BASE_INFO(void);
};

#endif // BASE_INFO_H_INCLUDED
