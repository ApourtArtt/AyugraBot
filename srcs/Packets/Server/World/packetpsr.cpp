#include "packetpsr.h"

PacketPsr::PacketPsr(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketPsr::getSkillCastID() const
{
    return packet[1].toInt();
}
