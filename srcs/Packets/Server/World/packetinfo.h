#ifndef PACKETINFO_H
#define PACKETINFO_H

#include "srcs/Packets/basepacket.h"

class PacketInfo : public BasePacket
{
public:
    PacketInfo(QStringList Packet);
    QString getMessage();
};

#endif // PACKETINFO_H
