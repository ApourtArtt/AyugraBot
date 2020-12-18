#ifndef FAILCENUM_H
#define FAILCENUM_H

enum class FailcType {
    NONE                    = 0,
    OLDCLIENT               = 1,
    UNHANDLEDERROR          = 2,
    MAINTENANCE             = 3,
    ALREADYCONNECTED        = 4,
    WRONGCREDENTIALS        = 5,
    CANTCONNECT             = 6,
    BANNED                  = 7,
    WRONGCOUNTRY            = 8,
    WRONGCAPS               = 9
};

#endif // FAILCENUM_H
