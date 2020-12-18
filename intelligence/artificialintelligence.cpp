#include "artificialintelligence.h"

ArtificialIntelligence::ArtificialIntelligence(QObject *parent)
    : QObject(parent)
{
    core = new QTimer(this);
    core->setInterval(40);
    connect(core, &QTimer::timeout, this, &ArtificialIntelligence::startComputing);
    charIA = new CharacterIA(this);
    partIA = new PartnerIA(this);
    nosmateIA = new NosmateIA(this);
    working = false;
}

void ArtificialIntelligence::setWorld(Map *Map, MyCharacter *Character)
{
    if(Map && Character)
        charIA->setWorld(Map, Character);
}

void ArtificialIntelligence::setWorld(Map *Map, MyPartner *Partner)
{
    if(Map && Partner)
        partIA->setWorld(Map, Partner);
}

void ArtificialIntelligence::setWorld(Map *Map, MyNosmate *Nosmate)
{
    if(Map && Nosmate)
        nosmateIA->setWorld(Map, Nosmate);
}

void ArtificialIntelligence::setFilter(QList<int> monstersID, MonsterListType listType)
{
    if(charIA)
        charIA->setFilter(monstersID, listType);
}

void ArtificialIntelligence::setFilter(QList<int> dropsID, DropListType listType)
{
    if(charIA)
        charIA->setFilter(dropsID, listType);
}

void ArtificialIntelligence::setUsableSkills(QMap<int, UsableSkill> Skills)
{
    if(charIA->isCharacterValid())
        charIA->setSkills(Skills);
}

void ArtificialIntelligence::setPartnerUsableSkills(QMap<int, UsableSkill> Skills)
{
    if(partIA->isPartnerValid())
        partIA->setSkills(Skills);
}

void ArtificialIntelligence::setNosmateUsableSkills(QMap<int, UsableSkill> Skills)
{
    if(nosmateIA->isNosmateValid())
        nosmateIA->setSkills(Skills);
}

void ArtificialIntelligence::setPartnerAI(MateAI aiType)
{
    partIA->setAIType(aiType);
    charIA->setPartnerAIType(aiType);
}

void ArtificialIntelligence::setPetAI(MateAI aiType)
{
    nosmateIA->setAIType(aiType);
    charIA->setPetAIType(aiType);
}

void ArtificialIntelligence::setState(bool Working)
{
    working = Working;
    if(working)
        core->start();
    else
        core->stop();
}

void ArtificialIntelligence::startComputing()
{
    if(charIA->isCharacterValid())
        charIA->compute();
    if(partIA->isPartnerValid())
        partIA->compute();
    if(nosmateIA->isNosmateValid())
        nosmateIA->compute();
}

void ArtificialIntelligence::resetTarget()
{
    if(charIA->isCharacterValid())
        charIA->resetTarget();
    if(partIA->isPartnerValid())
        partIA->resetTarget();
    if(nosmateIA->isNosmateValid())
        nosmateIA->resetTarget();
}

bool ArtificialIntelligence::isWorking()
{
    return working;
}

void ArtificialIntelligence::newCharacterSkills()
{
    charIA->newSkills();
}

void ArtificialIntelligence::setPathing(PathingType pathingType, QPair<int, int> firstPoint, QVector<QPair<int, int> > way)
{
    charIA->setPathing(pathingType, firstPoint, way);
}

void ArtificialIntelligence::setSit(int hpPercent, int mpPercent, int hpPercentGetUp, int mpPercentGetUp)
{
    charIA->setSit(hpPercent, mpPercent, hpPercentGetUp, mpPercentGetUp);
}

void ArtificialIntelligence::setGoToMLDelay(int seconds)
{
    charIA->setGoToMLDelay(seconds);
}

void ArtificialIntelligence::setStayMLDelay(int seconds)
{
    charIA->setStayMLDelay(seconds);
}

void ArtificialIntelligence::setDropDistance(int detectionRange)
{
    charIA->setDropDetectionRange(detectionRange);
}

void ArtificialIntelligence::sendPartnerPosToCharacter(int x, int y)
{
    charIA->setPartnerCoordinate(x, y);
}

void ArtificialIntelligence::sendPetPosToCharacter(int x, int y)
{
    charIA->setPetCoordinate(x, y);
}
