#ifndef SCENARIO_PARA_H_INCLUDED
#define SCENARIO_PARA_H_INCLUDED


#pragma once
#include "stdafx.h"
#include "system_para.h"
#include <utility>

/*这个类使用来解耦系统固定参数和仿真对象模拟之间*/
class SCENARIO_PARA
{
public:
   	//int sys_scenario;

	//---------------------- System Configuration Parameters ------------------------
	// see M.2135 Table 8-2,4,5
	// System parameter
	double CF;	                    // System main Carrier frequency in Hz
	double BW;                      // FDD system bandwidth

public:
    virtual int get_sectnum_pBS()=0;
    virtual int get_antnum_pBS()=0;
    virtual int get_basenum()=0;
    virtual int get_ISD()=0;
    virtual int get_antnumtotal()=0;
    virtual pair<double,double>* get_base_vect()=0;
    virtual pair<double,double>* get_area_vect()=0;
    virtual double get_H_MT()=0;
    virtual double get_H_BS()=0;
    virtual double get_arealength()=0;
    virtual double get_areawidth()=0;
    virtual int get_mt_perline()=0;
    virtual int get_line_nums()=0;
    virtual int get_MT_num()=0;
    virtual int get_cell_mt_num()=0;
    virtual int get_area_num()=0;
    virtual double get_BS_Txpower()=0;
    virtual double get_MT_Txpower()=0;
    virtual double get_BS_antgain()=0;
    virtual double get_MT_antgain()=0;
    virtual double get_BS_noise_fig()=0;
    virtual double get_BS_feed_loss()=0;
    virtual double get_MT_noise_fig()=0;
    virtual double get_MT_feed_loss()=0;
    virtual double get_MT_vmean()=0;
    virtual double get_Min_dist()=0;
    virtual double get_BS_boresight_gain()=0;
    virtual double get_MT_boresight_gain()=0;

    pair <double,double> xuanzhuan(pair <double,double>,pair <double,double>);

	//------------------------------------------------------------------------------------
public:
	SCENARIO_PARA(int data);                    //构造函数；
	virtual ~SCENARIO_PARA()=0;                 //析构函数；
};


class SCENARIO_FREEWAY :public SCENARIO_PARA
{
public:

	int    sectnum_pBS;
	int    antnum_pBS;
	int    antnum;         		    // Base Station distributed antenna Number
	int    basenum;			        // Base station number
	int    antnumtotal;
	int    area_num;                // area 数量

	int    mt_perline;              //每个道路上的用户数量
	int    line_nums;               //道路数量
	int    MT_num;                  // 总用户数量

	//for Freeway case
	double Freeway_arealength;      //高速路的长
	double Freeway_areawidth ;      //高速路的宽

	// BS & MT parameter
    int cell_mt_num;

	double ISD;                     // inter-site distance
	double BS_Txpower;
	double BS_Power;                // Base power mW
	double BS_antgain;              //dBi
    double MT_Txpower;
	double MT_Power;
	double MT_antgain;              //dBi
	double Min_dist;
	double BS_noise_fig;
	double BS_recv_noise;
	double BS_feed_loss;
    double MT_noise_fig;
	double MT_recv_noise;
	double MT_feed_loss;
	double MT_vmean;
	double BS_boresight_gain;
    double MT_boresight_gain;


	double H_BS;
    double H_MT;


	pair<double,double> *base_vect=new pair<double,double>[2];
	pair<double,double> *area_vect=new pair<double,double>[7];

	//------------------------------------------------------------------------------------
public:
	SCENARIO_FREEWAY(int data);             //构造函数
	~SCENARIO_FREEWAY(void);                //析构函数

    virtual int get_sectnum_pBS();
    virtual int get_antnum_pBS();
    virtual int get_basenum();
    virtual int get_ISD();
    virtual int get_antnumtotal();
    virtual pair<double,double>* get_base_vect();
    virtual pair<double,double>* get_area_vect();
    virtual double get_H_MT();
    virtual double get_H_BS();
    virtual double get_arealength();
    virtual double get_areawidth();
    virtual int get_mt_perline();
    virtual int get_line_nums();
    virtual int get_MT_num();
    virtual int get_cell_mt_num();
    virtual int get_area_num();
    virtual double get_BS_Txpower();
    virtual double get_MT_Txpower();
    virtual double get_BS_antgain();
    virtual double get_MT_antgain();
    virtual double get_BS_noise_fig();
    virtual double get_BS_feed_loss();
    virtual double get_MT_noise_fig();
    virtual double get_MT_feed_loss();
    virtual double get_MT_vmean();
    virtual double get_Min_dist();
    virtual double get_BS_boresight_gain();
    virtual double get_MT_boresight_gain();

};

class SCENARIO
{
   public:

    double CF;
    double BW;
	int    sectnum_pBS;
	int    antnum_pBS;
	int    antnum;         		    // Base Station distributed antenna Number
	int    basenum;			        // Base station number
	int    antnumtotal;
	int    area_num;                // area 数量

	int    mt_perline;              //每个道路上的用户数量
	int    line_nums;               //道路数量
	int    MT_num;                  // 总用户数量

	//for Freeway case
	double Freeway_arealength;      //高速路的长
	double Freeway_areawidth ;      //高速路的宽

	// BS & MT parameter
    int cell_mt_num;

	double ISD;                     // inter-site distance
	double BS_Txpower;
	double BS_Power;                // Base power mW
	double BS_antgain;              //dBi
    double MT_Txpower;
	double MT_Power;
	double MT_antgain;              //dBi
	double Min_dist;
	double BS_noise_fig;
	double BS_recv_noise;
	double BS_feed_loss;
    double MT_noise_fig;
	double MT_recv_noise;
	double MT_feed_loss;
	double MT_vmean;
	double H_BS;
    double H_MT;
    double BS_boresight_gain;
    double MT_boresight_gain;


	pair<double,double> *base_vect;
	pair<double,double> *area_vect;
public:
    SCENARIO(SCENARIO_PARA* scenario_data);                    //构造函数；
	~SCENARIO(void){}                                          //析构函数；
};
#endif // SCENARIO_H_INCLUDED
