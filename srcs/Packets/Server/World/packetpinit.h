#ifndef PACKETPINIT_H
#define PACKETPINIT_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/characterenum.h"

class PacketSubPinit
{
public:
    PacketSubPinit(QString packet);
    EntityType getEntityType();
    int getEntityID();
    short getGroupPosition();
    short getNormalLevel();
    QString getPseudonym();
    int getGroupID();
    Gender getGender();
    int getMorphID();
    Class getClass();
    short getHeroLevel();
    bool isNosmate();
    bool isPartner();
    // ??

private:
    QStringList packets;
};


class PacketPinit : public BasePacket
{
public:
    PacketPinit(QStringList Packet);
    short getGroupSize();
    std::vector<PacketSubPinit> getSubPackets();
};

#endif // PACKETPINIT_H
