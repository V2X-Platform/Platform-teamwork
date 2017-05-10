#include "stdafx.h"
#include "simulation.h"
#include "system_para.h"

extern int loop_index;

/*构造函数*/
SIMULATION::SIMULATION(SCENARIO scenario_data)
{
    mt_perline=scenario_data.mt_perline;                                    // 每个车道用户数
    line_nums=scenario_data.line_nums;
    mt_num = 0;
    mt_newnum = 0;

	basenum =scenario_data.basenum;
	BW = scenario_data.BW;

    //---------------------资源分配粒度------------------------
    /*此段代码主要作用是根据RB数目的多少决定多少个RB组成一个RB组，组成一个RB组的作用是什么暂时还不太清楚，v2x情况下可能都不需要，v2c下可能需要，所以暂时保留*/
	int RBG_size = 0;
	if (ResAllocateType==0)
	{
		if(sys_RBnum<=10)
			RBG_size = 1;
		else if(sys_RBnum>=11 && sys_RBnum<=26)
			RBG_size = 2;
		else if(sys_RBnum>=27 && sys_RBnum<=63)
			RBG_size = 3;
		else //sys_RBnum>=64
			RBG_size = 4;
	}
	else
	{
		RBG_size = 1;
	}

	sys_RBG_num = int(ceil(double(sys_RBnum)/RBG_size));

	sys_RBG_size = new int[sys_RBG_num];

	for(int i=0;i<sys_RBG_num;i++)
	{
		sys_RBG_size[i] = RBG_size;
		if(i==sys_RBG_num-1)//最后一个RBG
		{
			sys_RBG_size[i] = sys_RBnum - (sys_RBG_num-1)*RBG_size;
		}
	}
	//---------------------------------------------------------
}
SIMULATION::SIMULATION(const SIMULATION&_A)
{

    mt_perline=_A.mt_perline;                                    // 每个车道用户数
    line_nums=_A.line_nums;
    mt_num = 0;
    mt_newnum = 0;

	basenum =_A.basenum;
	BW = _A.BW;

    //---------------------资源分配粒度------------------------
    /*此段代码主要作用是根据RB数目的多少决定多少个RB组成一个RB组，组成一个RB组的作用是什么暂时还不太清楚，v2x情况下可能都不需要，v2c下可能需要，所以暂时保留*/
	int RBG_size = 0;
	if (ResAllocateType==0)
	{
		if(sys_RBnum<=10)
			RBG_size = 1;
		else if(sys_RBnum>=11 && sys_RBnum<=26)
			RBG_size = 2;
		else if(sys_RBnum>=27 && sys_RBnum<=63)
			RBG_size = 3;
		else //sys_RBnum>=64
			RBG_size = 4;
	}
	else
	{
		RBG_size = 1;
	}

	sys_RBG_num = int(ceil(double(sys_RBnum)/RBG_size));

	sys_RBG_size = new int[sys_RBG_num];

	for(int i=0;i<sys_RBG_num;i++)
	{
		sys_RBG_size[i] = RBG_size;
		if(i==sys_RBG_num-1)//最后一个RBG
		{
			sys_RBG_size[i] = sys_RBnum - (sys_RBG_num-1)*RBG_size;
		}
	}
	//---------------------------------------------------------
}


/*析构函数*/
SIMULATION::~SIMULATION()
{
	vector<BASE_INFO*>::iterator base_it;
	list<MT_INFO*>::iterator mt_it;

	for(base_it = base_list.begin(); base_it != base_list.end(); base_it++)
	{
		delete (*base_it);
	}

	for(mt_it = mt_list.begin(); mt_it != mt_list.end(); mt_it++)
	{
		if ((*mt_it) != NULL)
		{
			delete (*mt_it);
		}
	}

	delete [] sys_RBG_size;
	sys_RBG_size = NULL;
}
