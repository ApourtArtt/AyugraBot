#ifndef PORTALENUM_H
#define PORTALENUM_H

enum class PortalType {
    MAP_PORTAL       = -1,
    TS_NORMAL        = 0, // same over >127 - char
    CLOSED           = 1,
    OPEN             = 2,
    MINILAND         = 3,
    TS_END           = 4,
    TS_END_CLOSED    = 5,
    EXIT             = 6,
    EXIT_CLOSED      = 7,
    RAID             = 8,
    EFFECT           = 9, // same as 13 - 19 and 20 - 126
    BLUE_RAID        = 10,
    DARK_RAID        = 11,
    TIMESPACE        = 12,
    SHOP_TELEPORT    = 20
};


#endif // PORTALENUM_H
