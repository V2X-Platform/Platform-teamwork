#include "stdafx.h"
#include "bler_curve.h"
#include "system_para.h"
#include <stdio.h>
#include <fstream>


using namespace std;

BLER_CURVE::BLER_CURVE(int MCS_MAX)
{
	MCS_max = MCS_MAX;

	curve_num_RBS_1 = new int[MCS_max];
	sinr_data_RBS_1 = new double*[MCS_max];
	bler_data_RBS_1 = new double*[MCS_max];

	curve_num_RBS_2 = new int[MCS_max];
	sinr_data_RBS_2 = new double*[MCS_max];
	bler_data_RBS_2 = new double*[MCS_max];

	curve_num_RBS_5 = new int[MCS_max];
	sinr_data_RBS_5 = new double*[MCS_max];
	bler_data_RBS_5 = new double*[MCS_max];

	curve_num_RBS_10 = new int[MCS_max];
	sinr_data_RBS_10 = new double*[MCS_max];
	bler_data_RBS_10 = new double*[MCS_max];

	curve_num_RBS_25 = new int[MCS_max];
	sinr_data_RBS_25 = new double*[MCS_max];
	bler_data_RBS_25 = new double*[MCS_max];


	FILE *stream;

	fopen_s(&stream, "input_data/BLER_CURVE_DATA_RBS_1.txt", "r" );
	Create_CURVE(stream,curve_num_RBS_1,sinr_data_RBS_1,bler_data_RBS_1);
	fclose( stream );

	fopen_s(&stream, "input_data/BLER_CURVE_DATA_RBS_2.txt", "r" );
	Create_CURVE(stream,curve_num_RBS_2,sinr_data_RBS_2,bler_data_RBS_2);
	fclose( stream );

	fopen_s(&stream, "input_data/BLER_CURVE_DATA_RBS_5.txt", "r" );
	Create_CURVE(stream,curve_num_RBS_5,sinr_data_RBS_5,bler_data_RBS_5);
	fclose( stream );

	fopen_s(&stream, "input_data/BLER_CURVE_DATA_RBS_10.txt", "r" );
	Create_CURVE(stream,curve_num_RBS_10,sinr_data_RBS_10,bler_data_RBS_10);
	fclose( stream );

	fopen_s(&stream, "input_data/BLER_CURVE_DATA_RBS_25.txt", "r" );
	Create_CURVE(stream,curve_num_RBS_25,sinr_data_RBS_25,bler_data_RBS_25);
	fclose( stream );

}

