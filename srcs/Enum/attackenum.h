#ifndef ATTACKENUM_H
#define ATTACKENUM_H

enum class HitType {
    HIT_FRIEND          = -2,
    BUFF_FRIEND         = -1,
    NORMAL              = 0,
    MISS_UNUSED         = 1,
    CANCEL              = 2,
    CRIT                = 3,
    MISS                = 4,
    NORMAL_NOT_AIMED    = 5,
    CRIT_NOT_AIMED      = 6
};

enum class DamageType {
    NORMAL = 0,
    PURPLE = 1
};

#endif // ATTACKENUM_H
