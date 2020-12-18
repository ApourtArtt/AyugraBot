#ifndef SKILLENUM_H
#define SKILLENUM_H

enum class SkillTarget
{
    AIMED           = 0,
    SELF            = 1,
    BUFFMONOALLY    = 2,
    SKILLSHOT       = 3,
    SELFNOSMATE     = 4
};

enum class SkillType
{
    PASSIVE         = 0,
    SKILL           = 1,
    IMPROVEMENT     = 2,
    INTERACTION     = 3,
    MONSTER         = 4,
    NOSMATE         = 5
};

#endif // SKILLENUM_H
