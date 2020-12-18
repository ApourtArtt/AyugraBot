#ifndef PACKETSAYI2_H
#define PACKETSAYI2_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/chatenum.h"

class PacketSayi2 : public BasePacket
{
public:
    PacketSayi2(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    ChatType getChatType();
    int getTextFormat1();
    int getTextFormat2();
    short getChannel();
    QString getPseudonym();
    QString getMessage();
};

#endif // PACKETSAYI2_H
