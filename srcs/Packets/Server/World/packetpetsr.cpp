#include "packetpetsr.h"

PacketPetsr::PacketPetsr(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketPetsr::getSkillCastID()
{
    return packet[1].toInt();
}
