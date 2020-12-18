#include "packetglist.h"

PacketGlist::PacketGlist(short FirstValue, short SecondValue)
    : BasePacket("glist")
{
    firstValue = FirstValue;
    secondValue = SecondValue;
    packet.push_back(QString::number(firstValue));
    packet.push_back(QString::number(secondValue));
}

// Should I list every possibilities ?
bool PacketGlist::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(firstValue == 0 && secondValue == 2)
        return true;
    if(firstValue == 0 && secondValue == 0)
        return true;
    if(firstValue == 2 && secondValue == 0)
        return true;
    return false;
}
// Opening J : glist 0 2, recieve :
// ginfo [FAMILY_NAME] [FAMILY_HEAD] [HEAD_GENDER 0:M 1:F] [FAMILY_LEVEL] [CURRENT_XP] [REQUIRED_XP] [NB_CURRENT_MEMBER] [NB_MAX_MEMBER] [MY_RANG] 0 0 0 0 0 0 0
// MY_RANG : 3:MEMBER 2:GARDIAN 1:DEPUTY 0:HEAD
// End of list :
// [GARDIAN_INVITE] [GARDIAN_AVERT] [GARDIAN_SCREAM] [GARDIAN_HISTO] [SALIM] [MEMBER_HISTO] [SALIM]
// SALIM : 0:NO_RIGHT 1:DEPOSIT 2:DEPOSIT/WITHDRAW

// Opening family management : glist 0 0
// Sending glist 2 0 :
// gmbr 0 804120|18122115|Xastek|63|2|0|0|0|0|0 874831|18122115|Cenopt|56|3|1|0|0|0|1680
// 904508|18122115|HBbetE|55|1|1|0|0|0|0 1540460|19101017|Moquin|18|3|3|0|0|0|672
// 1540462|19101017|Endi$|18|3|3|0|0|0|1152 1540463|19101017|Yennefer|18|2|3|0|0|0|1680
// 1540478|19101017|Baehyun|17|1|3|0|0|0|1704 1535837|19101223|Yaong|50|3|3|0|0|0|1680
// 1535734|19101223|Taehun|50|1|3|0|0|0|1680
// Note that those characters aren't even in my family, so there is a glitch somewhere
