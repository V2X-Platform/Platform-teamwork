#pragma once
#include "scenario_para.h"

SCENARIO_PARA::SCENARIO_PARA(int data)
{
    CF = sys_frequency;                                 // ϵͳƵ��
    BW = sys_BW;                                        // ϵͳ����
    sectnum_pBS = sys_sectnum_pBS;                      // ÿ����վ������Ŀ
    antnum = sys_antnum_pBS;                            // ÿ����վ������Ŀ
    basenum = sys_basenum;                              // ��վ����Ŀ
    antnumtotal = antnum*basenum;

    mt_perline=MT_perline;                              // ÿ�������û�����������û��
    line_nums=Line_nums;                                // ��������
    MT_num=mt_perline*line_nums;                        // ���û�����


    Freeway_arealength = 2*sys_ISD;                     // ����·�ĳ�
    Freeway_areawidth = 50;                             // ����·�Ŀ�

    ISD = sys_ISD;                                     // ��վ���

    BS_Power = pow((double)10.0,sys_BS_Txpower/10.0);   // ��վ���书�ʣ�

    MT_num=mt_perline*line_nums;                        // �û�����
    BS_antgain = sys_BS_antgain;                        // ��վ��������
    MT_antgain = sys_MT_antgain;                        // �ն���������
    Min_dist = sys_min_dist;                            // ��С����
    H_BS = sys_H_BS;                                    // �û����߸߶�
    H_MT = sys_H_MT;                                    // �û��ֲ������ڵĸ���

}
