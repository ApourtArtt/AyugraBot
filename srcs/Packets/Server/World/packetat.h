#ifndef PACKETAT_H
#define PACKETAT_H

#include "srcs/Packets/basepacket.h"

class PacketAt : public BasePacket
{
public:
    PacketAt(QStringList Packet);
    int getCharacterID();
    int getMapID();
    int getPosX();
    int getPosY();
    short getDirection();
    // ?
    int getMusicID();
    // ?
    // ?
};

#endif // PACKETAT_H
