#ifndef PACKETCHAR_NEW_H
#define PACKETCHAR_NEW_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/characterenum.h"

class PacketChar_NEW : public BasePacket
{
public:
    PacketChar_NEW(QString Pseudonym, short Slot, Gender CharGender, HairStyle Hairstyle, short Haircolor);
    virtual bool isSendable() override;

private:
    QString pseudonym;
    short slot;
    Gender gender;
    HairStyle hairstyle;
    short haircolor;
    const int PACKET_SIZE = 6;
};

#endif // PACKETCHAR_NEW_H
