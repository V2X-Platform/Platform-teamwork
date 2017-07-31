#ifndef DATASTATISTIC_H_INCLUDED
#define DATASTATISTIC_H_INCLUDED
#include "simulation.h"

//此头文件用来统计的发送数据以及吞吐量数据的收集


void DataStatistic(list<MT_INFO*> &MtList);
void DataStatistic(vector<BASE_INFO*> &BsList);

#endif // DATASTATISTIC_H_INCLUDED
