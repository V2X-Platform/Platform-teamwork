//#pragma once
#include <iostream>
#include <stdlib.h>
#include <list>
#include "scenario_para.h"
#include "simulation.h"
#include "base_create.h"
#include "mt_create.h"
#include "gain_cac.h"
#include "global_para.h"
#include "tbinfo_cac.h"
#include "display.h"
#include "random.h"

using namespace std;

int main()
{
    Config();

    //unsigned uSeed = 453676;                                                   //这是一个种子，用来/*(unsigned)time( NULL )*/
	//srand(uSeed);                                                              //设置一个随机数
	//int SubFrame_index ;


    //***************相关类声明部分***************//
    SCENARIO_PARA *scenario_curr=new SCENARIO_FREEWAY(20170330);
    SCENARIO scenario_data(scenario_curr);
    SIMULATION ss(scenario_data);
    BASE_CREATE create_base(scenario_data);
    MT_CREATE create_mt(scenario_data);
    MT2MTGAIN_CAC mt2mtgain_cac(scenario_data);
    MT2BSGAIN_CAC mt2bsgain_cac(scenario_data);
    MT2MT_TB mt2mttb_cac(scenario_data);
    MT2BS_TB mt2bstb_cac(scenario_data);
    BLER_CURVE bler_data(15);
    //***************相关类声明部分***************//


    create_base.Create_base(scenario_data,ss.base_list);                       //创建基站
    create_base.Output_sitevect();                                             //输出基站位置

    create_mt.Create_newmt(ss.mt_list);                                        //创建用户

    //for(SubFrame_index=0;SubFrame_index<SubFrame_num;SubFrame_index++)
    {
        //此处还需要一个对车辆位置进行更新的函数；
        mt2mtgain_cac.Cac_pathloss(ss.base_list,ss.mt_list);                                            //计算用户间路径损耗
        mt2bsgain_cac.Cac_pathloss(ss.base_list,ss.mt_list);                                            //计算基站用户间路径损耗
        //simul_time = SubFrame_index*sys_subframe_time;
        mt2mtgain_cac.store_gain(ss.mt_list,ss.carrier);
        mt2bsgain_cac.store_gain(ss.mt_list,ss.base_list,ss.carrier);
        mt2mttb_cac.Cac_Tbinfo(ss.mt_list,ss.carrier,bler_data);
        mt2bstb_cac.Cac_Tbinfo(ss.base_list,ss.carrier,bler_data);


    }


    return 0;
}
