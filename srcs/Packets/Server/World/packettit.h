#ifndef PACKETTIT_H
#define PACKETTIT_H

#include "srcs/Packets/basepacket.h"

class PacketTit : public BasePacket
{
public:
    PacketTit(QStringList Packet);
    QString getClassName();
    QString getPseudonym();
};

#endif // PACKETTIT_H
