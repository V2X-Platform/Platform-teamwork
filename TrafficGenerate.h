#ifndef TRAFFICGENERATE_H_INCLUDED
#define TRAFFICGENERATE_H_INCLUDED

#pragma once

#include "mt_info.h"

class TRAFFIC_GENERATE
{
private:
	double Alpha;

	double K;

	double M;

public:
	TRAFFIC_GENERATE();

	~TRAFFIC_GENERATE();

	//void Generate_traffic(list<MT_INFO*> &mt_list,double simul_time);

	//void Generate_traffic_fullbuffer(list<MT_INFO*> &mt_list,double simul_time);

	void Generate_traffic_periodic(list<MT_INFO*> &mt_list,double simul_time);

private:

	double Generate_timeinterval();

};

#endif // TRAFFICGENERATE_H_INCLUDED
