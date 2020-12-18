#include "packetski.h"

PacketSki::PacketSki(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketSki::getSpaceSkillID()
{
    return packet.size() > 1 ? packet[1].toInt() : -1;
}

int PacketSki::getZSkillID()
{
    return packet.size() > 2 ? packet[2].toInt() : -1;
}

QVector<int> PacketSki::getOtherSkillsID()
{
    QVector<int> skillsID;
    for(int i = 3 ; i < packet.size() ; i++)
        skillsID.push_back(packet[i].toInt());
    return skillsID;
}
