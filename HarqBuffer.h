#ifndef HARQBUFFER_H_INCLUDED
#define HARQBUFFER_H_INCLUDED

#include "system_para.h"
#include "scenario_para.h"
#include ".\tblock_info.h"

class HARQ_BUFFER
{
public:

	TBLOCK_INFO TB_info[MT_Max_layernum][HARQ_num];

	double NACK_time[MT_Max_layernum][HARQ_num];

	bool   NDI[HARQ_num];
	//bool   NDI[MT_Max_layernum][HARQ_num];

	bool   Swap_flag[HARQ_num];

	int layer_num[HARQ_num];//�����̵Ĵ��������ÿ�ε���ǰΪ֮ǰ��HARQ_num��ʱ�̵��ȵĽ�������ε���֮��Ϊ��ǰHARQ���̵ĵ��Ⱦ��߽��

	//int RB_position[HARQ_num];

	//int RB_num[HARQ_num];

	int wait_status[MT_Max_layernum][HARQ_num];

	//int temp_HARQ_num;//��ǰ���еĽ�����


	//---------------- Soft Combining -------------------------
	int HARQ_type;

	int    Trans_times[MT_Max_layernum][HARQ_num];//�������

	//double (*SINR_record)[MT_Max_layernum][HARQ_num][ReTrans_maxNum];

	double *SINR_temp[MT_Max_layernum][HARQ_num];//��ǰ��ϲ�SINRֵ

	double SINR_eff[MT_Max_layernum][HARQ_num];

	//bool *Trans_Flag[MT_Max_layernum][HARQ_num];//����ָʾ��ǰ���ز��Ƿ����ڴ��䣬�Ƿ�Ӧ����eesm��Ȩ

	int RB_number;

	// added by ling lisha 20100315
	bool *RB_occupied_indicator[HARQ_num];
	int RB_occupied_num[HARQ_num];

	//---------------------------------------------------------


public:

	HARQ_BUFFER();

	~HARQ_BUFFER();

	void Set_Soft_buffer(int RB_num);

	void ACK_message_feedback(bool ACK_message,int HARQ_No,double ACK_message_time);//��������ACK

	void ACK_message_feedback(bool *ACK_message,int ACK_num,int HARQ_No,double ACK_message_time);//�������ACK

	void ACK_message_feedback(bool ACK_message_0,bool ACK_message_1,int HARQ_No,double ACK_message_time);

	void Increase_TransTimes(int HARQ_No,int layer);

	int Get_TransTimes(int HARQ_No,int layer);

	void Clear_buffer(int HARQ_n,int layer);

	void Clear_RB_indicator(int HARQ_index);

	void Swap_layer(int HARQ_n);

	void Swap_layer(int HARQ_n,int L_d,int L_s);

	//---------------- Soft Combining -------------------------
	void sinr_combining(int layer,int HARQ_No,double *sinr);

	//void Clear_buffer(int layer,int HARQ_No);
	//---------------------------------------------------------

};

#endif // HARQBUFFER_H_INCLUDED
