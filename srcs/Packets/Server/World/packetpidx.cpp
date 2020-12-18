#include "packetpidx.h"

PacketPidx::PacketPidx(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketPidx::getGroupID()
{
    return packet[1].toInt();
}

std::vector<PacketSubPidx> PacketPidx::getSubPackets()
{
    std::vector<PacketSubPidx> packets;
    for(int i = 2 ; i < packet.size() ; i++)
    {
        packets.push_back(PacketSubPidx(packet[2 + i]));
    }
    return packets;
}


PacketSubPidx::PacketSubPidx(QString packet)
{
    packets = packet.split(".");
}

bool PacketSubPidx::isOrWasGrouped()
{
    return packets[0] == "-1" ? false : true;
}

int PacketSubPidx::getID()
{
    return packets[1].toInt();
}
