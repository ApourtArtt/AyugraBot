#ifndef NOSMATEIA_H
#define NOSMATEIA_H

#include <QObject>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/GameObjects/Entity/mynosmate.h"
#include "widgets/skillswidget.h"
#include "widgets/behaviourwidget.h"

class NosmateIA : public QObject
{
public:
    NosmateIA(QObject *parent);
    bool isNosmateValid();
    void setWorld(Map *Map, MyNosmate *Nosmate);
    void setSkills(QMap<int, UsableSkill> Skills);
    void compute();
    void resetTarget();
    void setAIType(MateAI AiType);

    MateAI getAIType() const;

private:
    int getNearestTargetID();
    bool shouldRest();
    bool shouldGoToTarget(int range);
    bool shouldAttackTarget(int range);
    bool shouldGetNewTarget();
    double distanceToTarget();
    QPair<UsableSkill*, int> pickSkill();

    Map *map;
    MyNosmate *nosmate;
    QMap<int, UsableSkill> skills;
    int targetID;
    QDateTime animationTimer;
    MateAI aiType;
};

#endif // NOSMATEIA_H
