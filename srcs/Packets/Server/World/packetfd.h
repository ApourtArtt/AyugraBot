#ifndef PACKETFD_H
#define PACKETFD_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/reputationenum.h"

class PacketFd : public BasePacket
{
public:
    PacketFd(QStringList Packet);
    int getReputation();
    ReputationIcon getReputationIcon();
    int getDignity();
    DignityIcon getDignityIcon();
};

#endif // PACKETFD_H
