#include "packetsayt.h"

PacketSayt::PacketSayt(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketSayt::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketSayt::getEntityID()
{
    return packet[2].toInt();
}

ChatType PacketSayt::getChatType()
{
    return static_cast<ChatType>(packet[3].toInt());
}

QString PacketSayt::getPseudonym()
{
    return packet[4];
}

QString PacketSayt::getMessage()
{
    QStringList message = packet;
    message.erase(message.begin(), message.begin() + 5);
    return message.join(" ");
}
