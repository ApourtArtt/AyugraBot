#ifndef PACKETSAYT_H
#define PACKETSAYT_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/chatenum.h"

class PacketSayt : public BasePacket
{
public:
    PacketSayt(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    ChatType getChatType();
    QString getPseudonym();
    QString getMessage();
};

#endif // PACKETSAYT_H
