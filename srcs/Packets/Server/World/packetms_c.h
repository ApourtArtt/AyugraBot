#ifndef PACKETMS_C_H
#define PACKETMS_C_H

#include "srcs/Packets/basepacket.h"

class PacketMs_c : public BasePacket
{
public:
    PacketMs_c(QStringList Packet);
    // ? The argument is unknown
};

#endif // PACKETMS_C_H
