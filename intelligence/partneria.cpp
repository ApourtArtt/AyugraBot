#include "partneria.h"

PartnerIA::PartnerIA(QObject *parent)
    : QObject(parent)
{
    map = nullptr;
    partner = nullptr;
    targetID = -1;
    animationTimer = QDateTime::currentDateTime().addDays(-1);
    aiType = MateAI::D;
    forceResting = false;
}

bool PartnerIA::isPartnerValid()
{
    if(!map || !partner)
        return false;
    return true;
}

void PartnerIA::setWorld(Map *Map, MyPartner *Partner)
{
    map = Map;
    partner = Partner;
    targetID = -1;
}

void PartnerIA::setSkills(QMap<int, UsableSkill> Skills)
{
    skills = Skills;
}

void PartnerIA::compute()
{
    if(!isPartnerValid() || !partner->isAlive())
        return;
    if(aiType == MateAI::A)
    {
        Compute_A();
    }
    else if(aiType == MateAI::D)
    {
        Compute_D();
    }
    else if(aiType == MateAI::S)
    {
        Compute_S();
    }
    else if(aiType == MateAI::SDS)
    {

    }
    else if(aiType == MateAI::SDR)
    {

    }

    /*
    if(shouldRest()) // and no monsters close to Partner
    {
        // rest
        return;
    }
    QPair<UsableSkill*, int> usableSkill = pickSkill();
    UsableSkill *skill = usableSkill.first;
    int range = (usableSkill.first == nullptr) ? partner->getRange() : (skill->getSkill()->getSkillTarget() == SkillTarget::AIMED) ? usableSkill.second : -1;
    if(shouldGetNewTarget())
    {
        targetID = getNearestTargetID();
    }
    if(shouldGoToTarget(range))
    {
        if(partner->getPartnerState() != PartnerState::RUNNING)
        {
            Monster monster = map->getMonsterList()[targetID];
            partner->walk(monster.getX(), monster.getY(), range, false);
        }
    }
    if(shouldAttackTarget(range))
    {
        if(partner->canAttack() && QDateTime::currentDateTime() > animationTimer)
        {
            if(skill && skill->getSkill()->isUsable())
            {
                partner->useSkill(skill->getSkill(), map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(skill->getSkill()->getAnimationTimeMs() * 5);
            }
            else
            {
                partner->useSkill(nullptr, map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(partner->msBetweenTwoAA() * 2);
            }
        }
    }*/
}

int PartnerIA::getNearestTargetID()
{
    QMap<int, Monster> monsters = map->getMonsterList();
    QList<int> monstersKeys = monsters.keys();
    double distanceMin = -1.;
    int TargetID = -1;
    for(int i = 0 ; i < monstersKeys.size() ; i++)
    {
        double currentDist = PathFinding::distance({ partner->getX(), partner->getY() },
                                                   { monsters[monstersKeys[i]].getX(), monsters[monstersKeys[i]].getY() });
        if(currentDist < distanceMin || distanceMin < 0)
        {
            distanceMin = currentDist;
            TargetID = monstersKeys[i];
        }
    }
    return TargetID;
}

bool PartnerIA::shouldRest()
{
    if(aiType != MateAI::A && forceResting)
        return true;
    return false;
}

bool PartnerIA::shouldGoToTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() <= range)
        return false;
    return true;
}

bool PartnerIA::shouldAttackTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() > range)
        return false;
    return true;
}

bool PartnerIA::shouldGetNewTarget()
{
    if(partner->getPartnerState() == PartnerState::RESTING)
        return false;
    if(map->getMonsterList().contains(targetID))
        return false;
    return true;
}

double PartnerIA::distanceToTarget()
{
    Monster monster = map->getMonsterList()[targetID];
    return PathFinding::distance({ partner->getX(), partner->getY() }, { monster.getX(), monster.getY() });
}

QPair<UsableSkill*, int> PartnerIA::pickSkill()
{
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        Skill *s = skills[keys[i]].getSkill();
        if(!s || !partner)
            continue;
        if(!s->isUsable())
            continue;
        if(partner->getStatsProperties().getCurrentMP() < s->getManaCost())
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
    return { nullptr, partner->getRange() };
}

void PartnerIA::rest()
{

}

void PartnerIA::Compute_A()
{
    if(shouldRest())
        // Check for closed agressive or agrod monsters
        // and finish through hp (need it in behaviourwidget)
    {
        rest();
        return;
    }
    QPair<UsableSkill*, int> usableSkill = pickSkill();
    UsableSkill *skill = usableSkill.first;
    int range = (usableSkill.first == nullptr) ? partner->getRange() : (skill->getSkill()->getSkillTarget() == SkillTarget::AIMED) ? usableSkill.second : -1;
    if(shouldGetNewTarget())
    {
        targetID = getNearestTargetID();
    }
    if(shouldGoToTarget(range))
    {
        if(partner->getPartnerState() != PartnerState::RUNNING)
        {
            Monster monster = map->getMonsterList()[targetID];
            partner->walk(monster.getX(), monster.getY(), range, false);
        }
    }
    if(shouldAttackTarget(range))
    {
        if(partner->canAttack() && QDateTime::currentDateTime() > animationTimer)
        {
            if(skill && skill->getSkill()->isUsable())
            {
                partner->useSkill(skill->getSkill(), map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(skill->getSkill()->getAnimationTimeMs() * 5);
            }
            else
            {
                partner->useSkill(nullptr, map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(partner->msBetweenTwoAA() * 2);
            }
        }
    }
}

void PartnerIA::Compute_D()
{
    if(shouldRest())
        // Check for closed agressive or agrod monsters
        // and finish through hp (need it in behaviourwidget)
        // forceResting...
    {
        rest();
        return;
    }
    QPair<UsableSkill*, int> usableSkill = pickSkill();
    UsableSkill *skill = usableSkill.first;
    int range = (usableSkill.first == nullptr) ? partner->getRange() : (skill->getSkill()->getSkillTarget() == SkillTarget::AIMED) ? usableSkill.second : -1;
    if(shouldGetNewTarget())
    {
        return;
    }
    if(shouldGoToTarget(range))
    {
        if(partner->getPartnerState() != PartnerState::RUNNING)
        {
            Monster monster = map->getMonsterList()[targetID];
            partner->walk(monster.getX(), monster.getY(), range, false);
        }
    }
    if(shouldAttackTarget(range))
    {
        if(partner->canAttack() && QDateTime::currentDateTime() > animationTimer)
        {
            if(skill && skill->getSkill()->isUsable())
            {
                partner->useSkill(skill->getSkill(), map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(skill->getSkill()->getAnimationTimeMs() * 5);
            }
            else
            {
                partner->useSkill(nullptr, map->getMonsterList()[targetID]);
                animationTimer = QDateTime::currentDateTime().addMSecs(partner->msBetweenTwoAA() * 2);
            }
        }
    }
}

void PartnerIA::Compute_S()
{
    if(shouldRest())
    {
        rest();
        return;
    }
}

void PartnerIA::resetTarget()
{
    targetID = -1;
}

void PartnerIA::setAIType(MateAI AiType)
{
    aiType = AiType;
}

void PartnerIA::setResting(bool value)
{
    forceResting = value;
}

void PartnerIA::setTargetID(int value)
{
    targetID = -1;
}

MateAI PartnerIA::getAIType() const
{
    return aiType;
}
