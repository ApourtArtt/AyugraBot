#include "packetfd.h"

PacketFd::PacketFd(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketFd::getReputation()
{
    return packet[1].toInt();
}

ReputationIcon PacketFd::getReputationIcon()
{
    return static_cast<ReputationIcon>(packet[2].toInt());
}

int PacketFd::getDignity()
{
    return packet[3].toInt();
}

DignityIcon PacketFd::getDignityIcon()
{
    return static_cast<DignityIcon>(packet[4].toInt());
}
