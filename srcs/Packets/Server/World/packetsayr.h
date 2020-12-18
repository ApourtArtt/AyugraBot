#ifndef PACKETSAYR_H
#define PACKETSAYR_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/chatenum.h"

class PacketSayR : public BasePacket
{
public:
    PacketSayR(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    ChatType getChatType();
    QString getMessage();
};
//say 1 728990 31 ooo

#endif // PACKETSAYR_H
