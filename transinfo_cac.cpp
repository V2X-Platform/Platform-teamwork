#include "stdafx.h"
#include "transinfo_cac.h"
#include "system_para.h"
#include "extern.h"
#include <stdlib.h>



TRANSINFO_CAC::TRANSINFO_CAC(int x)
{
	noise_power = Thermallevel * RBbandwidth/sys_bindnum * pow((double)10.0,MT_noise_fig/10);//mW

	BS_Power = sys_BS_Power;//��վ�ܹ���mW

	MT_Power = sys_MT_Power;//�û��ܹ���

	RB_Txpower = MT_Power/sys_RBnum/sys_bindnum;// ÿ��RB�ķ��͹��ʣ���վ�ܹ��� / RB���� / ÿ����վ�������� ��ע��20MHz��21dBm���͹��ʡ�100��RB��

	realsubnum=sys_realsubnum;

}

TRANSINFO_CAC::~TRANSINFO_CAC(void){}


void TRANSINFO_CAC::Cac_Transinfo_STEP1A(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>> &carrier,BLER_CURVE &bler_data)
{
	std::ofstream SUCCESS_RATE("result/SUCCESS_RATE.txt",ios::out|ios::trunc);
	std::ofstream test2("result/test2.txt",ios::out|ios::trunc);
	std::ofstream test3("result/test3.txt",ios::out|ios::trunc);

    for(int i=0;i<MT_num;i++)
    {
        success[i]=0;
    }

	for(int carrier_temp=0;carrier_temp<realsubnum;carrier_temp++)
    {
        vector<GAIN_INFO*>::iterator carrier_ptr;
        int nums=0;
        int nums1=0;
        for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
        {
            int receive_id=(*mt_ptr)->mt_id;
            int send_id=FALSE_VALUE;
            double total_power=0.0;
            double min_pl=9999.0;
            double sinr;
            for(carrier_ptr=carrier[carrier_temp].begin();carrier_ptr!=carrier[carrier_temp].end();carrier_ptr++)
            {

                if((*carrier_ptr)->target_id==receive_id)
                {
                    if((*carrier_ptr)->coupling_loss<min_pl)
                    {
                        total_power=RB_Txpower/min_pl;
                        min_pl=(*carrier_ptr)->coupling_loss;
                        send_id=(*carrier_ptr)->send_id;
                    }
                    else
                        total_power+=RB_Txpower/(*carrier_ptr)->coupling_loss;
                }
            }

            /*if(send_id!=FALSE_VALUE)

            {
                test2<<send_id<<"\t"<<nums++<<endl;
                //test3<<total_power<<endl;
            }*/

            if(send_id!=FALSE_VALUE)
            {
                if(total_power>0.00000001)
                {
                    sinr=RB_Txpower/min_pl/total_power;
                    //test3<<sinr<<endl;
                    if(Cac_Bler(bler_data,sys_RBnum,sinr))
                    {
                       success[send_id]=success[send_id]+1;
                       test3<<send_id<<"\t"<<success[send_id]<<"\t"<<nums1++<<endl;
                    }
                }
                else
                    {
                        success[send_id]=success[send_id]+1;
                        test3<<send_id<<"\t"<<success[send_id]<<"\t"<<nums1++<<endl;
                    }
            }
        }
    }

   int send_id;
   double success_rate;
   for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
   {

       send_id=(*mt_ptr)->mt_id;
       success_rate=(double)success[send_id]/(*mt_ptr)->comm_mt_list.size();
       SUCCESS_RATE<<success_rate<<endl;
   }

}
bool TRANSINFO_CAC::Cac_Bler(BLER_CURVE &bler_data,int RB_S,double sinr)
{

		double	quality = bler_data.Read_BLER(sinr,1,RB_S);//�����ڶ�����ΪMCS[layer]���ȼٶ�Ϊ1��

		double temp_quality = rand()/(RAND_MAX+1.0);

		if(temp_quality>quality)
		{
            return 1;
		}
		else
            return 0;
}
