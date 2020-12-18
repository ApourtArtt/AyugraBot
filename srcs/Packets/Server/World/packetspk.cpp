#include "packetspk.h"

PacketSpk::PacketSpk(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketSpk::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketSpk::getEntityID()
{
    return packet[2].toInt();
}

ChatType PacketSpk::getChatType()
{
    return static_cast<ChatType>(packet[3].toInt());
}

QString PacketSpk::getPseudonym()
{
    return packet[4];
}

QString PacketSpk::getMessage()
{
    QStringList message = packet;
    message.erase(message.begin(), message.begin() + 5);
    return message.join(" ");
}
