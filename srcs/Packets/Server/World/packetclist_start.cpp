#include "packetclist_start.h"

PacketClist_start::PacketClist_start(QStringList Packet)
    : BasePacket((Packet))
{

}

bool PacketClist_start::isEventOnline()
{
    return packet[1] == "0" ? true : false;
}
