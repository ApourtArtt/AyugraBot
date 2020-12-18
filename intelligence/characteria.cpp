#include "characteria.h"

CharacterIA::CharacterIA(QObject *parent)
    : QObject(parent)
{
    map = nullptr;
    character = nullptr;
    targetID = -1;
    dropID = -1;
    animationTimer = QDateTime::currentDateTime().addDays(-1);
    mListType = MonsterListType::BLACKLIST;
    dListType = DropListType::BLACKLIST;
    pathingType = PathingType::FREE;
    partnerAI = MateAI::S;
    petAI = MateAI::S;
    petCoord = { -1, -1 };
    partnerCoord = { -1, -1 };
    hpPercent = 20;
    hpPercentGetUp = 100;
    mpPercent = 20;
    mpPercentGetUp = 100;
    dropDetectionRange = 15;
}

bool CharacterIA::isCharacterValid()
{
    if(!map || !character)
        return false;
    return true;
}

void CharacterIA::setWorld(Map *Map, MyCharacter *Character)
{
    map = Map;
    character = Character;
    targetID = -1;
}

void CharacterIA::setSkills(QMap<int, UsableSkill> Skills)
{
    skills = Skills;
    QList<int> keys = skills.keys();
    qDebug() << keys;
    for(int i = 0 ; i < keys.size() ; i++)
    {
        qDebug() << i << " : " << keys[i] << skills[keys[i]].getSkill()->getName();
    }
}

void CharacterIA::setFilter(QList<int> MonstersID, MonsterListType ListType)
{
    monstersID = MonstersID;
    mListType = ListType;
}

void CharacterIA::setFilter(QList<int> DropsID, DropListType ListType)
{
    dropsID = DropsID;
    dListType = ListType;
}

void CharacterIA::setPathing(PathingType PathingType, QPair<int, int> Arg1, QVector<QPair<int, int> > Arg2)
{
    pathingType = PathingType;
    pathingArg1 = Arg1;
    pathingArg2 = Arg2;
}

void CharacterIA::compute()
{
    if(!isCharacterValid() || !character->isAlive())
        return;
    /*mini land */
    if(rest() || character->getState() == CharacterState::RESTING)
        return;
    if(drop())
        return;
    if(farm())
        return;
}

int CharacterIA::getNearestTargetID()
{
    QMap<int, Monster> monsters = map->getMonsterList();
    QList<int> monstersKeys = monsters.keys();
    double distanceMin = -1.;
    int TargetID = -1;
    for(int i = 0 ; i < monstersKeys.size() ; i++)
    {
        if((monstersID.contains(monsters[monstersKeys[i]].getName().toInt()) && mListType == MonsterListType::BLACKLIST)
        ||(!monstersID.contains(monsters[monstersKeys[i]].getName().toInt()) && mListType == MonsterListType::WHITELIST))
            continue;
        int mobX = monsters[monstersKeys[i]].getX();
        int mobY = monsters[monstersKeys[i]].getY();
        double currentDist = PathFinding::distance({ character->getX(), character->getY() }, { mobX, mobY });
        if(shouldConsiderMonster(mobX, mobY))
        {
            if(currentDist < distanceMin || distanceMin < 0)
            {
                distanceMin = currentDist;
                TargetID = monstersKeys[i];
            }
        }
    }
    // emit targetID for partner and pet
    // so that if they're in D, they will be able
    // to attack it
    return TargetID;
}

Drop CharacterIA::getNearestDrop()
{
    QMap<int, Drop> drops = map->getDropList();
    QList<int> keys = drops.keys();
    Drop d;
    double dist = -1.;
    for(int i = 0 ; i < drops.size() ; i++)
    {
        qDebug() << (dropsID.contains(drops[keys[i]].getName().toInt() && dListType == DropListType::BLACKLIST));
        qDebug() << (!dropsID.contains(drops[keys[i]].getName().toInt() && dListType == DropListType::WHITELIST));
        qDebug() << dropsID;
        if((dropsID.contains(drops[keys[i]].getName().toInt()) && dListType == DropListType::BLACKLIST)
        ||(!dropsID.contains(drops[keys[i]].getName().toInt()) && dListType == DropListType::WHITELIST))
            continue;
        qDebug() << character->getX() << character->getY() << drops[keys[i]].getX() << drops[keys[i]].getY();
        double currentDist = PathFinding::distance({ character->getX(), character->getY() }, { drops[keys[i]].getX(), drops[keys[i]].getY() });
        qDebug() << currentDist << dropDetectionRange;
        if(currentDist > dropDetectionRange)
            continue;
        if(currentDist < dist || dist < 0)
        {
            if(drops[keys[i]].getOwnerID() == character->getCharacterID() || drops[keys[i]].isPublic())
            {
                d = drops[keys[i]];
                dist = currentDist;
                dropID = drops[keys[i]].getID();
            }
        }
    }
    return d;
}

