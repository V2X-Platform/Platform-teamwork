#include "stdafx.h"
#include "gain_cac.h"
#include "system_para.h"
#include "gain_info.h"
#include <utility>
#include <fstream>
#include <stdlib.h>
#include "extern.h"

/*-------------------基类构造函数、析构函数-------------------*/
GAIN_CAC::GAIN_CAC(int x)
{
	CF = sys_frequency;//Hz

	H_MT = sys_H_MT;

}

GAIN_CAC::~GAIN_CAC(void){}

/*-----------------基类构造函数、析构函数完成-----------------*/

/*------------------派生类构造函数、析构函数------------------*/

MT2MTGAIN_CAC::MT2MTGAIN_CAC(int x):GAIN_CAC(1)
{
	D_BP  = 4*(H_MT-1.0)*(H_MT-1.0)*CF/c_velocity;
}

MT2MTGAIN_CAC::~MT2MTGAIN_CAC(void){}

MT2BSGAIN_CAC::MT2BSGAIN_CAC(int x):GAIN_CAC(1)
{
	H_BS=sys_H_BS;
	D_BP  = 4*(H_BS-1.0)*(H_MT-1.0)*CF/c_velocity;
}

MT2BSGAIN_CAC::~MT2BSGAIN_CAC(void){}

/*----------------派生类构造函数、析构函数完成----------------*/


/*---------------两个用户终端之间的路径损耗计算---------------*/

void  MT2MTGAIN_CAC::Cac_pathloss(list<MT_INFO*> &mt_list)
{
    int mt_posx,mt_posy,mt_posx2,mt_posy2,mt_id,mt_id2;

	double mt2mt_dist;

	double mt2mt_dist_horizon,mt2mt_dist_vertical,dist_loss;	//增加计算LOS概率变量

	int LoS_flag;

	//std::ofstream OUT_Cl_Info("result/coupling_loss.txt",ios::out|ios::trunc);

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

            {
                //LoS_flag = Decide_LoSflag(mt2mt_dist);//此链路为LoS的概率,对UMi为室外部分的LoS的概率

                LoS_flag =0;

                //Set_LoSflag(base_list[base_index],*mt_ptr,LoS_flag,mt_Indoor); 这行还有用，不过暂时不知道怎么利用

                dist_loss = Cac_distloss(LoS_flag,mt2mt_dist);

                GAIN_INFO*temp1=new GAIN_INFO(mt_id,mt_id2);
                GAIN_INFO*temp2=new GAIN_INFO(mt_id2,mt_id);

                temp1->LOS_flag = LoS_flag;
                temp2->LOS_flag = LoS_flag;

                temp1->pathloss_dB = dist_loss;
                temp2->pathloss_dB = dist_loss;

                temp1->coupling_loss=temp1->pathloss_dB-3;
                temp2->coupling_loss=temp2->pathloss_dB-3;

                temp1->pathloss = pow((double)10.0,(temp1->pathloss_dB/10.0));
                temp2->pathloss = pow((double)10.0,(temp2->pathloss_dB/10.0));

                (*mt_ptr)->comm_mt_list.push_back(temp1);
                (*mt_ptr2)->comm_mt_list.push_back(temp2);

            }

        }
        //OUT_Cl_Info<<(*mt_ptr)->comm_mt_list.size()<<"\t"<<mt_id<<endl;
	}

}

double MT2MTGAIN_CAC::Cac_distloss(bool LoSflag,double dist)
{
    double dist_loss=0;
	double dist_loss_freespace=0;
	double dist_loss_Outside;

	if(LoSflag==LoS)
	{
		if((dist>10.0)&&(dist<D_BP))                        //UMi 场景LOS两个公式的判断要用水平距离
			dist_loss_Outside = 22.7*log10(dist)+41.0+20.0*log10(CF/1.0e9);//第一个公式用空间距离,原来B=27

		else
			dist_loss_Outside = 40.0*log10(dist) - 17.3*log10(0.8) -17.3*log10(0.8)  +9.45;
	}
	else
    {
        dist_loss_Outside = (44.9-6.55*log10(H_MT))*log10(dist) + 14.78 + 34.97*log10(CF/1.0e9)+5.83*log10(H_MT)-5;
    }

    dist_loss = dist_loss_Outside;

	dist_loss_freespace=20*log10(dist)+46.4+20*log10((CF/1.0e9)/5);
	dist_loss=(dist_loss_freespace>dist_loss_Outside?dist_loss_freespace:dist_loss_Outside);

	return dist_loss;
}


