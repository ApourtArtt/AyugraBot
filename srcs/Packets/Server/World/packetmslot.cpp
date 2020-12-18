#include "packetmslot.h"

PacketMslot::PacketMslot(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketMslot::getCastID()
{
    return packet[1].toInt();
}

int PacketMslot::getKeybindID()
{
    return packet[2].toInt();
}