bool CharacterIA::shouldDrop()
{
    if(checkForAgroedMonster(30) != -1)
        return false;
    if(map->getDropList().size() == 0)
        return false;
    return true;
}

bool CharacterIA::drop()
{
    if(!shouldDrop())
    {
        if(dropID != -1)
        {
            dropID = -1;
            character->stopMoving();
            animationTimer = QDateTime::currentDateTime().addMSecs(400);
        }
        return false;
    }
    qDebug() << "Should Drop";
    Drop drop;
    // add distance condition in the condition V
    if(dropID != -1 && map->getDropList().contains(dropID) &&
       PathFinding::distance({ character->getX(), character->getY() }, { map->getDropList()[dropID].getX(), map->getDropList()[dropID].getY() }) <= dropDetectionRange)
    {
        drop = map->getDropList()[dropID];
    }
    else
    {
        dropID = -1;
        drop = getNearestDrop();
    }
    qDebug() << "DropId : " << dropID << "Drop name : " << drop.getName();
    if(drop.getID() == -2 || drop.getX() == -1 || drop.getY() == -1)
    {
        qDebug() << "Drop pas valide";
        return false;
    }
    if(PathFinding::distance({ character->getX(), character->getY() }, { drop.getX(), drop.getY() }) >= 2)
    {
        if(character->getState() != CharacterState::RUNNING && (character->canMove() && QDateTime::currentDateTime() > animationTimer))
        {
            character->walk(drop.getX(), drop.getY(), 1.5);
            targetID = -1;
            return true;
        }
    }
    else
    {
        animationTimer = QDateTime::currentDateTime().addMSecs(200);
        character->drop(drop, 1.5, false, true);
    }
    return true;
}

bool CharacterIA::farm()
{
    if(shouldGetNewTarget())
        targetID = getNearestTargetID();
    QPair<UsableSkill, int> usableSkill = pickSkill();
    UsableSkill skill = usableSkill.first;
    if(skill.getSkill() == nullptr)
        return false;
    int range = (skill.getSkill()->getSkillTarget() == SkillTarget::AIMED || skill.getSkill()->getSkillTarget() == SkillTarget::SKILLSHOT)
            ? usableSkill.second : -1;
    if(shouldGoToTarget(range) && targetID != -1)
    {
        if(character->getState() != CharacterState::RUNNING
        && (character->canMove() && QDateTime::currentDateTime() > animationTimer))
        {
            Monster monster = map->getMonsterList()[targetID];
            character->walk(monster.getX(), monster.getY(), range);
            return true;
        }
    }
    if(shouldAttackTarget(range) && targetID != -1)
    {
        if(character->canAttack() && QDateTime::currentDateTime() > animationTimer)
        {
            if(skill.getSkill()->isUsable())
            {
                character->useSkill(skill.getSkill(), map->getMonsterList()[targetID]);
                int time = skill.getSkill()->getAnimationTimeMs();
                if(time == 0) time = 800;
                animationTimer = QDateTime::currentDateTime().addMSecs(time);
                return true;
            }
        }
    }
    return false;
}

bool CharacterIA::shouldGoToTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() <= range + 0.5)
        return false;
    return true;
}

bool CharacterIA::shouldAttackTarget(int range)
{
    if(targetID == -1)
        return false;
    if(range != -1 && distanceToTarget() > range + 0.5)
        return false;
    return true;
}

bool CharacterIA::shouldGetNewTarget()
{
    if(character->getState() == CharacterState::RESTING)
        return false;
    if(map->getMonsterList().contains(targetID))
        return false;
    return true;
}

bool CharacterIA::shouldConsiderMonster(int mobX, int mobY)
{
    if(pathingType == PathingType::FREE)
        return true;
    if(pathingType == PathingType::CLOSEST && pathingArg2.size() >= 1
    && PathFinding::distance({ pathingArg1.first, pathingArg1.second }, { mobX, mobY }) <= pathingArg2[0].first)
        return true;
    return false;
}

double CharacterIA::distanceToTarget()
{
    Monster monster = map->getMonsterList()[targetID];
    return PathFinding::distance({ character->getX(), character->getY() }, { monster.getX(), monster.getY() });
}

QPair<UsableSkill, int> CharacterIA::pickSkill()
{
    QList<int> keys = skills.keys();
    bool aaExist = false;
    for(int i = 0 ; i < keys.size() ; i++)
    {
        Skill *s = skills[keys[i]].getSkill();
        if(!s || !character)
            continue;
        if(!availableSkillID.contains(s->getID()))
            continue;
        if(s->getCastID() == 0)
            aaExist = true;
        if(!s->isUsable())
            continue;
        if(character->getStatsProperties().getCurrentMP() < s->getManaCost())
            continue;
        if(skills[keys[i]].getSecondBetweenCast() > 0)
        {
            if(!skills[keys[i]].isCastablePseudoCooldown())
                continue;
            skills[keys[i]].setPseudoCooldown(QDateTime::currentDateTime());
        }
        return { skills[keys[i]], skills[keys[i]].getMaxRange() };
    }
    if(!aaExist)
    {
        QMap<int, Skill*> allSkills = character->getSkills();
        UsableSkill defaultSkill(allSkills[allSkills.keys()[0]]);
        defaultSkill.configure(-1, allSkills[allSkills.keys()[0]]->getRange(), Target::MONSTER);
        return { defaultSkill, allSkills[allSkills.keys()[0]]->getRange() };
    }
    return { UsableSkill(nullptr), 9999 };
}

