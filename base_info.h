#ifndef BASE_INFO_H_INCLUDED
#define BASE_INFO_H_INCLUDED

/*用来存放基站信息的类*/
#include <list>
#include <utility>
#include <iostream>
#include "scenario_para.h"
#include "system_para.h"
#include "gain_info.h"
#include <vector>

using namespace std;

class BASE_INFO
{
public:

    int antnum;
    int RBnum;
    int base_id;
    int antnum_pBS;
    int MT_num;

    double BS_array_broadside;//天线阵列的垂直方向角，范围[180,180)
    double *Theta;//扇区天线相对x正半轴的夹角，范围[180,180)

    pair <double,double> *ant_pos;			//the base ants' position
    pair <double,double> base_pos;			//the base ants' position
    vector<GAIN_INFO*> comm_mt_list;

	double* ant_sendpacketnum;			// ant send packet number

	double* ant_sendblocknum;			// ant send block number

	double* ant_sendbitnum;				// ant send bit number

	//RUNIT_INFO** base_resource;			// the resource unit in the base station

	double sendpacket_num;				// send packet number

	double sendblock_num;				// the send block number;

	double sendbit_num;					// the send bit number

	double discardpacket_num;				// drop packet number

	double discardbit_num;					// the drop bit number

public:
    BASE_INFO(SCENARIO scenario_data,int baseid,pair<double,double> *antpos,double *theta,double array_broadside);

    void Sending_data(double simultime);

    double Get_sendpacketnum();

	double Get_antsendpacketnum(int ant_index);

	double Get_sendblocknum();

	double Get_antsendblocknum(int ant_index);

	double Get_sendbitnum();

	double Get_antsendbitnum(int ant_index);

	double Get_discardpacketnum();

	double Get_discardbitnum();

    BASE_INFO();
    ~BASE_INFO(void);
};

#endif // BASE_INFO_H_INCLUDED
