#include "packetpetski.h"

PacketPetski::PacketPetski(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketPetski::getSkillID()
{
    return packet[1].toInt();
}
