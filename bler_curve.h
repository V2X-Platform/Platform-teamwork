#ifndef BLER_CURVE_H_INCLUDED
#define BLER_CURVE_H_INCLUDED

#pragma once
#include <iostream>
#include <fstream>

class BLER_CURVE
{
public:

	int MCS_max;//���MCSֵ��MCS����

	int *curve_num_RBS_1;//���ߵĵ���
	int *curve_num_RBS_2;
	int *curve_num_RBS_5;
	int *curve_num_RBS_10;
	int *curve_num_RBS_25;

	//����y����ֵ
	double **bler_data_RBS_1;
	double **bler_data_RBS_2;
	double **bler_data_RBS_5;
	double **bler_data_RBS_10;
	double **bler_data_RBS_25;

	//���ߵ�x����ֵ
	double **sinr_data_RBS_1;
	double **sinr_data_RBS_2;
	double **sinr_data_RBS_5;
	double **sinr_data_RBS_10;
	double **sinr_data_RBS_25;

public:

	BLER_CURVE(int MCS_MAX);

	~BLER_CURVE(void);

	//��ȡ���ߵ�ֵ
	double Read_BLER(double sinr,int method,int RBS);//����sinr�����Ʊ��뷽ʽ,RB_size��ȡ��֡��

	void Create_CURVE(FILE *stream,int *curve_num,double **sinr_data,double **bler_data);

	int Approximate_RBS(int RBS);
};

#endif // BLER_CURVE_H_INCLUDED