BLER_CURVE::~BLER_CURVE()
{
	if(curve_num_RBS_1!=NULL)
	{
		delete [] curve_num_RBS_1;
		curve_num_RBS_1 = NULL;
	}
	if(curve_num_RBS_2!=NULL)
	{
		delete [] curve_num_RBS_2;
		curve_num_RBS_2 = NULL;
	}
	if(curve_num_RBS_5!=NULL)
	{
		delete [] curve_num_RBS_5;
		curve_num_RBS_5 = NULL;
	}
	if(curve_num_RBS_10!=NULL)
	{
		delete [] curve_num_RBS_10;
		curve_num_RBS_10 = NULL;
	}
	if(curve_num_RBS_25!=NULL)
	{
		delete [] curve_num_RBS_25;
		curve_num_RBS_25 = NULL;
	}

	if(sinr_data_RBS_1!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(sinr_data_RBS_1[i]!=NULL)
			{
				delete sinr_data_RBS_1[i];
				sinr_data_RBS_1[i] = NULL;
			}
		}

		delete [] sinr_data_RBS_1;
		sinr_data_RBS_1 = NULL;
	}
	if(sinr_data_RBS_2!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(sinr_data_RBS_2[i]!=NULL)
			{
				delete sinr_data_RBS_2[i];
				sinr_data_RBS_2[i] = NULL;
			}
		}

		delete [] sinr_data_RBS_2;
		sinr_data_RBS_2 = NULL;
	}
	if(sinr_data_RBS_5!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(sinr_data_RBS_5[i]!=NULL)
			{
				delete sinr_data_RBS_5[i];
				sinr_data_RBS_5[i] = NULL;
			}
		}

		delete [] sinr_data_RBS_5;
		sinr_data_RBS_5 = NULL;
	}
	if(sinr_data_RBS_10!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(sinr_data_RBS_10[i]!=NULL)
			{
				delete sinr_data_RBS_10[i];
				sinr_data_RBS_10[i] = NULL;
			}
		}

		delete [] sinr_data_RBS_10;
		sinr_data_RBS_10 = NULL;
	}
	if(sinr_data_RBS_25!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(sinr_data_RBS_25[i]!=NULL)
			{
				delete sinr_data_RBS_25[i];
				sinr_data_RBS_25[i] = NULL;
			}
		}

		delete [] sinr_data_RBS_25;
		sinr_data_RBS_25 = NULL;
	}

	if(bler_data_RBS_1!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(bler_data_RBS_1[i]!=NULL)
			{
				delete bler_data_RBS_1[i];
				bler_data_RBS_1[i] = NULL;
			}
		}

		delete [] bler_data_RBS_1;
		bler_data_RBS_1 = NULL;
	}
	if(bler_data_RBS_2!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(bler_data_RBS_2[i]!=NULL)
			{
				delete bler_data_RBS_2[i];
				bler_data_RBS_2[i] = NULL;
			}
		}

		delete [] bler_data_RBS_2;
		bler_data_RBS_2 = NULL;
	}
	if(bler_data_RBS_5!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(bler_data_RBS_5[i]!=NULL)
			{
				delete bler_data_RBS_5[i];
				bler_data_RBS_5[i] = NULL;
			}
		}

		delete [] bler_data_RBS_5;
		bler_data_RBS_5 = NULL;
	}
	if(bler_data_RBS_10!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(bler_data_RBS_10[i]!=NULL)
			{
				delete bler_data_RBS_10[i];
				bler_data_RBS_10[i] = NULL;
			}
		}

		delete [] bler_data_RBS_10;
		bler_data_RBS_10 = NULL;
	}
	if(bler_data_RBS_25!=NULL)
	{
		for(int i=0;i<MCS_max;i++)
		{
			if(bler_data_RBS_25[i]!=NULL)
			{
				delete bler_data_RBS_25[i];
				bler_data_RBS_25[i] = NULL;
			}
		}

		delete [] bler_data_RBS_25;
		bler_data_RBS_25 = NULL;
	}
}

void BLER_CURVE::Create_CURVE(FILE *stream,int *curve_num,double **sinr_data,double **bler_data)
{
	if( stream == NULL )
	{
		printf( "The file BLER_CURVE_DATA.txt was not opened\n" );
	}
	else
	{
		for(int k=0;k<MCS_max;k++)
		{
			//确定当前MCS曲线的点数
			double temp = 0;
			fscanf_s( stream, "%lg ",&temp);
			curve_num[k] = (int)temp;

			//读取曲线
			if(curve_num[k] != 0)
			{
				sinr_data[k] = new double[curve_num[k]];
				bler_data[k] = new double[curve_num[k]];
			}
			else
			{
				sinr_data[k] = NULL;
				bler_data[k] = NULL;
			}
			for(int i=0; i<curve_num[k];i++)
			{
				fscanf_s( stream, "%lg ",&sinr_data[k][i]);
			}

			for(int i=0; i<curve_num[k];i++)
			{
				fscanf_s( stream, "%lg ",&bler_data[k][i]);
			}
		}
	}

}

