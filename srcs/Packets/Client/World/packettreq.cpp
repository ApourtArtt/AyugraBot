#include "packettreq.h"

PacketTreq::PacketTreq(int X, int Y, bool Enter, bool Record)
    : BasePacket("preq")
{
    x = X;
    y = Y;
    enter = Enter;
    record = Record;
    packet.push_back(QString::number(x));
    packet.push_back(QString::number(y));
    if(enter)
    {
        packet.push_back("1");
        if(record)
            packet.push_back("1");
    }
}

bool PacketTreq::isSendable()
{
    if(packet.size() < 3 || packet.size() > 5)
        return false;
    if(packet.size() == 3 && (enter || record))
        return false;
    if(packet.size() == 4 && (!enter || record))
        return false;
    if(packet.size() == 5 && (!enter || !record))
        return false;
    if(record && !enter)
        return false;
    if(x < 0 || x > 500)
        return false;
    if(y < 0 || y > 500)
        return false;
    return true;
}
