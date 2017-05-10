#include "stdafx.h"
#include "gain_cac.h"
#include "system_para.h"
#include "gain_info.h"
#include <utility>
#include <fstream>
#include <stdlib.h>
#include "extern.h"
#include "random.h"
#include "scenario_para.h"
#include "tools.h"
#include "math.h"

/*-------------------基类构造函数、析构函数-------------------*/
GAIN_CAC::GAIN_CAC(SCENARIO scenario_data)
{
	CF = sys_frequency;//Hz

	H_MT = scenario_data.H_MT;

	H_BS = scenario_data.H_BS;

	MT_boresight_gain = scenario_data.MT_boresight_gain;

	BS_boresight_gain = scenario_data.BS_boresight_gain;

    cell_distance = scenario_data.ISD/sqrt(3.0);

    antnum_pBS=scenario_data.antnum_pBS;
}

GAIN_CAC::~GAIN_CAC(void){}

/*-----------------基类构造函数、析构函数完成-----------------*/

double GAIN_CAC::Cac_Antenna_Gain(double angle_H,double angle_V,bool omni,double boresight_gain)
{
    double ant_gain_dB = 0;

	if(omni)
	{
		ant_gain_dB = boresight_gain;//线性值
	}
	else
	{
		double temp1 = -Cac_Antenna_Gain_Horizontal(angle_H);
		double temp2 = -Cac_Antenna_Gain_Vertical(angle_V);

		double ant_gain_dB_temp = - ((temp1+temp2)<sys_Am ? (temp1+temp2):sys_Am);

		ant_gain_dB = boresight_gain + ant_gain_dB_temp;
	}

	return ant_gain_dB;//返回dB值
}


double GAIN_CAC::Cac_Antenna_Gain_Horizontal(double angle_phi)
{
    double ant_gain = 0;

	//角度范围调整至[-180，180）
	while (angle_phi>=180)
	{
		angle_phi = angle_phi - 360;
	}
	while (angle_phi<-180)
	{
		angle_phi = angle_phi + 360;
	}

	double tempAtheta = 12*pow((double)(angle_phi/sys_theta3dB),2);

	ant_gain = tempAtheta<sys_Am? tempAtheta:sys_Am;

	return -ant_gain;//返回dB值
}

double GAIN_CAC::Cac_Antenna_Gain_Vertical(double angle_phi)
{
    	//角度范围调整至[-180，180）
	while (angle_phi>=180)
	{
		//angle_phi = angle_phi - 360;
		angle_phi = 360 - angle_phi;
	}
	while (angle_phi<-180)
	{
		angle_phi = angle_phi + 360;
	}

	double ant_gain = 0;

	double tempAphi = 12*pow((double)((angle_phi-Phi_tilt)/sys_phi_3dB),2); //天线垂直夹角增益 phatilt与场景有关

	ant_gain = tempAphi<sys_Am? tempAphi:sys_Am;                    //Am 为20dB

	return -ant_gain;//返回dB值
}

double GAIN_CAC::Cac_theta(pair<double,double> base_pos, pair<double,double> mt_pos)
{
    pair<double,double> antmt_vect=make_pair(mt_pos.first-base_pos.first,mt_pos.second-base_pos.second);

    double Min_theta = 1000000.0;

    //set the mt-to-bs vecotrs and related angles

    for(int ant_id=0;ant_id<antnum_pBS;ant_id++)
    {
        double theta = arg(antmt_vect)-PI/3 + 2*PI/3*ant_id; ;//直视路径相对于扇区天线朝向的夹角

        if(theta<-PI)
            theta = theta + 2*PI;
        else if(theta>PI)
            theta = theta - 2*PI;

        if(theta<0)
        {
            Min_theta = -theta<Min_theta?-theta:Min_theta;
        }
        else
        {
            Min_theta = theta<Min_theta?theta:Min_theta;
        }
    }

    Min_theta = Min_theta*180/PI;                  //弧度转成角度

    return Min_theta;
}

double GAIN_CAC::Cac_phi(pair<double,double> base_pos, pair<double,double> mt_pos)
{

    pair<double,double> antmt_vect = make_pair(mt_pos.first-base_pos.first,mt_pos.second-base_pos.second);

	double antmt_dist = cac_length(antmt_vect);
	double phi=arg(antmt_dist,H_BS-H_MT);
	return phi;
}

/*------------------派生类构造函数、析构函数------------------*/

MT2MTGAIN_CAC::MT2MTGAIN_CAC(SCENARIO scenario_data):GAIN_CAC(scenario_data)
{
	D_BP  = 4*(H_MT-1.0)*(H_MT-1.0)*CF/c_velocity;
}

MT2MTGAIN_CAC::~MT2MTGAIN_CAC(void){}

MT2BSGAIN_CAC::MT2BSGAIN_CAC(SCENARIO scenario_data):GAIN_CAC(scenario_data)
{

	D_BP  = 4*(H_BS-1.0)*(H_MT-1.0)*CF/c_velocity;
}

MT2BSGAIN_CAC::~MT2BSGAIN_CAC(void){}

/*----------------派生类构造函数、析构函数完成----------------*/


/*---------------两个用户终端之间的路径损耗计算---------------*/

