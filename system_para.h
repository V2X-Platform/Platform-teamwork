#ifndef SYSTEM_PARA_H_INCLUDED
#define SYSTEM_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include <math.h>
#include <utility>
using namespace std;

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



// Subcarrier information	20MHz bandwidth -- 100RB -- 44dBm
const int       sys_bindnum = 12;                                       // system binding group subcarrier number
const int       sys_realsubnum=600;
const int 		sys_RBnum = sys_realsubnum/sys_bindnum;			        // system sub carrier group using
const double	RBbandwidth = 180e3;                                    // RB һ��RB�Ĵ���
const double    sys_subc_BW = 15e3;                                     // һ�����ز����� һ��RB��180kHz��ÿ��RB12�����ز���ÿ�����ز�����15kHz
const int		sys_sym_num = 7*20;                                     // û�þ�ɾ��

const double	sys_frequency=6e9;	                                    // ϵͳƵ��System main Carrier frequency in Hz
const double    sys_BW=10e6;                                            // ϵͳ����


//system antenna gain information, see r1-091320 - ITU test environments.doc in detail
const double    sys_theta3dB = 70.0;             //3dB�����Ӧ��ˮƽ�нǵ�λΪ��
const double    sys_Am = 20.0;					 //�������
const double    sys_phi_tilt[5] = {0,12.0,12.0,6.0,6.0};             //UMi UMa���������´�ֱ���
const double    sys_phi_3dB = 15.0;				// 3dB�����Ӧ�Ĵ�ֱ�нǵ�λΪ��

const double    Phi_tilt = sys_phi_tilt[1];           // Antenna Pattern�еĴ�ֱ�����

const bool      MT_omni = 1;


//---------------- For SU-MIMO ----------------
const int         nMtMaxLayernum = 1;
//const int       sys_Max_layernum = 2;
//const int       MT_pairing_Max = 1;//����û������
//const int       Schedule_scheme = SU_MIMO;// SU_MIMO , MU_MIMO
//const int       sys_BS_antnum = 4;
//const int       sys_MT_antnum = 2;
//------------------------------------------------------------*/

#endif // SYSTEM_H_INCLUDED
