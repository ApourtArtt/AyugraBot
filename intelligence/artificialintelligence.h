#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H

#include "intelligence/characteria.h"
#include "intelligence/nosmateia.h"
#include "intelligence/partneria.h"

class ArtificialIntelligence : public QObject
{
    Q_OBJECT
public:
    ArtificialIntelligence(QObject *parent);

    void setWorld(Map *Map, MyCharacter *character);
    void setWorld(Map *Map, MyPartner *partner);
    void setWorld(Map *Map, MyNosmate *nosmate);

    void setFilter(QList<int> monstersID, MonsterListType listType);
    void setFilter(QList<int> dropsID, DropListType listType);

    void setUsableSkills(QMap<int, UsableSkill> Skills);
    void setPartnerUsableSkills(QMap<int, UsableSkill> Skills);
    void setNosmateUsableSkills(QMap<int, UsableSkill> Skills);

    void setPartnerAI(MateAI aiType);
    void setPetAI(MateAI aiType);

    /*
    void sitLowerThan(int hpPercent, int mpPercent);

    void goToMinilandEvery(int seconds);
    void stayInMinilandFor(int seconds);

    void distDropChanged(int detectionRange);
*/

    void setState(bool Working);
    void resetTarget();
    bool isWorking();

    void newCharacterSkills();
    void setPathing(PathingType pathingType, QPair<int, int> firstPoint, QVector<QPair<int, int>> way);
    void setSit(int hpPercent, int mpPercent, int hpPercentGetUp, int mpPercentGetUp);
    void setGoToMLDelay(int seconds);
    void setStayMLDelay(int seconds);
    void setDropDistance(int detectionRange);

    void sendPartnerPosToCharacter(int x, int y);
    void sendPetPosToCharacter(int x, int y);

private slots:
    void startComputing();

private:
    PartnerIA *partIA;
    CharacterIA *charIA;
    NosmateIA *nosmateIA;

    bool working;
    QTimer *core;
};

#endif // ARTIFICIALINTELLIGENCE_H