void  MT2MTGAIN_CAC::Cac_pathloss(vector<BASE_INFO*>&base_list,list <MT_INFO*>&mt_list)
{
    int mt_posx,mt_posy,mt_posx2,mt_posy2,mt_id,mt_id2;

	double mt2mt_dist;

	double mt2mt_dist_horizon,mt2mt_dist_vertical;	//增加计算LOS概率变量

	double temp_dist_loss,temp_Atotal,temp_pathloss,temp_Antenna_Gain;            //当前计算值

	double theta,phi;                                           //天线之间相对角度

	int LoS_flag;

	std::ofstream OUT_Cl_Info("result/coupling_loss.txt",ios::out|ios::trunc);

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

                theta = 0.0;  //用户天线是全向性的，和角度无关，所以暂时只写0.0,留个计算接口，若以后需要可以添加

                phi = 0.0;    //用户天线是全向性的，和角度无关，所以暂时只写0.0,留个计算接口，若以后需要可以添加


                //Set_LoSflag(base_list[base_index],*mt_ptr,LoS_flag,mt_Indoor); 这行还有用，不过暂时不知道怎么利用

                temp_dist_loss = Cac_distloss(LoS_flag,mt2mt_dist);

                GAIN_INFO*temp1=new GAIN_INFO(mt_id,mt_id2);
                GAIN_INFO*temp2=new GAIN_INFO(mt_id2,mt_id);

                temp1->bs2mt_flag=0;
                temp2->bs2mt_flag=0;

                temp1->LOS_flag = LoS_flag;
                temp2->LOS_flag = LoS_flag;

                temp1->pathloss_dB = temp_dist_loss;
                temp2->pathloss_dB = temp_dist_loss;

                temp_Atotal = Cac_Antenna_Gain(theta,phi,1,MT_boresight_gain);
                temp1->Atotal = temp_Atotal;
                temp2->Atotal = temp_Atotal;

                temp_Antenna_Gain=pow((double)10.0,temp_Atotal);
                temp1->Antenna_Gain = temp_Antenna_Gain;
                temp2->Antenna_Gain = temp_Antenna_Gain;

                temp_pathloss = pow((double)10.0,(temp_dist_loss/10.0));
                temp1->pathloss = temp_pathloss;
                temp2->pathloss = temp_pathloss;

                (*mt_ptr)->comm_mt_list.push_back(temp1);
                (*mt_ptr2)->comm_mt_list.push_back(temp2);

            }

        }
        OUT_Cl_Info<<(*mt_ptr)->comm_mt_list.size()<<"\t"<<mt_id<<endl;
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
void  MT2BSGAIN_CAC::Cac_pathloss(vector<BASE_INFO*>&base_list,list <MT_INFO*>&mt_list)
{
    int mt_posx,mt_posy,base_id,mt_id;

    double bs_posx,bs_posy;

	double mt2bs_dist;

	double mt2bs_dist_horizon,mt2bs_dist_vertical,dist_loss;	//增加计算LOS概率变量

	int LoS_flag;

	double theta,phi;

	std::ofstream OUT_Cl_Info("result/coupling_loss1.txt",ios::out|ios::trunc);

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

		    if(mt2bs_dist< cell_distance)

            {
                LoS_flag =0;

                theta = Cac_theta((*bs_ptr)->base_pos,(*mt_ptr)->mt_position);

                phi = Cac_phi((*bs_ptr)->base_pos,(*mt_ptr)->mt_position);

                GAIN_INFO*temp=new GAIN_INFO(base_id,mt_id);

                temp->bs2mt_flag=1;

                temp->LOS_flag = LoS_flag;

                temp->pathloss_dB = Cac_distloss(LoS_flag,mt2bs_dist);

                temp->Atotal = Cac_Antenna_Gain(theta,phi,0,BS_boresight_gain);

                temp->Antenna_Gain = pow((double)10.0,(temp->Atotal/10.0));

                temp->pathloss = pow((double)10.0,(temp->pathloss_dB/10.0));

                (*bs_ptr)->comm_mt_list.push_back(temp);

                OUT_Cl_Info<<temp->Atotal<<"\t"<<mt_id<<endl;
            }
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
		if((dist>10.0)&&(dist<D_BP))
			dist_loss_Outside = 22.7*log10(dist)+41.0+20.0*log10(CF/1.0e9);

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

/*---------------存储基站用户之间的相关通信信息---------------*/

void MT2BSGAIN_CAC::store_gain(list<MT_INFO*> &mt_list,vector <BASE_INFO*> &base_list,unordered_map<int,vector<GAIN_INFO*>>&carrier)
{
    vector <BASE_INFO*>::iterator bs_ptr;

    int carrier_temp;

    for(bs_ptr=base_list.begin();bs_ptr!=base_list.end();bs_ptr++)
    {

        for(auto mt_tocomm=(*bs_ptr)->comm_mt_list.begin();mt_tocomm!=(*bs_ptr)->comm_mt_list.end();mt_tocomm++)
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

/*-------------存储基站用户之间的相关通信信息完成-------------*/

double MT2BSGAIN_CAC::Cac_delay(double V,double E)
{
    /*double X = random_0to1();//X产生
    double Tao = (-1)*3.2 * sigma_DS * log(X);//tao产生
    double D_factor = 0.7705 - 0.0433*sigma_K + 0.0002*pow((double)sigma_K,2) + 0.000017*pow((double)sigma_K,3);//D的生成
    double Path_delay=Tao/D_factor;//最终生成延迟

    return Path_delay;*/
    return 0.0;
}

double MT2MTGAIN_CAC::Cac_delay(double V,double E)
{
    /*double X = random_0to1();//X产生
    double Tao = (-1)*3.2 * sigma_DS * log(X);//tao产生
    double D_factor = 0.7705 - 0.0433*sigma_K + 0.0002*pow((double)sigma_K,2) + 0.000017*pow((double)sigma_K,3);//D的生成
    double Path_delay=Tao/D_factor;//最终生成延迟
    return Path_delay;*/
    return 0.0;
}

