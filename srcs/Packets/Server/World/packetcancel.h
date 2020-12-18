#ifndef PACKETCANCEL_H
#define PACKETCANCEL_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/cancelenum.h"

class PacketCancel : public BasePacket
{
public:
    PacketCancel(QStringList Packet);
    CancelType getCancelType();
    int getCancelID();
};

#endif // PACKETCANCEL_H
