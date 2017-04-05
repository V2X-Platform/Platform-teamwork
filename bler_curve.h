#ifndef BLER_CURVE_H_INCLUDED
#define BLER_CURVE_H_INCLUDED

#pragma once
#include <iostream>
#include <fstream>

class BLER_CURVE
{
public:

	int MCS_max;//最大MCS值，MCS总数

	int *curve_num_RBS_1;//曲线的点数
	int *curve_num_RBS_2;
	int *curve_num_RBS_5;
	int *curve_num_RBS_10;
	int *curve_num_RBS_25;

	//曲线y坐标值
	double **bler_data_RBS_1;
	double **bler_data_RBS_2;
	double **bler_data_RBS_5;
	double **bler_data_RBS_10;
	double **bler_data_RBS_25;

	//曲线的x坐标值
	double **sinr_data_RBS_1;
	double **sinr_data_RBS_2;
	double **sinr_data_RBS_5;
	double **sinr_data_RBS_10;
	double **sinr_data_RBS_25;

public:

	BLER_CURVE(int MCS_MAX);

	~BLER_CURVE(void);

	//读取曲线的值
	double Read_BLER(double sinr,int method,int RBS);//根据sinr及调制编码方式,RB_size读取误帧率

	void Create_CURVE(FILE *stream,int *curve_num,double **sinr_data,double **bler_data);

	int Approximate_RBS(int RBS);
};

#endif // BLER_CURVE_H_INCLUDED
