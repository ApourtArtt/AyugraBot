#ifndef PACKETSUCCESS_H
#define PACKETSUCCESS_H

#include "srcs/Packets/basepacket.h"

class PacketSuccess : public BasePacket
{
public:
    PacketSuccess(QStringList Packet);
};

#endif // PACKETSUCCESS_H
