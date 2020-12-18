#include "packetsay.h"

PacketSay::PacketSay(QString Message)
    : BasePacket("say")
{
    message = Message;
    packet.push_back(message);
}

bool PacketSay::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(message.size() > 50 || message.isEmpty()) // to check max val
        return false;
    return true;
}
