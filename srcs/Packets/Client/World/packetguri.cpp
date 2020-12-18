#include "packetguri.h"

PacketGuri::PacketGuri(int Type)
    : BasePacket("guri")
{
    type = Type;
    packet.push_back(QString::number(type));
}

PacketGuri::PacketGuri(int Type, EntityType _EntityType, int EntityID, int Timer, int Argument)
    : BasePacket("guri")
{
    type = Type;
    entityType = _EntityType;
    entityID = EntityID;
    timer = Timer;
    argument = Argument;
    packet.push_back(QString::number(type));
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(timer));
    packet.push_back(QString::number(argument));
}

bool PacketGuri::isSendable()
{
    return true;
}
