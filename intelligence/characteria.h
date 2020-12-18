#ifndef CHARACTERIA_H
#define CHARACTERIA_H

#include <QObject>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/GameObjects/Entity/mycharacter.h"
#include "widgets/skillswidget.h"
#include "widgets/monsterwidget.h"
#include "widgets/dropwidget.h"
#include "widgets/pathingwidget.h"
#include "widgets/behaviourwidget.h"

class CharacterIA : public QObject
{
public:
    CharacterIA(QObject *parent);
    bool isCharacterValid();
    void setWorld(Map *Map, MyCharacter *Character);
    void setSkills(QMap<int, UsableSkill> Skills);
    void setFilter(QList<int> MonstersID, MonsterListType ListType);
    void setFilter(QList<int> DropsID, DropListType ListType);
    void setPathing(PathingType PathingType, QPair<int, int> Arg1 = {}, QVector<QPair<int, int>> Arg2 = {});
    void compute();
    void resetTarget();
    void newSkills();
    void setSit(int HpPercent, int MpPercent, int HpPercentGetUp, int MpPercentGetUp);
    void setGoToMLDelay(int Seconds);
    void setStayMLDelay(int Seconds);
    void setDropDetectionRange(int DetectionRange);

    void setPartnerCoordinate(int PartX = -1, int PartY = -1);
    void setPartnerAIType(MateAI PartnerAI);
    void setPetCoordinate(int PetX = -1, int PetY = -1);
    void setPetAIType(MateAI PetAI);

private:
    bool rest();
    bool drop();
    bool farm();

    int getNearestTargetID();
    Drop getNearestDrop();
    bool shouldDrop();
    bool shouldRest();
    bool shouldGoToTarget(int range);
    bool shouldAttackTarget(int range);
    bool shouldGetNewTarget();
    bool shouldConsiderMonster(int mobX, int mobY);
    double distanceToTarget();
    QPair<UsableSkill, int> pickSkill();
    int checkForAgroedMonster(int range);

    Map *map;
    MyCharacter *character;
    QMap<int, UsableSkill> skills;
    QList<int> monstersID, dropsID, availableSkillID;
    MonsterListType mListType;
    DropListType dListType;
    int targetID, dropID;
    QDateTime animationTimer;
    PathingType pathingType;
    QPair<int, int> pathingArg1;
    QVector<QPair<int, int>> pathingArg2;

    int hpPercent, mpPercent, hpPercentGetUp, mpPercentGetUp;
    int gotoMLDelay, stayMLDelay;
    int dropDetectionRange;

    Vec2i partnerCoord, petCoord;
    MateAI partnerAI, petAI;
};

#endif // CHARACTERIA_H
