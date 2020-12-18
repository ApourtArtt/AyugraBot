#ifndef PACKETPST_H
#define PACKETPST_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/characterenum.h"

class PacketPst : public BasePacket
{
public:
    PacketPst(QStringList Packet);
    EntityType getEntityType() const;
    int getEntityID() const;
    short getGroupPosition() const;
    short getHPPercent() const;
    short getMPPercent() const;
    int getHP() const;
    int getMP() const;
    Class getClass() const;
    Gender getGender() const;
    int getMorphID() const;
    QVector<QPair<int, int>> getBuffs() const;
};

#endif // PACKETPST_H
