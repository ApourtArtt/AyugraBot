#ifndef PACKETC_INFO_RESET_H
#define PACKETC_INFO_RESET_H

#include "srcs/Packets/basepacket.h"

class PacketC_info_reset : public BasePacket
{
public:
    PacketC_info_reset(QStringList Packet);
};

#endif // PACKETC_INFO_RESET_H
