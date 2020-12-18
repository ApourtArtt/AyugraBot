#include "packetinfo.h"

PacketInfo::PacketInfo(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketInfo::getMessage()
{
    QStringList tmp = packet;
    tmp.removeFirst();
    return tmp.join(" ");
}
