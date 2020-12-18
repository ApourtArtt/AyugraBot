#include "nosmateia.h"

NosmateIA::NosmateIA(QObject *parent)
    : QObject(parent)
{
    map = nullptr;
    nosmate = nullptr;
    targetID = -1;
    animationTimer = QDateTime::currentDateTime().addDays(-1);
    aiType = MateAI::D;
}

bool NosmateIA::isNosmateValid()
{
    if(!map || !nosmate)
        return false;
    return true;
}

void NosmateIA::setWorld(Map *Map, MyNosmate *Nosmate)
{
    map = Map;
    nosmate = Nosmate;
    targetID = -1;
}

void NosmateIA::setSkills(QMap<int, UsableSkill> Skills)
{
    skills = Skills;
}

void NosmateIA::compute()
{
    if(nosmate->getStatsProperties().getCurrentHP() == 0)
        return;
    if(shouldRest()) // and no monsters close to Partner
    {
        // rest
        return;
    }
    QPair<UsableSkill*, int> usableSkill = pickSkill();
    UsableSkill *skill = usableSkill.first;
    int range = (usableSkill.first == nullptr) ? nosmate->getRange() : (skill->getSkill()->getSkillTarget() == SkillTarget::AIMED) ? usableSkill.second : -1;
    if(shouldGetNewTarget())
    {
        targetID = getNearestTargetID();
    }
    if(shouldGoToTarget(range))
    {
        if(nosmate->getNosmateState() != NosmateState::RUNNING)
        {
            Monster monster = map->getMonsterList()[targetID];
            nosmate->walk(monster.getX(), monster.getY(), range, false);
        }
    }
    if(shouldAttackTarget(range))
    {
        if(nosmate->canAttack() && QDateTime::currentDateTime() > animationTimer)
        {
            if(skill && skill->getSkill()->isUsable())
            {
                qDebug() << "Nosmate Skill";
                nosmate->useSkill(skill->getSkill(), map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(skill->getSkill()->getAnimationTimeMs() * 5);
            }
            else
            {
                qDebug() << "Nosmate AA";
                nosmate->useSkill(nullptr, map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(nosmate->msBetweenTwoAA() * 2);
            }
        }
    }
}

int NosmateIA::getNearestTargetID()
{
    QMap<int, Monster> monsters = map->getMonsterList();
    QList<int> monstersKeys = monsters.keys();
    double distanceMin = -1.;
    int TargetID = -1;
    for(int i = 0 ; i < monstersKeys.size() ; i++)
    {
        double currentDist = PathFinding::distance({ nosmate->getX(), nosmate->getY() },
                                                   { monsters[monstersKeys[i]].getX(), monsters[monstersKeys[i]].getY() });
        if(currentDist < distanceMin || distanceMin < 0)
        {
            distanceMin = currentDist;
            TargetID = monstersKeys[i];
        }
    }
    return TargetID;
}

bool NosmateIA::shouldRest()
{
    // TODO
/*if(hp > hpMinAuthorized)
    return false
    ...
    ...
return true;*/

    return false;
}

bool NosmateIA::shouldGoToTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() <= range)
        return false;
    return true;
}

bool NosmateIA::shouldAttackTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() > range)
        return false;
    return true;
}

bool NosmateIA::shouldGetNewTarget()
{
    if(nosmate->getNosmateState() == NosmateState::RESTING)
        return false;
    if(map->getMonsterList().contains(targetID))
        return false;
    return true;
}

double NosmateIA::distanceToTarget()
{
    Monster monster = map->getMonsterList()[targetID];
    return PathFinding::distance({ nosmate->getX(), nosmate->getY() }, { monster.getX(), monster.getY() });
}

QPair<UsableSkill*, int> NosmateIA::pickSkill()
{
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        Skill *s = skills[keys[i]].getSkill();
        if(!s || !nosmate)
            continue;
        if(!s->isUsable())
            continue;
        if(nosmate->getStatsProperties().getCurrentMP() < s->getManaCost())
            continue;
        // TODO : add a if(!Partner->getSkillList().contains(s)) continue;
        if(skills[keys[i]].getSecondBetweenCast() > 0)
        {
            if(!skills[keys[i]].isCastablePseudoCooldown())
                continue;
            skills[keys[i]].setPseudoCooldown(QDateTime::currentDateTime());
        }
        return { &skills[keys[i]], skills[keys[i]].getMaxRange() };
    }
    return { nullptr, nosmate->getRange() };
}

void NosmateIA::resetTarget()
{
    targetID = -1;
}

void NosmateIA::setAIType(MateAI AiType)
{
    aiType = AiType;
}

MateAI NosmateIA::getAIType() const
{
    return aiType;
}