double BLER_CURVE::Read_BLER(double sinr,int method,int RBS)
{
	int *curve_num;
	double **sinr_data;
	double **bler_data;

	//确定RBS对应的曲线
	switch(Approximate_RBS(RBS))
	{
	case 1:
		curve_num = curve_num_RBS_1;
		sinr_data = sinr_data_RBS_1;
		bler_data = bler_data_RBS_1;
		break;

	case 2:
		curve_num = curve_num_RBS_2;
		sinr_data = sinr_data_RBS_2;
		bler_data = bler_data_RBS_2;
		break;

	case 5:
		curve_num = curve_num_RBS_5;
		sinr_data = sinr_data_RBS_5;
		bler_data = bler_data_RBS_5;
		break;

	case 10:
		curve_num = curve_num_RBS_10;
		sinr_data = sinr_data_RBS_10;
		bler_data = bler_data_RBS_10;
		break;

	default://case 25
		curve_num = curve_num_RBS_25;
		sinr_data = sinr_data_RBS_25;
		bler_data = bler_data_RBS_25;
	}

	sinr = 10*log10(sinr);

	method = method -1;

	int curvenum = curve_num[method];

	if(sinr>sinr_data[method][curvenum-1])
		return 0;
	else if(sinr<sinr_data[method][0])
		return 1;
	else
	{
		int k=1;

		for(;k<curvenum;k++)
		{
			if(sinr<=sinr_data[method][k])
				break;
		}
		//sinr在sinr_data[method][k-1]与sinr_data[method][k]之间
		return ( (sinr-sinr_data[method][k])*bler_data[method][k-1] - (sinr-sinr_data[method][k-1])*bler_data[method][k] )/(sinr_data[method][k-1]-sinr_data[method][k]);
	}
}

int BLER_CURVE::Select_MCS(double sinr,double BLER_require,int RBS)
{
	int *curve_num;
	double **sinr_data;
	double **bler_data;

	//确定RBS对应的曲线
	switch(Approximate_RBS(RBS))
	{
	case 1:
		curve_num = curve_num_RBS_1;
		sinr_data = sinr_data_RBS_1;
		bler_data = bler_data_RBS_1;
		break;

	case 2:
		curve_num = curve_num_RBS_2;
		sinr_data = sinr_data_RBS_2;
		bler_data = bler_data_RBS_2;
		break;

	case 5:
		curve_num = curve_num_RBS_5;
		sinr_data = sinr_data_RBS_5;
		bler_data = bler_data_RBS_5;
		break;

	case 10:
		curve_num = curve_num_RBS_10;
		sinr_data = sinr_data_RBS_10;
		bler_data = bler_data_RBS_10;
		break;

	default://case 25
		curve_num = curve_num_RBS_25;
		sinr_data = sinr_data_RBS_25;
		bler_data = bler_data_RBS_25;
	}

	/*
	sinr = 10*log10(sinr);

	int MCS = -1;

	for(int mcs=0;mcs<MCS_max;mcs++)
	{
		int curvenum = curve_num[mcs];

		int k_temp = curvenum-1;

		for(int k=curvenum-1;k>=0;k--)
		{
			if(bler_data[mcs][k]<=BER_requirement)
				k_temp = k;
			else
				break;//找到当前mcs下满足系统误码率要求的最小sinr
		}

		if(sinr>=sinr_data[mcs][k_temp])
			MCS = mcs;
		else
			break;//找到当前sinr下满足系统误码率要求的最大mcs
	}

	return MCS+1;
	//*/

	//------------------------------------------------------
	int MCS = 0;

	/* ------------------- Modified by tsing 20110121 ------------------- */
	// 修正原因: mcs的取值范围为[1, 15]，之前是[1, 14]
//	for(int mcs=1;mcs<=MCS_max;mcs++)
	for(int mcs=1;mcs<MCS_max;mcs++)
	{
		double FER_temp = Read_BLER(sinr,mcs,RBS);

		if(FER_temp<=BER_requirement)
		{
			MCS = mcs;
			continue;
		}
		else
		{
			break;
		}
	}

	return MCS;
	//*/------------------------------------------------------
}

