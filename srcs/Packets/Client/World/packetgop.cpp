#include "packetgop.h"
#include <QDebug>

PacketGop::PacketGop(BlockingOption option, bool activated)
    : BasePacket("gop")
{
    blockingOption = option;
    isActivated = activated;
    packet.push_back(QString::number(static_cast<int>(blockingOption)));
    packet.push_back(QString::number(isActivated));
}

bool PacketGop::isSendable()
{
    qDebug() << packet;
    if(static_cast<int>(blockingOption) < 0)
        return false;
    qDebug() << "FS";
    if(packet.size() != PACKET_SIZE)
        return false;
    qDebug() << "true";
    return true;
}
