#include "packetdlgi2.h"

PacketDlgi2::PacketDlgi2(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketDlgi2::getPacketToAccept() const
{
    return packet[1];
}

QString PacketDlgi2::getPacketToDeny() const
{
    return packet[2];
}

int PacketDlgi2::getSentanceID() const
{
    return packet[3].toInt();
}

int PacketDlgi2::getSentanceFormater() const
{
    return packet[4].toInt();
}

QString PacketDlgi2::getSentanceVariables() const
{
    return packet[5];
}
