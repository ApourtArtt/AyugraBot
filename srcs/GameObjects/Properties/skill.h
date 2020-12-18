#ifndef SKILL_H
#define SKILL_H

#include "srcs/Database/databaseskill.h"

class Skill : public SkillFromDb
{
public:
    Skill(){}
    Skill(int Id);
    int getRemainingCooldown() const;
    bool isUsable() const;
    void setInCooldow(bool inCooldown);
    void setAvailableCombo(bool isAvailable);
    bool isAvailableAsCombo() const;

    friend bool operator== (const Skill &s1, const Skill &s2)
    {
        return (s1.id == s2.id);
    }

private:
    bool cooldown;
    bool availableAsCombo;
};

#endif // SKILL_H
