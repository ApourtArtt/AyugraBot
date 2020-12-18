#ifndef PACKETREST_H
#define PACKETREST_H

#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/basepacket.h"

class PacketRest : public BasePacket
{
public:
    PacketRest(int Quantity, QVector<QPair<EntityType, int>> EntityTypeAndID);
    virtual bool isSendable() override;

private:
    int quantity;
    QVector<QPair<EntityType, int>> entityTypeAndID;

    const int PACKET_SIZE = 2;
};

#endif // PACKETREST_H
