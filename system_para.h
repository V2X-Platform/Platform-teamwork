#ifndef SYSTEM_PARA_H_INCLUDED
#define SYSTEM_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include <math.h>
#include <utility>
using namespace std;

const int       non_statistic_time = 200;//ms,这里认为200个TTI之后系统已经步入稳态（之前可能是非稳态），因此不统计前200个TTI（200应该是足够的，具体最合适的数值跟调度窗口的大小有关）


// #######################################  Common Parameters  ###########################################
const double    c_velocity = 3e8;		                                // 光速
const double    ThermalleveldB = -174;								    //thermal noise level: -174dBm/Hz
const double	Thermallevel = pow((double)10.0,ThermalleveldB/10);

// -------------Simulation Para---------------

const int       loop_num = 1;  // drop
const int       step_all = 1;  //not used
const int       SubFrame_num =100/*1*//*1200*/;					// 注：每个drop的子帧数应该大于预热TTI数 - non_statistic_time - 200+
const double    sys_subframe_time = 0.001;//1 ms
const double	sys_tstep = sys_subframe_time*SubFrame_num;		// Simulation time step



// Subcarrier information	20MHz bandwidth -- 100RB -- 44dBm
const int       sys_bindnum = 12;                                       // system binding group subcarrier number
const int       sys_realsubnum=600;
const int 		sys_RBnum = sys_realsubnum/sys_bindnum;			        // system sub carrier group using
const double	RBbandwidth = 180e3;                                    // RB 一个RB的带宽
const double    sys_subc_BW = 15e3;                                     // 一个子载波带宽 一个RB是180kHz，每个RB12个子载波，每个子载波就是15kHz
const int		sys_sym_num = 7*20;                                     // 没用就删。

const double	sys_frequency=6e9;	                                    // 系统频段System main Carrier frequency in Hz
const double    sys_BW=10e6;                                            // 系统带宽


//system antenna gain information, see r1-091320 - ITU test environments.doc in detail
const double    sys_theta3dB = 70.0;             //3dB增益对应的水平夹角单位为°
const double    sys_Am = 20.0;					 //最大增益
const double    sys_phi_tilt[5] = {0,12.0,12.0,6.0,6.0};             //UMi UMa场景下天下垂直倾角
const double    sys_phi_3dB = 15.0;				// 3dB增益对应的垂直夹角单位为°

const double    Phi_tilt = sys_phi_tilt[1];           // Antenna Pattern中的垂直下倾角

const bool      MT_omni = 1;


//---------------- For SU-MIMO ----------------
const int         nMtMaxLayernum = 1;
//const int       sys_Max_layernum = 2;
//const int       MT_pairing_Max = 1;//最大用户配对数
//const int       Schedule_scheme = SU_MIMO;// SU_MIMO , MU_MIMO
//const int       sys_BS_antnum = 4;
//const int       sys_MT_antnum = 2;
//------------------------------------------------------------*/

#endif // SYSTEM_H_INCLUDED
