#include "packetesf.h"

PacketEsf::PacketEsf(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketEsf::getID()
{
    return packet[1].toInt();
}
