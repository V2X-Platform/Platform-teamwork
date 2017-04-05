#ifndef ENTERN_H_INCLUDED
#define ENTERN_H_INCLUDED

#pragma once
#include "system_Para.h"

extern int loop_index;
extern int step;
extern int SubFrame_index;

extern int mt_traceid;
extern int subFrame_traced;

extern int trace_idx;

extern int Retrans_times;
extern int Trans_times;

extern int Init_retrans_times;
extern int Init_trans_times;

//===========================================================================================================================
//跟踪用户的信道变化状况
#ifdef TraceDebug_Mode

//在MIMO_CHANNEL中写入,SIMULATION中输出
extern double MT_traced_Hr[loop_num*SubFrame_num][sys_MT_antnum*sys_BS_antnum*NRB];//跟踪用户到连接天线的频域信道响应的实部值
extern double MT_traced_Hi[loop_num*SubFrame_num][sys_MT_antnum*sys_BS_antnum*NRB];//跟踪用户到连接天线的频域信道响应的虚部值

//在STI_CAC中写入,SIMULATION中输出
extern double MT_traced_sinr[loop_num*SubFrame_num][NRB];//实际传输中得到的各RB上的sinr值

//在FEEDBACK_PROCESS中写入,SIMULATION中输出
extern double MT_traced_cqi[loop_num*SubFrame_num/CQI_Np][NRB];//反馈时计算得到各RB上的sinr值

//extern double CQI_Feedback[570][NRB];//跟踪时刻的前一个反馈时刻所有用户在所有子载波上的反馈sinr值
//extern double Rxsinr_Traced_t[570][NRB];//跟踪时刻所有用户在被调度子载波上的实际接收sinr值

#endif

//===========================================================================================================================
//资源分配方式
extern int ResAllocateType;

//------------资源分配粒度---------
//------在SIMULATION中被初始化-----
extern int sys_RBG_num;
extern int *sys_RBG_size;
//extern int sys_RBG_size_last;
//---------------------------------

// ------------- 日志文件 -------------
extern char	g_szLog[10];

#endif // ENTERN_H_INCLUDED
