#include "packetwreq.h"

PacketWreq::PacketWreq(bool Enter, bool Record)
    : BasePacket("wreq")
{
    enter = Enter;
    record = Record;
    if(enter)
    {
        packet.push_back("1");
        if(record)
            packet.push_back("1");
    }
}

bool PacketWreq::isSendable()
{
    if(packet.size() < 1 || packet.size() > 3)
        return false;
    if(packet.size() == 1 && (enter || record))
        return false;
    if(packet.size() == 2 && (!enter || record))
        return false;
    if(packet.size() == 3 && (!enter || !record))
        return false;
    return true;
}
