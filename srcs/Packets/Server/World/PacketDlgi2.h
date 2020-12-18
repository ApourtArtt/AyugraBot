#ifndef PACKETDLGI2_H
#define PACKETDLGI2_H

#include "srcs/Packets/basepacket.h"

class PacketDlgi2 : public BasePacket
{
public: // dlgi2 #pjoin^3^886274 #pjoin^4^886274 233 1 Beijin
    PacketDlgi2(QStringList Packet);
    QString getPacketToAccept() const;
    QString getPacketToDeny() const;
    int getSentanceID() const;
    int getSentanceFormater() const;
    QString getSentanceVariables() const;
};

#endif // PACKETDLGI2_H
