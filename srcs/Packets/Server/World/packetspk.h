#ifndef PACKETSPK_H
#define PACKETSPK_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/chatenum.h"

class PacketSpk : public BasePacket
{
public:
    PacketSpk(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    ChatType getChatType();
    QString getPseudonym();
    QString getMessage();
};

#endif // PACKETSPK_H
