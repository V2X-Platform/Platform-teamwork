#ifndef SYSTEM_PARA_H_INCLUDED
#define SYSTEM_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include <math.h>

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


// -------------Base and MT configuration related parameters---------------

const double    BS_noise_fig = 5.0; // 基站的噪声指数，dB为单位
const double    BS_recv_noise = pow((double)10.0,BS_noise_fig/10.0);               //基站的接收噪声
const double    BS_feeder_loss = 2.0;//---------------------------------------2.0; // 一个补偿噪声，没用的话以后就删除了

const double    MT_noise_fig = 7.0; // 用户的噪声指数，dB为单位
const double    MT_recv_noise = pow((double)10.0,MT_noise_fig/10.0);

const int       sys_cell_mtnum = 100;  //待考察的变量

// Subcarrier information	20MHz bandwidth -- 100RB -- 44dBm
const int       sys_bindnum = 12;                                       // system binding group subcarrier number
const int       sys_realsubnum=600;
const int 		sys_RBnum = sys_realsubnum/sys_bindnum;			        // system sub carrier group using
const double	RBbandwidth = 180e3;                                    // RB 一个RB的带宽
const double    sys_subc_BW = 15e3;                                     // 一个子载波带宽 一个RB是180kHz，每个RB12个子载波，每个子载波就是15kHz
const int		sys_sym_num = 7*20;                                     // 没用就删。

const double	sys_frequency=6e9;	                                    // 系统频段System main Carrier frequency in Hz
const double    sys_BW=10e6;                                            // 系统带宽
const int       sys_sectnum_pBS=1;                                      // 每个基站扇区数目
const int		sys_antnum_pBS=1;         		                        // 每个基站的天线数量
const int		sys_basenum=2;			                                // 基站数目

//车道信息
const int       MT_perline=50;                                          // 车道内车辆数目
const int       Line_nums=6;                                            // 车道数目
const int       MT_num=MT_perline*Line_nums;                            // 用户总数

const double    sys_ISD = 1732;                                          // 基站间间距
const double	sys_BS_Txpower = 23;                                     // BS发射功率(dBm)
const double    sys_BS_antgain = 3;                                      // dBi天线增益
const double    sys_MT_antgain = 0.0;                                    // dBi用户增益
const double    sys_min_dist = 35;
const double    sys_H_BS = 5;                                            // 基站天线高度
const double    sys_H_MT = 1.5;                                          // 用户天线高度
const double    sys_MT_vmean = 70;                                       // 用户移动速度
const double    sys_MT_Power=23.0;                                        // 用户发射功率
const double    sys_BS_Power=46.0;                                         // 基站发射功率

#endif // SYSTEM_H_INCLUDED
