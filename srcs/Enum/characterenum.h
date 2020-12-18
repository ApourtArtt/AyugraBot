#ifndef CHARACTERENUM_H
#define CHARACTERENUM_H

enum class Class {
    ADVENTURER      = 0,
    SWORDSMAN       = 1,
    ARCHER          = 2,
    MAGICIAN        = 3,
    MARTIAL_ARTIST  = 4
};

enum class HairStyle {
    HAIRSTYLE_A  = 0,
    HAIRSTYLE_B  = 1,
    HAIRSTYLE_C  = 2,
    HAIRSTYLE_D  = 3,
    NOHAIR       = 4
};

enum class Gender {
    MALE    = 0,
    FEMALE  = 1
};

enum class Authority {
    PLAYER = 0,
    GM = 2
};

#endif // CHARACTERENUM_H
