#ifndef PACKETSKI_H
#define PACKETSKI_H

#include "srcs/Packets/basepacket.h"

class PacketSki : public BasePacket
{
public:
    PacketSki(QStringList Packet);
    int getSpaceSkillID();
    int getZSkillID();
    QVector<int> getOtherSkillsID();
};

#endif // PACKETSKI_H
