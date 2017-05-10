#pragma once
#include "scenario_para.h"
#include <iostream>
#include <fstream>
#include <math.h>

SCENARIO_PARA::SCENARIO_PARA(int data)
{
    CF = sys_frequency;                                 // ϵͳƵ��
    BW = sys_BW;                                        // ϵͳ����

}

SCENARIO_PARA::~SCENARIO_PARA(){}

SCENARIO_FREEWAY::SCENARIO_FREEWAY(int data):SCENARIO_PARA(data)
{

    sectnum_pBS = 3;                                    // ÿ����վ������Ŀ
    antnum_pBS=1;                                        // ÿ����վ������Ŀ
    basenum = 2;                                        // ��վ����Ŀ
    antnumtotal = antnum_pBS*basenum;
    area_num = 7;

    mt_perline=50;                                      // ÿ�������û�����������û��
    line_nums=6;                                        // ��������
    MT_num=mt_perline*line_nums;                        // ���û�����

    ISD = 1732;                                         // ��վ���
    Freeway_arealength = 2*ISD;                         // ����·�ĳ�
    Freeway_areawidth = 50;                             // ����·�Ŀ�

    cell_mt_num = 100;                                  // ÿ��С�����û���

    BS_Txpower = 46.0;
    //BS_Power = pow((double)10.0,BS_Txpower/10.0);       // ��վ���书��
    BS_antgain = 3;                                     // ��վ��������

    MT_Txpower = 23.0;
    //MT_Power = pow((double)10.0,MT_Txpower/10.0);
    MT_antgain = 0.0;                                   // �ն���������

    Min_dist = 35;                                      // ��С����

    BS_noise_fig = 5.0;                                 // ��վ������ָ����dBΪ��λ
    BS_recv_noise = pow((double)10.0,BS_noise_fig/10.0);// ��վ�Ľ�������
    BS_feed_loss = 0.0;//---------------------------------------2.0; // һ������������û�õĻ��Ժ��ɾ����

    MT_noise_fig = 7.0;                                 // �û�������ָ����dBΪ��λ
    MT_recv_noise = pow((double)10.0,MT_noise_fig/10.0);
    Min_dist = 35;                                      // ��С����
    MT_vmean = 70;                                      // �����ٶ�

    H_BS = 5;                                           // ��վ���߸߶�
    H_MT = 1.5;                                         // �û����߸߶�

    base_vect[0] = make_pair(ISD/2,0.0);                 // ��վλ��
    base_vect[1] = make_pair(-ISD/2,0.0);

    //********************* area_vect generation *********************

    double cellradius = ISD/3.0;//1 site with 3 cells��С���߳�a

    double cell_distance = cellradius*sqrt(3.0);//site������С���ļ�࣬site�ı߳�A

    pair<double,double> rotate_vect = make_pair(cos(PI/3),sin(PI/3));

    pair<double,double> area_vect_ref[7];

    area_vect_ref[0] = pair<double,double>(0.0,0.0);

    area_vect_ref[1] = pair<double,double>(12*cellradius,sqrt(3.0)*3*cellradius);


    for(int i=2; i<7; i++)
    {
        area_vect_ref[i] = xuanzhuan(area_vect_ref[i-1],rotate_vect);
    }

    for (int i = 0; i < area_num; i++)
    {
        area_vect[i] = area_vect_ref[i];
    }

    BS_boresight_gain = 17.0;
    MT_boresight_gain = 17.0;

}

SCENARIO_FREEWAY::~SCENARIO_FREEWAY(void){}

int SCENARIO_FREEWAY::get_sectnum_pBS()
{
    return sectnum_pBS;
}

int SCENARIO_FREEWAY::get_antnum_pBS()
{
    return antnum_pBS;
}

int SCENARIO_FREEWAY::get_basenum()
{
    return basenum;
}

int SCENARIO_FREEWAY::get_antnumtotal()
{
    return antnumtotal;
}

int SCENARIO_FREEWAY::get_mt_perline()
{
    return mt_perline;
}

int SCENARIO_FREEWAY::get_line_nums()
{
    return line_nums;
}

int SCENARIO_FREEWAY::get_MT_num()
{
    return MT_num;
}

int SCENARIO_FREEWAY::get_ISD()
{
    return ISD;
}

double SCENARIO_FREEWAY::get_arealength()
{
    return Freeway_arealength;
}

double SCENARIO_FREEWAY::get_areawidth()
{
    return Freeway_areawidth;
}

int SCENARIO_FREEWAY::get_cell_mt_num()
{
    return cell_mt_num;
}

int SCENARIO_FREEWAY::get_area_num()
{
    return area_num;
}

double SCENARIO_FREEWAY::get_BS_Txpower()
{
    return BS_Txpower;
}

