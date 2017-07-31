#include "stdafx.h"
#include "TrafficGenerate.h"
#include "system_para.h"
#include ".\random_traffic.h"
#include ".\packet_info.h"
#include ".\tblock_info.h"
#include "math.h"

TRAFFIC_GENERATE::TRAFFIC_GENERATE()
{
	Alpha = Tf_alpha;

	K = Tf_k;

	M = Tf_m;
}

TRAFFIC_GENERATE::~TRAFFIC_GENERATE()
{
#ifdef DESTRUCT_MODE
	std::ofstream OUT_destruct("result/destruction.txt",ios::out|ios::app);
	OUT_destruct<<"TRAFFIC_GENERATE Destructing...\n";

	cout<<"TRAFFIC_GENERATE Destructing...\n";
#endif

}


void TRAFFIC_GENERATE::Generate_traffic_periodic(list<MT_INFO*> &mt_list,double simul_time)
{
	//cout<<"\n Generate traffic for MT ......"<<endl;

	list<MT_INFO*>::iterator MtPtr;

	double simul_x100=simul_time*100; //平台最小时间单位是0.001秒，所以乘100，如果小数位为0即为100ms的整数倍时间。
	int digitbeforepoint=simul_x100;  //对simul_x100取整数；

	for( MtPtr = mt_list.begin(); MtPtr!= mt_list.end();MtPtr++ )
	{

		if(simul_x100-digitbeforepoint<=0.00001&&simul_x100-digitbeforepoint>=-0.00001)
		{

			(*MtPtr)->Add_block_periodic(block_num_pPacket,simul_time);
		}

		int k = (*MtPtr)->HARQ_number;

		for(int Layer=0;Layer<MT_Max_layernum;Layer++)
		{
			if((*MtPtr)->HARQ_buffer.wait_status[Layer][k]==Idle_ing)
			{
				(*MtPtr)->HARQ_buffer.TB_info[Layer][k] = *( (*MtPtr)->TB_que.begin() );
				(*MtPtr)->TB_que.pop_front();
				(*MtPtr)->block_num--;
			}
		}
	}
}

double TRAFFIC_GENERATE::Generate_timeinterval()
{
	double interval_time = K/pow((double)1.0-pktime_gen(),1.0/Alpha)/1000;

	interval_time = interval_time<M?interval_time:M;

	return interval_time;
}
