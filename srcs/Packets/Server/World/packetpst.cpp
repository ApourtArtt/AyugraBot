#include "packetpst.h"

PacketPst::PacketPst(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketPst::getEntityType() const
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketPst::getEntityID() const
{
    return packet[2].toInt();
}

short PacketPst::getGroupPosition() const
{
    return packet[3].toShort();
}

short PacketPst::getHPPercent() const
{
    return packet[4].toShort();
}

short PacketPst::getMPPercent() const
{
    return packet[5].toShort();
}

int PacketPst::getHP() const
{
    return packet[6].toInt();
}

int PacketPst::getMP() const
{
    return packet[7].toInt();
}

Class PacketPst::getClass() const
{
    return static_cast<Class>(packet[8].toInt());
}

Gender PacketPst::getGender() const
{
    return static_cast<Gender>(packet[9].toInt());
}

int PacketPst::getMorphID() const
{
    return packet[10].toInt();
}

QVector<QPair<int, int> > PacketPst::getBuffs() const
{
    QVector<QPair<int, int>> buffs;
    for(int i = 11 ; i < packet.size() ; i++)
        buffs.push_back({ packet[i].split(".")[0].toInt(), packet[i].split(".")[1].toInt() });
    return buffs;
}
