#include "packetwear.h"
#include <QDebug>

PacketWear::PacketWear(int Slot, short TargetSlot)
    : BasePacket("wear")
{
    slot = Slot;
    targetSlot = TargetSlot;
    packet.push_back(QString::number(slot));
    packet.push_back(QString::number(targetSlot));
}

bool PacketWear::isSendable()
{
    qDebug() << "WP0";
    if(packet.size() != PACKET_SIZE)
        return false;
    qDebug() << "WP1";
    if(slot < 0 || slot > 119)
        return false;
    qDebug() << "WP2";
    if(targetSlot < 0 || targetSlot > 12)
        return false;
    qDebug() << "WP3 (ok)";
    return true;
}
