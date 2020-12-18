#include "packetrsfi.h"

PacketRsfi::PacketRsfi(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketRsfi::getQuestAct()
{
    return packet[1].toShort();
}

short PacketRsfi::getQuestPart()
{
    return packet[2].toShort();
}

short PacketRsfi::getTSDone()
{
    return packet[5].toShort();
}

short PacketRsfi::getTSTotal()
{
    return packet[6].toShort();
}
