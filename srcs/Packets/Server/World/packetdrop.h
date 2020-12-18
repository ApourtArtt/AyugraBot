#ifndef PACKETDROP_H
#define PACKETDROP_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketDrop : public BasePacket
{
public:
    PacketDrop(QStringList Packet);
    QString getName();
    int getID();
    short getX();
    short getY();
    short getQuantity();
    bool isQuest();
    int getOwnerID();


    EntityType getEntityType(){return EntityType::DROP;}
    short getDir(){return 2;}
};

#endif // PACKETDROP_H
