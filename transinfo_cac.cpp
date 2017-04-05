#include "stdafx.h"
#include "transinfo_cac.h"
#include "system_para.h"
#include "extern.h"
#include <stdlib.h>



TRANSINFO_CAC::TRANSINFO_CAC(int x)
{
	noise_power = Thermallevel * RBbandwidth/sys_bindnum * pow((double)10.0,MT_noise_fig/10);//mW

	BS_Power = BS_Power;//基站总功率mW

	RB_Txpower = BS_Power/sys_RBnum/sys_bindnum;// 每个RB的发送功率：基站总功率 / RB数量 / 每个基站的天线数 （注意20MHz～21dBm发送功率～100个RB）

	realsubnum=sys_realsubnum;

}

TRANSINFO_CAC::~TRANSINFO_CAC(void){}


void TRANSINFO_CAC::Cac_Transinfo_STEP1A(list<MT_INFO*> &mt_list,unordered_map<int,unordered_set<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)
{
	for(int carrier_temp=0;carrier_temp<realsubnum;carrier_temp++)
    {
        unordered_set<GAIN_INFO*>::iterator carrier_ptr=carrier[carrier_temp].begin();
        for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
        {
            int receive_id=(*mt_ptr)->mt_id;
            int send_id=FALSE_VALUE;
            double total_power=0.0;
            double min_pl=0;
            double sinr;
            for(;carrier_ptr!=carrier[carrier_temp].end();carrier_ptr++)
            {

                if((*carrier_ptr)->target_id==receive_id)
                {
                    if((*carrier_ptr)->pathloss<min_pl)
                    {
                        total_power=RB_Txpower/min_pl;
                        min_pl=(*carrier_ptr)->pathloss;
                        send_id=(*carrier_ptr)->send_id;
                    }
                    else

                        total_power+=RB_Txpower/(*carrier_ptr)->pathloss;
                }

            }

            if(send_id!=FALSE_VALUE)
            {
                if(total_power>0.00000001)
                {
                    sinr=RB_Txpower/min_pl/total_power;
                    if(TRANSINFO_CAC::Cac_Bler(bler_data,sys_RBnum,sinr))
                    {
                       success[send_id]++;
                    }
                }
                else
                    success[send_id]++;
            }

        }
    }

   // for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)

}
bool TRANSINFO_CAC::Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)
{

		double	quality = bler_data.Read_BLER(sinr,1,RB_S);//函数第二个数为MCS[layer]，先假定为1；

		double temp_quality = rand()/(RAND_MAX+1.0);

		if(temp_quality>quality)
		{
            return 1;
		}
		else
            return 0;
}
