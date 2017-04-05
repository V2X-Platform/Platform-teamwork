#include "stdafx.h"
#include "mt2mtgain_cac.h"
#include "system_para.h"
#include "gain_info.h"
#include <utility>
#include <fstream>
#include <stdlib.h>
#include "extern.h"

MT2MTGAIN_CAC::MT2MTGAIN_CAC(int x)
{
	CF = sys_frequency;//Hz

	H_MT = sys_H_MT;

	D_BP  = 4*(H_MT-1.0)*(H_MT-1.0)*CF/c_velocity;
}

MT2MTGAIN_CAC::~MT2MTGAIN_CAC(void){}

void  MT2MTGAIN_CAC::Cac_pathloss(list<MT_INFO*> &mt_list)                     //计算路径损耗的函数
{
    int mt_posx,mt_posy,mt_posx2,mt_posy2,mt_id,mt_id2;

	double mt2mt_dist;

	double mt2mt_dist_horizon,mt2mt_dist_vertical,dist_loss;	//增加计算LOS概率变量

	int LoS_flag;

	std::ofstream OUT_Cl_Info("result/coupling_loss.txt",ios::out|ios::trunc);

	GAIN_INFO *pgain = NULL;
	GAIN_INFO *pgain2 = NULL;

	list<MT_INFO*>::iterator mt_ptr;
	list<MT_INFO*>::iterator mt_ptr2;




	for(mt_ptr = mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
	{
		mt_posx=(*mt_ptr)->x_sort;
		mt_posy=(*mt_ptr)->y_sort;
		mt_id=(*mt_ptr)->mt_id;

		mt_ptr2=mt_ptr;

        for(mt_ptr2++;mt_ptr2!=mt_list.end();mt_ptr2++)
        {

            mt_posx2=(*mt_ptr2)->x_sort;
            mt_posy2=(*mt_ptr2)->y_sort;
            mt_id2=(*mt_ptr2)->mt_id;

            mt2mt_dist=(mt_posx-mt_posx2);

            mt2mt_dist_horizon = abs(mt_posx-mt_posx2);//水平距离

            mt2mt_dist_vertical = abs(mt_posy-mt_posy2);//空间距离

            mt2mt_dist=sqrt(pow(mt2mt_dist_horizon,2)+pow(mt2mt_dist_vertical,2)); //两个用户距离

            if(mt2mt_dist<=320.0)

            {//LoS_flag = Decide_LoSflag(mt2mt_dist);//此链路为LoS的概率,对UMi为室外部分的LoS的概率

                LoS_flag =0;

                //Set_LoSflag(base_list[base_index],*mt_ptr,LoS_flag,mt_Indoor); 这行还有用，不过暂时不知道怎么利用

                dist_loss = Cac_distloss(LoS_flag,mt2mt_dist);

                GAIN_INFO*temp1=new GAIN_INFO(mt_id,mt_id2);
                GAIN_INFO*temp2=new GAIN_INFO(mt_id2,mt_id);

                pgain = temp1;
                pgain2 = temp2;

                (*mt_ptr)->comm_mt.insert(temp1);
                (*mt_ptr2)->comm_mt.insert(temp2);

                pgain->LOS_flag = LoS_flag;
                pgain2->LOS_flag = LoS_flag;

                pgain->pathloss_dB = dist_loss;
                pgain2->pathloss_dB = dist_loss;

                pgain->coupling_loss=pgain->pathloss_dB-3;
                pgain->coupling_loss=pgain->pathloss_dB-3;


                pgain->pathloss = pow((double)10.0,(pgain->pathloss_dB/10.0));
                pgain2->pathloss = pow((double)10.0,(pgain->pathloss_dB/10.0));

                delete temp1;
                delete temp2;

                OUT_Cl_Info<<pgain->coupling_loss<<"\n";
            }

        }

	}
}
double MT2MTGAIN_CAC::Cac_distloss(bool LoSflag,double mt2mt_dist)
{
    double dist_loss=0;
	double dist_loss_freespace=0;
	double dist_loss_Outside;

	if(LoSflag==LoS)
	{
		if((mt2mt_dist>10.0)&&(mt2mt_dist<320))                        //UMi 场景LOS两个公式的判断要用水平距离
			dist_loss_Outside = 22.7*log10(mt2mt_dist)+41.0+20.0*log10(CF/1.0e9);//第一个公式用空间距离,原来B=27

		else
			dist_loss_Outside = 40.0*log10(mt2mt_dist) - 17.3*log10(0.8) -17.3*log10(0.8)  +9.45;
	}
	else
    {
        dist_loss_Outside = (44.9-6.55*log10(H_MT))*log10(mt2mt_dist) + 14.78 + 34.97*log10(CF/1.0e9)+5.83*log10(H_MT)-5;
    }

    dist_loss = dist_loss_Outside;

	dist_loss_freespace=20*log10(mt2mt_dist)+46.4+20*log10((CF/1.0e9)/5);
	dist_loss=(dist_loss_freespace>dist_loss_Outside?dist_loss_freespace:dist_loss_Outside);

	return dist_loss;
}

void MT2MTGAIN_CAC::store_gain(list<MT_INFO*> &mt_list,unordered_map<int,unordered_set<GAIN_INFO*>>&carrier)
{
    list<MT_INFO*>::iterator mt_ptr;

    int carrier_temp;

    for(mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
    {

        for(auto mt_tocomm=(*mt_ptr)->comm_mt.begin();mt_tocomm!=(*mt_ptr)->comm_mt.end();mt_tocomm++)
        {
            carrier_temp=rand()%sys_realsubnum;
            carrier[carrier_temp].insert(*mt_tocomm);
        }
    }
}

