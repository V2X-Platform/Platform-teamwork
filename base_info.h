#ifndef BASE_INFO_H_INCLUDED
#define BASE_INFO_H_INCLUDED

/*用来存放基站信息的类*/
#include <list>
#include <utility>
#include <iostream>
#include "scenario_para.h"
#include "system_para.h"

using namespace std;

class BASE_INFO
{
public:
    int antnum;
    int RBnum;
    int base_id;

    //list < MT_INFO*>  linkmt_list;           //链接的用户列表
    //list < MT_INFO*>  LoS_mtlist;             //视距用户列表
	//list < MT_INFO*>  NLoS_mtlist;            //非视距用户列表

	//ANT_INFO** ANT_list;                      //天线裂变
	//RUNIT_INFO** base_resource;               //基站资源

    double BS_array_broadside;//天线阵列的垂直方向角，范围[180,180)
    pair <double,double> *ant_pos;			//the base ants' position
    double *Theta;//扇区天线相对x正半轴的夹角，范围[180,180)



public:
    BASE_INFO(SCENARIO_PARA scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside);
    ~BASE_INFO(void);
};

#endif // BASE_INFO_H_INCLUDED
