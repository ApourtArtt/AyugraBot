#ifndef TS_H
#define TS_H

#include "srcs/Packets/Server/World/packetwp.h"

class TS
{
public:
    TS(){}
    TS(PacketWp Packet);
    void handleWpPacket(PacketWp Packet);
    short getX() const;
    short getY() const;
    int getID() const;
    TimeSpaceType getType() const;
    short getLvlMin() const;
    short getLvlMax() const;
    bool isHero() const;
    bool isDone() const;

private:
    short x;
    short y;
    int id;
    TimeSpaceType type;
    short lvlMin;
    short lvlMax;
};

#endif // TS_H
