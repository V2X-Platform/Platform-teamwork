#pragma once
#include "StdAfx.h"
#include "TranspotBlock.h"

TranspotBlock::TranspotBlock(int paket_i,int TB_i,double gen_time)
{
	paket_id = paket_i;

	TB_id = TB_i;

	TB_size = 0;

	code_rate = 0;

	Modulation = -1;

	Generate_times = gen_time;

	transmit_times = 0;
}

TranspotBlock::TranspotBlock()
{
	paket_id = -1;

	TB_id = -1;

	TB_size = 0;

	code_rate = 0;

	Modulation = -1;

	Generate_times = FALSE_VALUE;

	transmit_times = 0;
}

TranspotBlock::~TranspotBlock()
{
}

void TranspotBlock::Increase_TransTimes()
{
	transmit_times++;
}

int TranspotBlock::Get_TransTimes()
{
	return transmit_times;
}

void TranspotBlock::Clear()
{
	paket_id = -1;

	TB_id = -1;

	TB_size = 0;

	code_rate = 0;

	Modulation = -1;

	Generate_times = FALSE_VALUE;

	transmit_times = 0;
}


void TranspotBlock::Set_MCS(int CQI_index)
{
	if(CQI_index>=1 && CQI_index<=6)
		Modulation = QPSK;
	else if(CQI_index>=7 && CQI_index<=9)
		Modulation = QAM16;
	else if(CQI_index>=10 && CQI_index<=15)
		Modulation = QAM64;
	else //CQI_index==0
		Modulation = 0;

	code_rate = CodeRate[CQI_index];//  Bits_pSymbol[CQI_index]/Modulation;
}


void TranspotBlock::Set_TBsize(int RB_num)
{
	double temp_TBS = RB_num * sys_bindnum * (14-PDCCH_OH) * Modulation * code_rate;

	//在TBS_Table中找出最接近的TBS
	//const int      MCS_Table[29] = {2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,4,6,6,6,6,6,6,6,6,6,6,6,6};
	//const int      I_TBS_Table[29] = {0,1,2,3,4,5,6,7,8,9,9,10,11,12,13,14,15,15,16,17,18,19,20,21,22,23,24,25,26};

	double TBS_difference_min = MAX_VALUE;
	int I_TBS_temp = 0;

	for(int MCS_index=0;MCS_index<29;MCS_index++)
	{
		if(Modulation==MCS_Table[MCS_index])
		{
			//对应的I_TBS
			int I_TBS = I_TBS_Table[MCS_index];

			double TBS_difference = std::abs(temp_TBS - TBSTable[I_TBS][RB_num-1]);

			if(TBS_difference<TBS_difference_min)
			{
				TBS_difference_min = TBS_difference;
				I_TBS_temp = I_TBS;
			}
		}
		else if(Modulation>MCS_Table[MCS_index])
		{
			continue;
		}
		else //Modulation<MCS_Table[MCS_index]
		{
			break;
		}
	}

	TB_size = TBSTable[I_TBS_temp][RB_num-1];
	code_rate = (double)TB_size / (RB_num * sys_bindnum * (14-PDCCH_OH) * Modulation);
}
