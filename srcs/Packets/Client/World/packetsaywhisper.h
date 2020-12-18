#ifndef PACKETSAYWHISPER_H
#define PACKETSAYWHISPER_H

#include "srcs/Packets/basepacket.h"

class PacketSayWhisper : public BasePacket
{
public:
    PacketSayWhisper(QString Pseudonym, QString Message);
    virtual bool isSendable() override;

private:
    QString pseudonym;
    QString message;
    const int PACKET_SIZE = 3;
};

#endif // PACKETSAYWHISPER_H
