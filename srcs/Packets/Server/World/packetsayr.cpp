#include "packetsayr.h"

PacketSayR::PacketSayR(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketSayR::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketSayR::getEntityID()
{
    return packet[2].toInt();
}

ChatType PacketSayR::getChatType()
{
    return static_cast<ChatType>(packet[3].toInt());
}

QString PacketSayR::getMessage()
{
    QStringList message = packet;
    message.erase(message.begin(), message.begin() + 4);
    return message.join(" ");
}
