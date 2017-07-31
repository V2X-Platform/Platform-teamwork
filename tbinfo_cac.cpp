#include "stdafx.h"
#include "tbinfo_cac.h"
#include "system_para.h"
#include "extern.h"
#include <stdlib.h>

/*-------------------基类构造函数、析构函数-------------------*/

TBINFO_CAC::TBINFO_CAC(SCENARIO scenario_data)
{
	MT_noise_fig=scenario_data.MT_noise_fig;

	noise_power = Thermallevel * RBbandwidth/sys_bindnum * pow((double)10.0,MT_noise_fig/10);//mW

	realsubnum=sys_realsubnum;

	RB_Txpower_BS=scenario_data.BS_Power;

	RB_Txpower_MT=scenario_data.MT_Power;


}

TBINFO_CAC::~TBINFO_CAC(void){}

/*-----------------基类构造函数、析构函数完成-----------------*/

/*------------------派生类构造函数、析构函数------------------*/

MT2MT_TB::MT2MT_TB(SCENARIO scenario_data):TBINFO_CAC(scenario_data)
{

}

MT2MT_TB::~MT2MT_TB(){}



MT2BS_TB::MT2BS_TB(SCENARIO scenario_data):TBINFO_CAC(scenario_data)
{

}

MT2BS_TB::~MT2BS_TB(){}

/*----------------派生类构造函数、析构函数完成----------------*/

/*-----------------两个用户终端之间的TB计算-----------------*/

void MT2MT_TB::Cac_Tbinfo(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)
{
    std::ofstream SUCCESS_RATE("result/SUCCESS_RATE.txt",ios::out|ios::trunc);

    int MT_num=mt_list.size();
    for(int i=0;i<MT_num+2;i++)
    {
        success[i]=0;
    }

	for(int carrier_temp=0;carrier_temp<realsubnum;carrier_temp++)
    {
        vector<GAIN_INFO*>::iterator carrier_ptr;

        for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
        {
            int receive_id=(*mt_ptr)->mt_id;
            int send_id=FALSE_VALUE;
            double total_power=0.0;
            //double min_pl=9999.0;
            //double max_ag=0;
            double max_power=0.0;
            double sinr;
            for(carrier_ptr = carrier[carrier_temp].begin();carrier_ptr!=carrier[carrier_temp].end();carrier_ptr++)
            {

                if((*carrier_ptr)->target_id==receive_id)
                {
                    if((*carrier_ptr)->bs2mt_flag)
                        RB_Txpower=pow(10.0,RB_Txpower_BS*0.1);
                    else
                        RB_Txpower=pow(10.0,RB_Txpower_MT*0.1);

                    if(RB_Txpower*(*carrier_ptr)->Antenna_Gain/(*carrier_ptr)->pathloss>max_power)
                    {
                        //total_power+=RB_Txpower*max_ag/min_pl;
                        total_power+= max_power;
                        //min_pl=(*carrier_ptr)->pathloss;
                        //max_ag=(*carrier_ptr)->Antenna_Gain;
                        max_power = RB_Txpower*(*carrier_ptr)->Antenna_Gain/(*carrier_ptr)->pathloss;
                        send_id = (*carrier_ptr)->send_id;
                    }
                    else
                    {
                        total_power+=RB_Txpower*(*carrier_ptr)->Antenna_Gain/(*carrier_ptr)->pathloss;
                    }
                }
            }
            if(send_id!=FALSE_VALUE)
            {

                if(total_power>0.00000001)
                {
                    //sinr = RB_Txpower*max_ag/min_pl/total_power;
                    sinr = max_power/total_power;
                    if(Cac_Bler(bler_data,sys_RBnum,sinr))
                    {
                       success[send_id]=success[send_id]+1;
                       (*carrier_ptr)->PacketSize = 100.0;
                    }
                }
                else
                    success[send_id]=success[send_id]+1;
            }

        }
    }

   int send_id;
   double success_rate;
   for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
   {

       send_id=(*mt_ptr)->mt_id;
       success_rate=(double)success[send_id]/(*mt_ptr)->comm_mt_list.size();
       SUCCESS_RATE<<success_rate<<"\t"<<send_id<<endl;
   }

    for(int id=300 ;id<302;id++)
   {
       success_rate=(double)success[id]/300;
       SUCCESS_RATE<<success_rate<<"\t"<<id<<endl;
   }
}


bool MT2MT_TB::Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)
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

/*-----------------两个用户终端之间的TB计算完成-----------------*/


/*-----------------基站用户终端之间的TB计算-----------------*/

void MT2BS_TB::Cac_Tbinfo(vector <BASE_INFO*> &base_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)
{
      /*std::ofstream SUCCESS_RATE("result/SUCCESS_RATE1.txt",ios::out|ios::trunc);
      int send_id;
      double success_rate;
      for(auto bs_ptr=base_list.begin();bs_ptr!=base_list.end();bs_ptr++)
   {
       send_id=(*bs_ptr)->base_id;
       success_rate=(double)success[send_id]/(*bs_ptr)->comm_mt_list.size();
       SUCCESS_RATE<<(double)success[send_id]<<"\t"<<send_id<<endl;
   }*/
}
bool MT2BS_TB::Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)
{
   return 0;
}
/*---------------基站用户终端之间的TB计算完成---------------*/
