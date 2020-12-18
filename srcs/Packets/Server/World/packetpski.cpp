#include "packetpski.h"

PacketPski::PacketPski(QStringList Packet)
    : BasePacket(Packet)
{

}

QVector<int> PacketPski::getSkillsID()
{
    QVector<int> skillID;
    for(int i = 1 ; i < packet.size() ; i++)
        skillID.push_back(packet[i].toInt());
    return skillID;
}
