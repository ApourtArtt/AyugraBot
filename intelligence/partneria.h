#ifndef PARTNERIA_H
#define PARTNERIA_H

#include <QObject>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/GameObjects/Entity/mypartner.h"
#include "widgets/skillswidget.h"
#include "widgets/behaviourwidget.h"

class PartnerIA : public QObject
{
public:
    PartnerIA(QObject *parent);
    bool isPartnerValid();
    void setWorld(Map *Map, MyPartner *Partner);
    void setSkills(QMap<int, UsableSkill> Skills);
    void compute();
    void resetTarget();
    void setAIType(MateAI AiType);
    void setResting(bool value);
    void setTargetID(int value);

    MateAI getAIType() const;

private:
    int getNearestTargetID();
    bool shouldRest();
    bool shouldGoToTarget(int range);
    bool shouldAttackTarget(int range);
    bool shouldGetNewTarget();
    double distanceToTarget();
    QPair<UsableSkill*, int> pickSkill();
    void rest();

    void Compute_A();
    void Compute_D();
    void Compute_S();

    bool forceResting;

    Map *map;
    MyPartner *partner;
    QMap<int, UsableSkill> skills;
    int targetID;
    QDateTime animationTimer;
    MateAI aiType;
};

#endif // PARTNERIA_H
