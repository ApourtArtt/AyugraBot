#ifndef PACKETPIDX_H
#define PACKETPIDX_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/characterenum.h"

class PacketSubPidx
{
public:
    PacketSubPidx(QString packet);
    bool isOrWasGrouped();
    int getID();
private:
    QStringList packets;
};

class PacketPidx : BasePacket
{
public:
    PacketPidx(QStringList Packet);
    int getGroupID();
    std::vector<PacketSubPidx> getSubPackets();
};

#endif // PACKETPIDX_H
