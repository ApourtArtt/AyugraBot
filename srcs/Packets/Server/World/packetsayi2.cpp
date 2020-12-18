#include "packetsayi2.h"

PacketSayi2::PacketSayi2(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketSayi2::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketSayi2::getEntityID()
{
    return packet[2].toInt();
}

ChatType PacketSayi2::getChatType()
{
    return static_cast<ChatType>(packet[3].toInt());
}

int PacketSayi2::getTextFormat1()
{
    return packet[4].toInt();
}

int PacketSayi2::getTextFormat2()
{
    return packet[5].toInt();
}

short PacketSayi2::getChannel()
{
    return packet[7].toShort();
}

QString PacketSayi2::getPseudonym()
{
    return packet[8];
}

QString PacketSayi2::getMessage()
{
    QStringList message = packet;
    message.erase(message.begin(), message.begin() + 8);
    return message.join(" ");
}
