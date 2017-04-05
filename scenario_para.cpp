#pragma once
#include "scenario_para.h"

SCENARIO_PARA::SCENARIO_PARA(int data)
{
    CF = sys_frequency;                                 // 系统频带
    BW = sys_BW;                                        // 系统带宽
    sectnum_pBS = sys_sectnum_pBS;                      // 每个基站扇区数目
    antnum = sys_antnum_pBS;                            // 每个基站天线数目
    basenum = sys_basenum;                              // 基站总数目
    antnumtotal = antnum*basenum;

    mt_perline=MT_perline;                              // 每个车道用户数量，可能没用
    line_nums=Line_nums;                                // 车道数量
    MT_num=mt_perline*line_nums;                        // 总用户数量


    Freeway_arealength = 2*sys_ISD;                     // 高速路的长
    Freeway_areawidth = 50;                             // 高速路的宽

    ISD = sys_ISD;                                     // 基站间距

    BS_Power = pow((double)10.0,sys_BS_Txpower/10.0);   // 基站发射功率；

    MT_num=mt_perline*line_nums;                        // 用户数量
    BS_antgain = sys_BS_antgain;                        // 基站天线增益
    MT_antgain = sys_MT_antgain;                        // 终端天线增益
    Min_dist = sys_min_dist;                            // 最小距离
    H_BS = sys_H_BS;                                    // 用户天线高度
    H_MT = sys_H_MT;                                    // 用户分布于室内的概率

}