int BLER_CURVE::Approximate_RBS(int RBS)
{
	int RB_S;

	if(RBS<=0||RBS>100)
	{
		RB_S = 0;
		cout<<"error in RB size"<<endl;
	}
	else if(RBS==1)
	{
		RB_S = 1;
	}
	else if(RBS>=2 && RBS<=3)
	{
		RB_S = 2;
	}
	else if(RBS>=4 && RBS<=7)
	{
		RB_S = 5;
	}
	else if(RBS>=8 && RBS<=20)
	{
		RB_S = 10;
	}
	else
	{
		RB_S = 25;
	}

	return RB_S;
}
/*
double BLER_CURVE::Cac_eesm_bler(double *sinr_FB,int length,int method,int RB_size)
{
	//求用户全带宽上的指数平均信噪比
	double FER_temp = 1;

	double beta = FORMAT2BETA[method];//根据线性平均求beta值

	int band_num = (int)(length/RB_size);

	double *sinr_temp = new double[band_num];

	for(int band_i=0;band_i<band_num;band_i++)
	{
		sinr_temp[band_i] = 0;

		for(int sub_id=0;sub_id<RB_size;sub_id++)
		{
			sinr_temp[band_i] += exp(-sinr_FB[band_i*RB_size+sub_id]/beta);
		}
		sinr_temp[band_i] =	-beta * log(sinr_temp[band_i] / RB_size);

		FER_temp = FER_temp *  (1-Read_BLER(sinr_temp[band_i],method));
	}
	FER_temp = 1 - FER_temp;

	delete [] sinr_temp;

	return FER_temp;
}
*/
double BLER_CURVE::Read_BLER(double sinr,int method,int RBS)
{
	int *curve_num;
	double **sinr_data;
	double **bler_data;

	//确定RBS对应的曲线
	switch(Approximate_RBS(RBS))
	{
	case 1:
		curve_num = curve_num_RBS_1;
		sinr_data = sinr_data_RBS_1;
		bler_data = bler_data_RBS_1;
		break;

	case 2:
		curve_num = curve_num_RBS_2;
		sinr_data = sinr_data_RBS_2;
		bler_data = bler_data_RBS_2;
		break;

	case 5:
		curve_num = curve_num_RBS_5;
		sinr_data = sinr_data_RBS_5;
		bler_data = bler_data_RBS_5;
		break;

	case 10:
		curve_num = curve_num_RBS_10;
		sinr_data = sinr_data_RBS_10;
		bler_data = bler_data_RBS_10;
		break;

	default://case 25
		curve_num = curve_num_RBS_25;
		sinr_data = sinr_data_RBS_25;
		bler_data = bler_data_RBS_25;
	}

	sinr = 10*log10(sinr);

	method = method -1;

	int curvenum = curve_num[method];

	if(sinr>sinr_data[method][curvenum-1])
		return 0;
	else if(sinr<sinr_data[method][0])
		return 1;
	else
	{
		int k=1;

		for(;k<curvenum;k++)
		{
			if(sinr<=sinr_data[method][k])
				break;
		}
		//sinr在sinr_data[method][k-1]与sinr_data[method][k]之间
		return ( (sinr-sinr_data[method][k])*bler_data[method][k-1] - (sinr-sinr_data[method][k-1])*bler_data[method][k] )/(sinr_data[method][k-1]-sinr_data[method][k]);
	}
}

int BLER_CURVE::Approximate_RBS(int RBS)
{
	int RB_S;

	if(RBS<=0||RBS>100)
	{
		RB_S = 0;
		cout<<"error in RB size"<<endl;
	}
	else if(RBS==1)
	{
		RB_S = 1;
	}
	else if(RBS>=2 && RBS<=3)
	{
		RB_S = 2;
	}
	else if(RBS>=4 && RBS<=7)
	{
		RB_S = 5;
	}
	else if(RBS>=8 && RBS<=20)
	{
		RB_S = 10;
	}
	else
	{
		RB_S = 25;
	}

	return RB_S;
}