/*-------------两个用户终端之间的路径损耗计算完成-------------*/

/*---------------基站用户终端之间的路径损耗计算---------------*/
void  MT2BSGAIN_CAC::Cac_pathloss(list<MT_INFO*> &mt_list,vector<BASE_INFO*> &base_list)
{
    int mt_posx,mt_posy,base_id,mt_id;

    double bs_posx,bs_posy;

	double mt2bs_dist;

	double mt2bs_dist_horizon,mt2bs_dist_vertical,dist_loss;	//增加计算LOS概率变量

	int LoS_flag;

	list<MT_INFO*>::iterator mt_ptr;
    vector<BASE_INFO*>::iterator bs_ptr;
    for(bs_ptr=base_list.begin();bs_ptr!=base_list.end();bs_ptr++)
    {
        bs_posx=(*bs_ptr)->base_pos.first;
        bs_posy=(*bs_ptr)->base_pos.second;
        base_id=(*bs_ptr)->base_id;

        for(mt_ptr = mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
        {
            mt_posx=(*mt_ptr)->x_sort;
		    mt_posy=(*mt_ptr)->y_sort;
		    mt_id=(*mt_ptr)->mt_id;

		    mt2bs_dist_horizon = abs(mt_posx-bs_posx);//水平距离
		    mt2bs_dist_vertical = abs(mt_posy-bs_posy);//空间距离
		    mt2bs_dist=sqrt(pow(mt2bs_dist_horizon,2)+pow(mt2bs_dist_vertical,2)); //两个用户距离

            LoS_flag =0;

            dist_loss = Cac_distloss(LoS_flag,mt2bs_dist);

            GAIN_INFO*temp=new GAIN_INFO(base_id,mt_id);

            temp->LOS_flag = LoS_flag;

            temp->pathloss_dB = dist_loss;

            temp->coupling_loss=temp->pathloss_dB-3;

            temp->pathloss = pow((double)10.0,(temp->pathloss_dB/10.0));

            (*bs_ptr)->comm_mt_list.push_back(temp);


        }

    }

}

double MT2BSGAIN_CAC::Cac_distloss(bool LoSflag,double dist)
{
    double dist_loss=0;
	double dist_loss_freespace=0;
	double dist_loss_Outside;

	if(LoSflag==LoS)
	{
		if((dist>10.0)&&(dist<D_BP))                        //UMi 场景LOS两个公式的判断要用水平距离
			dist_loss_Outside = 22.7*log10(dist)+41.0+20.0*log10(CF/1.0e9);//第一个公式用空间距离,原来B=27

		else
			dist_loss_Outside = 40.0*log10(dist) - 17.3*log10(0.8) -17.3*log10(0.8)  +9.45;
	}
	else
    {
        dist_loss_Outside = (44.9-6.55*log10(H_BS))*log10(dist) + 14.78 + 34.97*log10(CF/1.0e9)+5.83*log10(H_MT)-5;
    }

    dist_loss = dist_loss_Outside;

	dist_loss_freespace=20*log10(dist)+46.4+20*log10((CF/1.0e9)/5);
	dist_loss=(dist_loss_freespace>dist_loss_Outside?dist_loss_freespace:dist_loss_Outside);

	return dist_loss;
}

/*-------------基站用户终端之间的路径损耗计算完成-------------*/

/*---------------存储两个用户之间的相关通信信息---------------*/

void MT2MTGAIN_CAC::store_gain(list<MT_INFO*> &mt_list,unordered_map<int,vector<GAIN_INFO*>>&carrier)
{
    list<MT_INFO*>::iterator mt_ptr;

    int carrier_temp;

    for(int i=0;i<600;i++)
    {
        carrier[i].clear();
    }
    for(mt_ptr=mt_list.begin();mt_ptr!=mt_list.end();mt_ptr++)
    {

        for(auto mt_tocomm=(*mt_ptr)->comm_mt_list.begin();mt_tocomm!=(*mt_ptr)->comm_mt_list.end();mt_tocomm++)
        {
            carrier_temp=rand()%sys_realsubnum;
            if(carrier.find(carrier_temp)==carrier.end())
            {
                carrier[carrier_temp]={*mt_tocomm};
            }
            else
            carrier[carrier_temp].push_back(*mt_tocomm);
        }
    }

}

/*-------------存储两个用户之间的相关通信信息完成-------------*/
