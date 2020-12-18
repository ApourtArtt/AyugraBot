#include "packetwalk.h"

PacketWalk::PacketWalk(int X, int Y, int Check, short Speed)
    : BasePacket("walk")
{
    x = X;
    y = Y;
    check = Check;
    speed = Speed;
    packet.push_back(QString::number(x));
    packet.push_back(QString::number(y));
    packet.push_back(QString::number(check));
    packet.push_back(QString::number(speed));
}

bool PacketWalk::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(check != ((x + y) % 3) % 2)
        return false;
    if (x < 0 || y < 0) // No > 300 because a map could in the future be larger
        return false;
    if(speed < 0) // Same here, no check on max speed (50 currently)
        return false;
    return true;
}
