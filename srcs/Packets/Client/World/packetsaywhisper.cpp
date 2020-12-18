#include "packetsaywhisper.h"

PacketSayWhisper::PacketSayWhisper(QString Pseudonym, QString Message)
    : BasePacket("/")
{
    pseudonym = Pseudonym;
    message = Message;
    packet.push_back(pseudonym);
    packet.push_back(message);
}

bool PacketSayWhisper::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(pseudonym.size() < 4 || pseudonym > 16) // to check : min and max val
        return false;
    if(pseudonym.contains(" "))
        return false;
    if(message.size() > 50) // to check : max val
        return false;
    return true;
}
