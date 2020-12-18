#ifndef PACKETPSKI_H
#define PACKETPSKI_H

#include "srcs/Packets/basepacket.h"

class PacketPski : public BasePacket
{
public:
    PacketPski(QStringList Packet);
    QVector<int> getSkillsID();
};

#endif // PACKETPSKI_H