int CharacterIA::checkForAgroedMonster(int range)
{
    QMap<int, Monster> agroedMobs = map->getAgroedMonsters();
    QList<int> agroedMobsKeys = agroedMobs.keys();
    Vec2i charXY = { character->getX(), character->getY() };
    double distMin = -1;
    int tID = -1;
    for(int i = 0 ; i < agroedMobsKeys.size() ; i++)
    {
        Vec2i mobXY = { agroedMobs[agroedMobsKeys[i]].getX(), agroedMobs[agroedMobsKeys[i]].getY() };
        double distChar = PathFinding::distance(charXY, mobXY);
        double distPart = PathFinding::distance(partnerCoord, mobXY);
        double distPet  = PathFinding::distance(petCoord, mobXY);
        if((character->pf.hasSight(charXY, mobXY) && distChar < range)
        ||((character->pf.hasSight(partnerCoord, mobXY) && partnerAI == MateAI::D) && distPart < range)
        ||((character->pf.hasSight(petCoord, mobXY) && petAI == MateAI::D) && distPet < range))
        {
            if(distMin < 0 || distMin > distChar)
            {
                distMin = distChar;
                tID = agroedMobs[agroedMobsKeys[i]].getID();
            }
        }
    }
    return tID;
}

void CharacterIA::newSkills()
{
    if(!isCharacterValid())
        return;
    availableSkillID.clear();
    QMap<int, Skill*> avSkills = character->getSkills();
    QList<int> avSkillsKeys = avSkills.keys();
    for(int i = 0 ; i < avSkillsKeys.size() ; i++)
        availableSkillID.push_back(avSkills[avSkillsKeys[i]]->getID());
}

void CharacterIA::setSit(int HpPercent, int MpPercent, int HpPercentGetUp, int MpPercentGetUp)
{
    hpPercent = HpPercent;
    mpPercent = MpPercent;
    hpPercentGetUp = HpPercentGetUp;
    mpPercentGetUp = MpPercentGetUp;
}

void CharacterIA::resetTarget()
{
    qDebug() << "reset called" << map->getAgroedMonsters().keys();
    targetID = -1;
    dropID = -1;
}

bool CharacterIA::rest()
{
    int hpP = static_cast<int>(character->getStatsProperties().getPercentHP() * 100);
    int mpP = static_cast<int>(character->getStatsProperties().getPercentMP() * 100);
    if(!shouldRest())
    {
        if(character->getState() == CharacterState::RESTING)
        {
            if(hpP >= hpPercentGetUp && mpP >= mpPercentGetUp)
                character->rest(false);
            // else return true;
            // and remove from Calculation() in the rest() condition "character->getState..."
        }
        return false;
    }
    if(character->getState() != CharacterState::RESTING)
        character->rest(true);
    else if(character->getState() == CharacterState::RESTING && hpP >= hpPercentGetUp && mpP >= mpPercentGetUp)
    {
        character->rest(false);
        return false;
    }
    return true;
}

bool CharacterIA::shouldRest()
{
    int hpP = static_cast<int>(character->getStatsProperties().getPercentHP() * 100);
    int mpP = static_cast<int>(character->getStatsProperties().getPercentMP() * 100);
    if(hpP > hpPercent && mpP > mpPercent)
        return false;
    if(checkForAgroedMonster(30) != -1)
        return false;
    return true;
}

void CharacterIA::setGoToMLDelay(int Seconds)
{
    gotoMLDelay = Seconds;
}

void CharacterIA::setStayMLDelay(int Seconds)
{
    stayMLDelay = Seconds;
}

void CharacterIA::setDropDetectionRange(int DetectionRange)
{
    qDebug() << "DropDetectionRange set to " << DetectionRange;
    dropDetectionRange = DetectionRange;
}

void CharacterIA::setPartnerCoordinate(int PartX, int PartY)
{
    partnerCoord = { PartX, PartY };
}

void CharacterIA::setPartnerAIType(MateAI PartnerAI)
{
    partnerAI = PartnerAI;
}

void CharacterIA::setPetCoordinate(int PetX, int PetY)
{
    petCoord = { PetX, PetY };
}

void CharacterIA::setPetAIType(MateAI PetAI)
{
    petAI = PetAI;
}
