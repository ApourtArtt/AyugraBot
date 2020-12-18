#ifndef ENTITYENUM_H
#define ENTITYENUM_H

enum class EntityType {
    MAP         = 0,
    PLAYER      = 1,
    NOSMATE_NPC = 2,
    MONSTER     = 3,
    DROP        = 9
};

enum class SpawnEffect {
    SUMMON      = 0,
    NO_EFFECT   = 1,
    FALLING     = 2
};

#endif // ENTITYENUM_H
