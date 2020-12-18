#include "packetchar_new_job.h"

PacketChar_NEW_JOB::PacketChar_NEW_JOB(QString Pseudonym, short Slot, Gender CharGender, HairStyle Hairstyle, short Haircolor)
    : BasePacket("Char_NEW_JOB")
{
    pseudonym = Pseudonym;
    slot = Slot;
    gender = CharGender;
    hairstyle = Hairstyle;
    haircolor = Haircolor;
    packet.push_back(pseudonym);
    packet.push_back(QString::number(slot));
    packet.push_back(QString::number(static_cast<short>(gender)));
    packet.push_back(QString::number(static_cast<short>(hairstyle)));
    packet.push_back(QString::number(static_cast<short>(haircolor)));
}

bool PacketChar_NEW_JOB::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(pseudonym.size() < 4 || pseudonym.size() > 14)
        return false;
    if(slot != 3)
        return false;
    if(static_cast<short>(hairstyle) < 0 || static_cast<short>(hairstyle) > 2)
        return false;
    if(haircolor < 0 || haircolor > 9)
        return false;
    return true;
}
