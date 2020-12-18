#include "skill.h"
#include <QDebug>

Skill::Skill(int Id)
    : SkillFromDb(Id)
{
    cooldown = false;
    availableAsCombo = false;
}

int Skill::getRemainingCooldown() const
{
    return 0;
}

bool Skill::isUsable() const
{
    if(cooldown)
        return false;
    if(combo && !availableAsCombo)
        return false;
    return true;
}

void Skill::setInCooldow(bool inCooldown)
{
    cooldown = inCooldown;
}

void Skill::setAvailableCombo(bool isAvailable)
{
    availableAsCombo = isAvailable;
}

bool Skill::isAvailableAsCombo() const
{
    return availableAsCombo;
}
