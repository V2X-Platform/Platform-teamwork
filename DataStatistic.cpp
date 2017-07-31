#include "DataStatistic.h"

void DataStatistic(list<MT_INFO*> &MtList)
{
	list<MT_INFO*>::iterator MtPtr;
	vector<GAIN_INFO*>::iterator PacketPtr;

	for(MtPtr = Mtlist.begin();MtPtr!=Mtlist.end();Mtptr++)
    {
        for(PacketPtr=(*MtPtr)->comm_mt_list.begin();PacketPtr!(*MtPtr)->comm_mt_list.end();PacketPtr++}
        {
            (*MtPtr)->SendBitTotal += (*PacketPtr)PacketSize;
        }
    }
}

void DataStatistic(vector<BASE_INFO*> &BsList)
{
    vector<BASE_INFO*>::iterator BsPtr;
    vector<GAIN_INFO*>::iterator PacketPtr;

    for(BsPtr = BSlist.begin();BsPtr!=BSlist.end();Bsptr++)
    {
        for(PacketPtr=(*Bsptr)->comm_mt_list.begin();PacketPtr!(*BsPtr)->comm_mt_list.end();PacketPtr++}
        {
            (*BsPtr)->SendBitTotal += (*PacketPtr)PacketSize;
        }
    }
}

