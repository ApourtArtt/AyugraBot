#include "packetpinit.h"

PacketPinit::PacketPinit(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketPinit::getGroupSize()
{
    return packet[1].toShort();
}

std::vector<PacketSubPinit> PacketPinit::getSubPackets()
{
    std::vector<PacketSubPinit> packets;
    for(int i = 2 ; i < packet.size() ; i++)
    {
        packets.push_back(PacketSubPinit(packet[i]));
    }
    return packets;
}




PacketSubPinit::PacketSubPinit(QString packet)
{
    packets = packet.split("|");
}

EntityType PacketSubPinit::getEntityType()
{
    return static_cast<EntityType>(packets[0].toInt());
}

int PacketSubPinit::getEntityID()
{
    return packets[1].toInt();
}

short PacketSubPinit::getGroupPosition()
{
    return packets[2].toShort();
}

short PacketSubPinit::getNormalLevel()
{
    return packets[3].toShort();
}

QString PacketSubPinit::getPseudonym()
{
    return packets[4];
}

int PacketSubPinit::getGroupID()
{
    return packets[5].toInt();
}

Gender PacketSubPinit::getGender()
{
    return static_cast<Gender>(packets[6].toInt());
}

int PacketSubPinit::getMorphID()
{
    if(static_cast<EntityType>(packets[0].toInt()) != EntityType::PLAYER)
        return packets[6].toInt();
    else if (packets.size() > 8)
        return packets[8].toInt();
    return 0;
}

Class PacketSubPinit::getClass()
{
    if(packets.size() > 7)
        return static_cast<Class>(packets[7].toInt());
    else
        return Class::ADVENTURER;
}

short PacketSubPinit::getHeroLevel()
{
    if(packets.size() > 9)
        return packets[9].toShort();
    else
        return -1;
}

bool PacketSubPinit::isNosmate()
{
    if(static_cast<EntityType>(packets[0].toInt()) != EntityType::PLAYER)
    {
        if(packets[7].toInt() == 0)
            return true;
    }
    return false;
}

bool PacketSubPinit::isPartner()
{
    if(static_cast<EntityType>(packets[0].toInt()) != EntityType::PLAYER)
    {
        if(packets[7].toInt() == 1)
            return true;
    }
    return false;
}
