#ifndef TBLOCK_H_INCLUDED
#define TBLOCK_H_INCLUDED

#include "system_para.h"
#include "scenario_para.h"

class TBLOCK_INFO
{
public:

	int paket_id;//L3���ݰ�

	int TB_id;// L2����

	int TB_size;

	int Modulation;//��ǰ�����ĵ��Ʒ�ʽ

	double code_rate;//����

	double Generate_times;//��������ʱ��

	int transmit_times;//�Ѵ������

	TBLOCK_INFO(int paket_i,int TB_i,double gen_time);

	TBLOCK_INFO();

	~TBLOCK_INFO();

	void Clear();

	void Increase_TransTimes();

	int Get_TransTimes();

	void Set_MCS(int CQI_index);

	void Set_TBsize(int RB_num);
};

#endif // TBLOCK_H_INCLUDED
