#ifndef SYSTEM_PARA_H_INCLUDED
#define SYSTEM_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include <math.h>

const int       non_statistic_time = 200;//ms,������Ϊ200��TTI֮��ϵͳ�Ѿ�������̬��֮ǰ�����Ƿ���̬������˲�ͳ��ǰ200��TTI��200Ӧ�����㹻�ģ���������ʵ���ֵ�����ȴ��ڵĴ�С�йأ�


// #######################################  Common Parameters  ###########################################
const double    c_velocity = 3e8;		                                // ����
const double    ThermalleveldB = -174;								    //thermal noise level: -174dBm/Hz
const double	Thermallevel = pow((double)10.0,ThermalleveldB/10);

// -------------Simulation Para---------------

const int       loop_num = 1;  // drop
const int       step_all = 1;  //not used
const int       SubFrame_num =100/*1*//*1200*/;					// ע��ÿ��drop����֡��Ӧ�ô���Ԥ��TTI�� - non_statistic_time - 200+
const double    sys_subframe_time = 0.001;//1 ms
const double	sys_tstep = sys_subframe_time*SubFrame_num;		// Simulation time step


// -------------Base and MT configuration related parameters---------------

const double    BS_noise_fig = 5.0; // ��վ������ָ����dBΪ��λ
const double    BS_recv_noise = pow((double)10.0,BS_noise_fig/10.0);               //��վ�Ľ�������
const double    BS_feeder_loss = 2.0;//---------------------------------------2.0; // һ������������û�õĻ��Ժ��ɾ����

const double    MT_noise_fig = 7.0; // �û�������ָ����dBΪ��λ
const double    MT_recv_noise = pow((double)10.0,MT_noise_fig/10.0);

const int       sys_cell_mtnum = 100;  //������ı���

// Subcarrier information	20MHz bandwidth -- 100RB -- 44dBm
const int       sys_bindnum = 12;                                       // system binding group subcarrier number
const int       sys_realsubnum=600;
const int 		sys_RBnum = sys_realsubnum/sys_bindnum;			        // system sub carrier group using
const double	RBbandwidth = 180e3;                                    // RB һ��RB�Ĵ���
const double    sys_subc_BW = 15e3;                                     // һ�����ز����� һ��RB��180kHz��ÿ��RB12�����ز���ÿ�����ز�����15kHz
const int		sys_sym_num = 7*20;                                     // û�þ�ɾ��

const double	sys_frequency=6e9;	                                    // ϵͳƵ��System main Carrier frequency in Hz
const double    sys_BW=10e6;                                            // ϵͳ����
const int       sys_sectnum_pBS=1;                                      // ÿ����վ������Ŀ
const int		sys_antnum_pBS=1;         		                        // ÿ����վ����������
const int		sys_basenum=2;			                                // ��վ��Ŀ

//������Ϣ
const int       MT_perline=50;                                          // �����ڳ�����Ŀ
const int       Line_nums=6;                                            // ������Ŀ
const int       MT_num=MT_perline*Line_nums;                            // �û�����

const double    sys_ISD = 1732;                                          // ��վ����
const double	sys_BS_Txpower = 23;                                     // BS���书��(dBm)
const double    sys_BS_antgain = 3;                                      // dBi��������
const double    sys_MT_antgain = 0.0;                                    // dBi�û�����
const double    sys_min_dist = 35;
const double    sys_H_BS = 5;                                            // ��վ���߸߶�
const double    sys_H_MT = 1.5;                                          // �û����߸߶�
const double    sys_MT_vmean = 70;                                       // �û��ƶ��ٶ�
const double    sys_MT_Power=23.0;                                        // �û����书��
const double    sys_BS_Power=46.0;                                         // ��վ���书��

#endif // SYSTEM_H_INCLUDED
