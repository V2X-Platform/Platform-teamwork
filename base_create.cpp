#include "stdafx.h"
#include "system_para.h"
#include "base_create.h"
#include "random.h"
#include <iostream>
#include <fstream>


/*构造函数*/
BASE_CREATE::BASE_CREATE(SCENARIO_PARA scenario_data)
{
	antnum = scenario_data.antnum;
	basenum = scenario_data.basenum;
    //area_num = scenario_data.area_num;                            //城市模型中再启用

	ISD = scenario_data.ISD;

	//area_vect = new complex<double>[area_num];                    //城市模型中再启用
	site_vect = new pair<double,double>[basenum];

}

/*析构函数*/
BASE_CREATE::~BASE_CREATE(void)
{
	if (NULL != site_vect)
	{
		delete []site_vect;
		site_vect = NULL;
	}
}

/*建立基站的函数*/

void BASE_CREATE::Create_base(SCENARIO_PARA scenario_data,vector<BASE_INFO*> &base_list)
{
	//cout<<"\n Create Base station and Ant position ...... "<<endl;

	pair<double,double> *ant_pos = new pair<double,double> [antnum];
	double *theta=new double[antnum];
	double array_broadside;

	for(int base_id =0;base_id<basenum;base_id++)
	{
		for(int k=0;k<antnum;k++)
		{
			ant_pos[k] = site_vect[base_id];
            theta[k] = 0;
		}

		array_broadside = random_0to1()*2*PI - PI;

		BASE_INFO *pBASE_INFO = new BASE_INFO(scenario_data,base_id,ant_pos,theta,array_broadside);

		if (pBASE_INFO != NULL)
		{
			base_list.push_back(pBASE_INFO);
		}

	}

	delete [] ant_pos;
	delete [] theta;

}

void BASE_CREATE::Output_sitevect()
{
	std::ofstream OUT_SITE("result/simula_sitevect.txt",ios::out|ios::trunc);

	OUT_SITE<<"site_vect = [ "<<endl;

	for(int i=0;i<basenum; i++)
	{
		OUT_SITE<<site_vect[i].first;

		if(site_vect[i].second>=0)
		{
			OUT_SITE<<"+";
		}
		OUT_SITE<<site_vect[i].second<<"i"<<endl;
	}

	OUT_SITE<<"];"<<endl;

	OUT_SITE.close();

}
