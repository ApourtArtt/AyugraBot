#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/Server/World/packetmv.h"
#include <QString>
#include <QDebug>

class BaseEntity
{
public:
    BaseEntity(){ x = -1; y = -1; id = -2;}
    template<typename T>
    BaseEntity(T Packet)
    {
        entityType = Packet.getEntityType();
        name = Packet.getName();
        id = Packet.getID();
        x = Packet.getX();
        y = Packet.getY();
        dir = Packet.getDir();
        speed = -1;
    }
    EntityType getEntityType() const {return entityType;}
    QString getName() const
    {
        return name;
    }
    void handleMvPacket(PacketMv Packet)
    {
        x = Packet.getX();
        y = Packet.getY();
        speed = Packet.getSpeed();
    }
    int getID() const {return id;}
    short getX() const {return x;}
    short getY() const {return y;}
    short getDir() const {return dir;}
    short getSpeed() const {return speed;}

protected:
    EntityType entityType;
    QString name;
    int id;
    short x;
    short y;
    short dir;
    short speed;
};

#endif // BASEENTITY_H
