#include "packettit.h"

PacketTit::PacketTit(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketTit::getClassName()
{
    return packet[1];
}

QString PacketTit::getPseudonym()
{
    return packet[2];
}
