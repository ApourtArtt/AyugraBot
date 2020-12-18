#ifndef PACKETFAILC_H
#define PACKETFAILC_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/failcenum.h"

class PacketFailc : public BasePacket
{
public:
    PacketFailc(QStringList packet);
    FailcType getErrorType();
};

#endif // PACKETFAILC_H
