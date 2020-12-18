#ifndef PACKETQNAMLI_H
#define PACKETQNAMLI_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/eventenum.h"

//qnamli 1 #guri^506 379 0 0 0
class PacketQnamli : public BasePacket
{
public:
    PacketQnamli(QStringList Packet);
    EventType getEventType();
    QString getResponsePacket();
    // ???
    // ???
    // ???
    // ???
};

#endif // PACKETQNAMLI_H
