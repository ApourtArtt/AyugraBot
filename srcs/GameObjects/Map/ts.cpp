#include "ts.h"

TS::TS(PacketWp Packet)
{
    handleWpPacket(Packet);
}

void TS::handleWpPacket(PacketWp Packet)
{
    x = Packet.getX();
    y = Packet.getY();
    id = Packet.getID();
    type = Packet.getType();
    lvlMax = Packet.getLvlMax();
    lvlMin = Packet.getLvlMin();
}

short TS::getX() const
{
    return x;
}

short TS::getY() const
{
    return y;
}

int TS::getID() const
{
    return id;
}

TimeSpaceType TS::getType() const
{
    return type;
}

short TS::getLvlMin() const
{
    return lvlMin;
}

short TS::getLvlMax() const
{
    return lvlMax;
}

bool TS::isHero() const
{
    return type == TimeSpaceType::HERO ? true : false;
}

bool TS::isDone() const
{
    return type == TimeSpaceType::DONE ? true : false;
}
