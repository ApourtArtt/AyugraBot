#include "packetpulse.h"

PacketPulse::PacketPulse(int Time, int RandomPart)
    : BasePacket("pulse")
{
    time = Time;
    randomPart = RandomPart;
    packet.push_back(QString::number(time));
    packet.push_back(QString::number(randomPart));
}

bool PacketPulse::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(time % 60 != 0)
        return false;
    if(randomPart != 0 && randomPart != 1)
        return false;
    return true;
}
