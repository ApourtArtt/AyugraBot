#include "packetdlgi.h"

PacketDlgi::PacketDlgi(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketDlgi::getPacketToAccept() const
{
    return packet[1];
}

QString PacketDlgi::getPacketToDeny() const
{
    return packet[2];
}

int PacketDlgi::getSentanceID() const
{
    return packet[3].toInt();
}

int PacketDlgi::getSentanceFormater() const
{
    return packet[4].toInt();
}

int PacketDlgi::getSentanceVariables() const
{
    return packet[5].toInt();
}
