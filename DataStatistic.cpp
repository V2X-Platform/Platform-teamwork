#include "DataStatistic.h"

void DataStatistic(list<MT_INFO*> &MtList)
{
	list<MT_INFO*>::iterator MtPtr;
	vector<GAIN_INFO*>::iterator PacketPtr;

	for(MtPtr = MtList.begin();MtPtr!=MtList.end();MtPtr++)
    {
        for(PacketPtr =(*MtPtr)->comm_mt_list.begin();PacketPtr!=(*MtPtr)->comm_mt_list.end();PacketPtr++)
        {
            (*MtPtr)->SendBitTotal += (*PacketPtr)->PacketSize;
        }
    }
}

void DataStatistic(vector<BASE_INFO*> &BsList)
{
    vector<BASE_INFO*>::iterator BsPtr;
    vector<GAIN_INFO*>::iterator PacketPtr;

    for(BsPtr = BsList.begin();BsPtr!=BsList.end();BsPtr++)
    {
        for(PacketPtr=(*BsPtr)->comm_mt_list.begin();PacketPtr!=(*BsPtr)->comm_mt_list.end();PacketPtr++)
        {
            //(*BsPtr)->SendBitTotal += (*PacketPtr)PacketSize;
        }
    }
}

