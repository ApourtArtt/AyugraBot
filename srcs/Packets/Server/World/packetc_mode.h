#ifndef PACKETC_MODE_H
#define PACKETC_MODE_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/wingsenum.h"
#include "srcs/Enum/entityenum.h"

class PacketC_mode : public BasePacket
{
public:
    PacketC_mode(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    int getMorphID();
    short getSPUpgrade();
    Wings getWingsType();
    bool isADMWinner();
    short getSize();
    // ???
};

#endif // PACKETC_MODE_H

/* c'est un int donc ici int lui ne le sera pas tu verras
 * // 0 1                       2    3      4   5          6      7   8
c_mode type (joueur, mob, etc) id morphid +sp typeaile winneradm size ?
c_mode 1                   215140    5     15   1          1       10  ?
*/
