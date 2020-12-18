#include "packetcancel.h"

PacketCancel::PacketCancel(QStringList Packet)
    : BasePacket(Packet)
{

}

CancelType PacketCancel::getCancelType()
{
    return static_cast<CancelType>(packet[1].toInt());
}

int PacketCancel::getCancelID()
{
    return packet[2].toInt();
}
