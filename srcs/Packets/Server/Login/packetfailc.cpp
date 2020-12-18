#include "packetfailc.h"

PacketFailc::PacketFailc(QStringList packet)
    : BasePacket(packet)
{

}

FailcType PacketFailc::getErrorType()
{
    return static_cast<FailcType>(packet[1].toInt());
}
