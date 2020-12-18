#ifndef PACKETDLGI_H
#define PACKETDLGI_H

#include "srcs/Packets/basepacket.h"

class PacketDlgi : public BasePacket
{
public: // dlgi #revival^0 #revival^1 570 0 0
    PacketDlgi(QStringList Packet);
    QString getPacketToAccept() const;
    QString getPacketToDeny() const;
    int getSentanceID() const;
    int getSentanceFormater() const;
    int getSentanceVariables() const;
};

#endif // PACKETDLGI_H
