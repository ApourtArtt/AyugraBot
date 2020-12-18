#ifndef PACKETCLIST_START_H
#define PACKETCLIST_START_H

#include "srcs/Packets/basepacket.h"

class PacketClist_start : public BasePacket
{
public:
    PacketClist_start(QStringList Packet);
    bool isEventOnline();
};

#endif // PACKETCLIST_START_H
