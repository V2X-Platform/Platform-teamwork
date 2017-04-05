#include "stdafx.h"
#include "transinfo_cac.h"
#include "system_para.h"
#include "extern.h"



TRANSINFO_CAC::TRANSINFO_CAC(int x)
{
	noise_power = Thermallevel * RBbandwidth/sys_bindnum * pow((double)10.0,MT_noise_fig/10);//mW

	BS_Power = BS_Power;//��վ�ܹ���mW

	RB_Txpower = BS_Power/sys_RBnum/sys_bindnum;// ÿ��RB�ķ��͹��ʣ���վ�ܹ��� / RB���� / ÿ����վ�������� ��ע��20MHz��21dBm���͹��ʡ�100��RB��

	realsubnum=sys_realsubnum;

}

TRANSINFO_CAC::~TRANSINFO_CAC(void){}


void TRANSINFO_CAC::Cac_Transinfo_STEP1A(list<MT_INFO*> &mt_list,unordered_map<int,unordered_set<GAIN_INFO*>> &carrier)
{
	for(int carrier_temp=0;carrier_temp<realsubnum;carrier_temp++)
    {
        unordered_set<GAIN_INFO*>::iterator carrier_ptr=carrier[carrier_temp].begin();
        for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
        {
            int receive_id=(*mt_ptr)->mt_id;
            int send_id=FALSE_VALUE;
            double total_power=0;
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
                if(total_power!=0)
                {
                    sinr=RB_Txpower/min_pl/total_power;
                    //�ж����
                }
                else
                    success[send_id]++;
            }

        }
    }

   // for(auto mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)

}
void TRANSINFO_CAC::Cac_Bler(BLER_CURVE &bler_data,int RB_S)
{
	boost::hellekalek1995 generator_quality(rand());
	boost::uniform_01<boost::hellekalek1995> real_quliaty(generator_quality);

	for(int layer=0;layer<link_layer;layer++)
	{

		double	quality = bler_data.Read_BLER(sinr,MCS[layer],RB_S);

		double temp_quality = real_quliaty();

		if(temp_quality>quality)
		{

		}
		else


	}

}
