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
//�����û����ŵ��仯״��
#ifdef TraceDebug_Mode

//��MIMO_CHANNEL��д��,SIMULATION�����
extern double MT_traced_Hr[loop_num*SubFrame_num][sys_MT_antnum*sys_BS_antnum*NRB];//�����û����������ߵ�Ƶ���ŵ���Ӧ��ʵ��ֵ
extern double MT_traced_Hi[loop_num*SubFrame_num][sys_MT_antnum*sys_BS_antnum*NRB];//�����û����������ߵ�Ƶ���ŵ���Ӧ���鲿ֵ

//��STI_CAC��д��,SIMULATION�����
extern double MT_traced_sinr[loop_num*SubFrame_num][NRB];//ʵ�ʴ����еõ��ĸ�RB�ϵ�sinrֵ

//��FEEDBACK_PROCESS��д��,SIMULATION�����
extern double MT_traced_cqi[loop_num*SubFrame_num/CQI_Np][NRB];//����ʱ����õ���RB�ϵ�sinrֵ

//extern double CQI_Feedback[570][NRB];//����ʱ�̵�ǰһ������ʱ�������û����������ز��ϵķ���sinrֵ
//extern double Rxsinr_Traced_t[570][NRB];//����ʱ�������û��ڱ��������ز��ϵ�ʵ�ʽ���sinrֵ

#endif

//===========================================================================================================================
//��Դ���䷽ʽ
extern int ResAllocateType;

//------------��Դ��������---------
//------��SIMULATION�б���ʼ��-----
extern int sys_RBG_num;
extern int *sys_RBG_size;
//extern int sys_RBG_size_last;
//---------------------------------

// ------------- ��־�ļ� -------------
extern char	g_szLog[10];

#endif // ENTERN_H_INCLUDED
