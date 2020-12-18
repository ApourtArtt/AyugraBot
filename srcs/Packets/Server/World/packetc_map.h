#ifndef PACKETC_MAP_H
#define PACKETC_MAP_H

#include "srcs/Packets/basepacket.h"

class PacketC_map : public BasePacket
{
public:
    PacketC_map(QStringList Packet);
    // ???
    int getMapID();
    bool isGoingTo();
};

#endif // PACKETC_MAP_H
