//#pragma once
#include <iostream>
#include <stdlib.h>
#include <list>
#include "scenario_para.h"
#include "simulation.h"
#include "base_create.h"
#include "mt_create.h"
#include "mt2mtgain_cac.h"
#include "global_para.h"
#include "transinfo_cac.h"

using namespace std;

int main()
{
    unsigned uSeed = 453676;                                                   //这是一个种子，用来/*(unsigned)time( NULL )*/
	srand(uSeed);                                                              //设置一个随机数
	int SubFrame_index ;


    //***************相关类声明部分***************//
    SCENARIO_PARA scenario_data(20170330);
    SIMULATION ss(scenario_data);
    BASE_CREATE create_base(scenario_data);
    MT_CREATE create_mt(create_base.site_vect);
    MT2MTGAIN_CAC mt2tgain_cac(20170330);
    TRANSINFO_CAC cac_transinfo(20170331);
    BLER_CURVE bler_data(15);
    //***************相关类声明部分***************//



    create_base.Create_base(scenario_data,ss.base_list);                       //创建基站
    create_base.Output_sitevect();                                             //输出基站位置

    create_mt.Create_newmt(ss.mt_list);                                        //创建用户
    mt2tgain_cac.Cac_pathloss(ss.mt_list);                                     //计算用户间路径损耗

    for(SubFrame_index=0;SubFrame_index<SubFrame_num;SubFrame_index++)
    {
        simul_time = SubFrame_index*sys_subframe_time;
        mt2tgain_cac.store_gain(ss.mt_list,ss.carrier);
        cac_transinfo.Cac_Transinfo_STEP1A(ss.mt_list,ss.carrier,bler_data);
    }











    return 0;
}
