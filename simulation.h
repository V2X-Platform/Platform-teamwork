#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED


/*��ͷ�ļ���������¼һЩ�������ݣ�Ŀǰ�������һ��ȫ�ֱ���������*/
#pragma once

#include "base_info.h"
#include "mt_info.h"
#include "scenario_para.h"
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include "extern.h"


class SIMULATION
{
public:

	int mt_num;						 // active mt number

	int mt_perline;                  // ÿ����·���û�����
	int line_nums;                   // ��·����

	int mt_newnum;					 // the new generate MT number

	int basenum;                     //��վ��Ŀ
	int antnum;                      //������Ŀ
	double BW;                       //���ߴ���


    vector<BASE_INFO*> base_list;                            //��վ�б�
    list <MT_INFO*> mt_list;                                 //�û��б�
    unordered_map<int,vector<GAIN_INFO*>>  carrier;          //ҵ���б�

    SIMULATION(SCENARIO_PARA &scenario_data);
	~SIMULATION();
};

#endif // SIMULATION_H_INCLUDED
