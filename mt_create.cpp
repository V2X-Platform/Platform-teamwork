#include "stdafx.h"
#include "mt_create.h"
#include "base_create.h"
#include "system_para.h"
#include <utility>
#include <stdlib.h>
#include <fstream>
#include "random.h"
#include <time.h>


MT_CREATE::MT_CREATE(SCENARIO scenario_data)
{
	mt_perline=scenario_data.mt_perline;
	line_nums=scenario_data.line_nums;
	mt_num=mt_perline*line_nums;

	ISD = scenario_data.ISD;
	site_vect = scenario_data.base_vect;

	//for Freeway case
    Freeway_arealength = scenario_data.Freeway_arealength;
    Freeway_areawidth = scenario_data.Freeway_arealength;

	R_max = sqrt(3.0) * ISD / 3; //小区边长A for 3 cells per site

}

MT_CREATE::~MT_CREATE(void){}

void MT_CREATE::Create_newmt(list<MT_INFO*> &mt_list)
{
	cout<<"\n Create MT position ......"<<endl;

    int new_mtnum = mt_num;                                                             //要产生的用户总数

    srand(unsigned(time(NULL)));

	if( new_mtnum>0 )                                                                   //如果要产生新的用户
	{
		for(int id_new=0; id_new<new_mtnum; id_new++)
		{
			MT_INFO* mt_new=new MT_INFO(id_new);

			mt_new->line_id=id_new/mt_perline;                                                                       //用户所在车道

            mt_new->x_sort=rand()%Freeway_arealength-Freeway_arealength/2;                                      //yty
            mt_new->y_sort=mt_new->line_id*4+37;
            mt_new->arrarray_direction=(random_0to1()-0.5)>0.0?0:PI;

			pair<int,int>mt_position= make_pair(mt_new->x_sort,mt_new->y_sort);

			mt_new->mt_position=mt_position;

			mt_list.push_back(mt_new);
		}

		//Output_mtposition(mt_list); //一个输出函数，保证输出

	}

}

void MT_CREATE::Output_mtposition(list<MT_INFO*> &mt_list)                                //输出用户位置函数
{


	list<MT_INFO*> ::iterator mt_ptr;


	std::ofstream OUT_MTPOS("result/mtposition.txt",ios::out|ios::app);


    for(mt_ptr = mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
	{
		//OUT_MTPOS<<(*mt_ptr)->x_sort<<"     "<<(*mt_ptr)->y_sort<<endl;
		OUT_MTPOS<<(*mt_ptr)->x_sort<<endl;

	}

	OUT_MTPOS.close();

}
