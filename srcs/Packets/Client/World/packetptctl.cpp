#include "packetptctl.h"

PacketPtctl::PacketPtctl(int MapID, int MovingAmount, int EntityID, int X, int Y, short Speed)
    : BasePacket("ptctl")
{
    mapID = MapID;
    movingAmount = MovingAmount;
    entityID = EntityID;
    x = X;
    y = Y;
    speed = Speed;
    packet.push_back(QString::number(mapID));
    packet.push_back(QString::number(movingAmount));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(x));
    packet.push_back(QString::number(y));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(speed));
}

bool PacketPtctl::isSendable()
{
    if(mapID < 0)
        return false;
    if(movingAmount <= 0 || movingAmount > 2)
        return false;
    if(entityID <= 0)
        return false;
    if(x < 0 || x > 300)
        return false;
    if(y < 0 || y > 300)
        return false;
    if(speed < 0 || speed >= 100)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}