double SCENARIO_FREEWAY::get_BS_antgain()
{
    return BS_antgain;
}

double SCENARIO_FREEWAY::get_MT_antgain()
{
    return MT_antgain;
}

double SCENARIO_FREEWAY::get_MT_Txpower()
{
    return MT_Txpower;
}

double SCENARIO_FREEWAY::get_Min_dist()
{
    return Min_dist;
}


double SCENARIO_FREEWAY::get_BS_feed_loss()
{
    return BS_feed_loss;
}

double SCENARIO_FREEWAY::get_BS_noise_fig()
{
    return BS_noise_fig;
}

double SCENARIO_FREEWAY::get_MT_noise_fig()
{
    return MT_noise_fig;
}

double SCENARIO_FREEWAY::get_MT_feed_loss()
{
    return MT_feed_loss;
}
double SCENARIO_FREEWAY::get_MT_vmean()
{
    return MT_vmean;
}

double SCENARIO_FREEWAY::get_H_MT()
{
    return H_MT;
}

double SCENARIO_FREEWAY::get_H_BS()
{
    return H_BS;
}

double SCENARIO_FREEWAY::get_BS_boresight_gain()
{
    return BS_boresight_gain;
}

double SCENARIO_FREEWAY::get_MT_boresight_gain()
{
    return MT_boresight_gain;
}


pair<double,double>* SCENARIO_FREEWAY::get_base_vect()
{
    return base_vect;
}

pair<double,double>* SCENARIO_FREEWAY::get_area_vect()
{
    return area_vect;
}

SCENARIO::SCENARIO(SCENARIO_PARA* scenario_data)
{
    CF=scenario_data->CF;	                                           // System main Carrier frequency in Hz
	BW=scenario_data->BW;                                              // FDD system bandwidth

    sectnum_pBS = scenario_data->get_sectnum_pBS();                    // ÿ����վ������Ŀ
    antnum_pBS=scenario_data->get_antnum_pBS();                        // ÿ����վ������Ŀ
    basenum = scenario_data->get_basenum();                            // ��վ����Ŀ
    antnumtotal = antnum_pBS*basenum;
    area_num= scenario_data->get_area_num();

    mt_perline=scenario_data->get_mt_perline();                        // ÿ�������û�����������û��
    line_nums=scenario_data->get_line_nums();                          // ��������
    MT_num=mt_perline*line_nums;                                       // ���û�����

    ISD = scenario_data->get_ISD();                                    // ��վ���
    Freeway_arealength = scenario_data->get_arealength();              // ����·�ĳ�
    Freeway_areawidth = scenario_data->get_areawidth();                // ����·�Ŀ�

    cell_mt_num = scenario_data->get_cell_mt_num();                    // ÿ��С�����û���

    BS_Txpower = scenario_data->get_BS_Txpower();
    BS_Power = pow((double)10.0,BS_Txpower/10.0);                      // ��վ���书��
    BS_antgain = scenario_data->get_BS_antgain();                      // ��վ��������

    MT_Txpower = scenario_data->get_MT_Txpower();
    MT_Power = pow((double)10.0,MT_Txpower/10.0);
    MT_antgain = scenario_data->get_MT_antgain();                      // �ն���������
    Min_dist = scenario_data->get_Min_dist();                          // ��С����

    BS_noise_fig = scenario_data->get_BS_noise_fig();                  // ��վ������ָ����dBΪ��λ
    BS_recv_noise = pow((double)10.0,BS_noise_fig/10.0);               // ��վ�Ľ�������
    BS_feed_loss = scenario_data->get_BS_feed_loss();//---------------------------------------2.0; // һ������������û�õĻ��Ժ��ɾ����

    MT_noise_fig = scenario_data->get_MT_noise_fig();                  // �û�������ָ����dBΪ��λ
    MT_recv_noise = pow((double)10.0,MT_noise_fig/10.0);

    MT_vmean = scenario_data->get_MT_vmean();                          // �����ٶ�

    H_BS = scenario_data->get_H_BS();                                  // ��վ���߸߶�
    H_MT = scenario_data->get_H_MT();                                  // �û����߸߶�

    base_vect = scenario_data->get_base_vect();                          // ��վλ��
    area_vect = scenario_data->get_area_vect();

    BS_boresight_gain=scenario_data->get_BS_boresight_gain();
    MT_boresight_gain=scenario_data->get_MT_boresight_gain();

}

pair <double,double> SCENARIO_PARA::xuanzhuan(pair <double,double> pos,pair <double,double>rotate_v)
{
    pair<double,double> result;

    result.first = pos.first*rotate_v.first-pos.second*rotate_v.second;
    result.second = pos.first*rotate_v.second+pos.second*rotate_v.first;

    return result;
}
