#include "mypartner.h"

MyPartner::MyPartner(int MapID, QObject *parent)
    : QObject(parent)
{
    //pathfinding = PathFinding::getInstance();
    mapID = MapID;
}

void MyPartner::handleAtPacket(PacketAt Packet)
{
    mapID = Packet.getMapID();
    characterID = Packet.getCharacterID();
    pf.loadMap(DatabaseMap::getMapObstacle(Packet.getMapID()));
    qDebug() << "Map AT Partner";
}

void MyPartner::handleInPacket(PacketIn23 Packet)
{
    // in 2 2640 861786 5 9 2 100 100 0 0 3 886274 1 0 2706 Jennifer 1 1 0 0 0 0 0 0 0 0 0 0
    vnum = Packet.getName();
    MonsterFromDb tmp = DatabaseMonster::getMonsterProperties(vnum.toInt());
    range = tmp.getRange();
    msAuto = tmp.getMsBasicAuto();
    x = Packet.getX();
    y = Packet.getY();
    partnerID = Packet.getID();
    characterID = Packet.getOwnerID();
    pf.loadMap(DatabaseMap::getMapObstacle(mapID));
}

void MyPartner::handlePskiPacket(PacketPski Packet)
{
    skills.clear();
    QVector<int> skillId = Packet.getSkillsID();
    for(int i = 0 ; i < skillId.size() ; i++)
    {
        Skill *tmp = new Skill(skillId[i]);
        skills.insert(tmp->getCastID(), tmp);
    }
    emit newSkills(skills);
}

void MyPartner::handlePdelayPacket(PacketPdelay Packet)
{
    // Add cancel on hit etc.
    //cancelActionsDelay();
    //cancelWalking();
    sendPacket(PacketGuri(6).getPacket());
    for(int i = 0 ; i <= (Packet.msToWait() / 1000) ; i++)
    {
        QTimer *tmp = new QTimer(this);
        actionTimers.push_back(tmp);
        tmp->setSingleShot(true);
        tmp->setInterval(i * 1000);
        PacketPdelay pTmp = Packet;
        state = PartnerState::CHANNELING;
        connect(tmp, &QTimer::timeout, [=]
        {
            sendPacket(PacketGuri(5, EntityType::NOSMATE_NPC, (i == 0) ? characterID : partnerID,
                                  static_cast<int>((i * 1000) / (Packet.msToWait() / 100)),
                                  Packet.getGuriArgument())
                       .getPacket());
            if((i * 1000) == Packet.msToWait())
            {
                sendPacket(Packet.getPacketAnswer(), true);
                state = PartnerState::WAITING;
            }
        });
        tmp->start();
    }
}

void MyPartner::handlePstPacket(PacketPst Packet)
{
    stats.handlePstatPacket(Packet);
}

void MyPartner::handleCondPacket(PacketCond Packet)
{
    rooted = Packet.isRooted();
    stunned = Packet.isStunned();
    speed = Packet.getSpeed();
}

void MyPartner::handlePsrPacket(PacketPsr Packet)
{
    skills[Packet.getSkillCastID()]->setInCooldow(false);
}

void MyPartner::handleDpskiPacket(PacketDpski Packet)
{
    Q_UNUSED(Packet)
    skills.clear();
    emit newSkills(skills);
}

void MyPartner::toggleSP()
{
    sendPacket(PacketPsl(0).getPacket());
}

bool MyPartner::useSkill(Skill *skill, BaseEntity entity)
{
    if(!canAttack())
        return false;
    if(!skill)
    {
        sendPacket(PacketSuctl(mapID, 1, partnerID, entity.getEntityType(), entity.getID()).getPacket());
        return true;
    }
    if(!(skills.value(skill->getCastID()) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    sendPacket(PacketU_ps(partnerID, entity.getEntityType(), entity.getID(), skill->getCastID()).getPacket(), false);
    skill->setInCooldow(true);
    QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    return true;
}

bool MyPartner::useSkill(Skill *skill, int x, int y)
{
    if(!canAttack())
        return false;
    if(!skill)
        return false;
    if(!(skills.value(skill->getCastID()) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    sendPacket(PacketU_ps(partnerID, EntityType::NOSMATE_NPC, partnerID, skill->getCastID(), x, y).getPacket(), false);
    skill->setInCooldow(true);
    QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    return true;
}

Vec2i MyPartner::walk(int posX, int posY, int range, bool wallHack)
{
    cancelActionsDelay();
    cancelWalking();
    if(x == -1 || y == -1 || (posX == x && posY == y) || speed == -1)
    {
        emit onDestination(x, y);
        return { x, y };
    }
    CoordinateList coord;
    if(range <= 0)
        coord = pf.findPath({ x, y }, { posX, posY });
    else
        coord = pf.findPath({ x, y }, { posX, posY }, range, wallHack);
    int step = static_cast<int>(std::ceil(static_cast<float>(speed/2.5f) - 1));
    float time = step * 2500 / speed;
    double dist = 0;
    int j = 0;
    Vec2i tmp = { x, y };
    for(int i = 0 ; i < coord.size() ; i++)
    {
        dist = dist + PathFinding::distance(tmp, coord[i]);
        tmp = coord[i];
        if(dist >= step || i == coord.size() - 1)
        {
            QTimer *tmp = new QTimer(this);
            tmp->setSingleShot(true);
            tmp->setInterval(static_cast<int>(time) * j); // TODO : adjust time when dist < step (last step)
            connect(tmp, &QTimer::timeout, this, [=]
            {
                if(x != coord[i].x || y != coord[i].y)
                {
                    state = PartnerState::RUNNING;
                    sendPacket(PacketPtctl(mapID, 1, partnerID, coord[i].x, coord[i].y, speed).getPacket());
                    QTimer::singleShot(time, [=]
                    {
                        if(coord[i].x != -1 && coord[i].y != -1)
                        {
                            x = coord[i].x;
                            y = coord[i].y;
                            emit moved(x, y);
                            if(i == coord.size() - 1)
                            {
                                cancelActionsDelay();
                                cancelWalking();
                                emit onDestination(x, y);
                                state = PartnerState::WAITING;
                            }
                        }
                        else
                        {
                            cancelActionsDelay();
                            cancelWalking();
                            emit onDestination(x, y);
                            state = PartnerState::WAITING;
                        }
                    });
                }
            });
            actionTimers.push_back(tmp);
            tmp->start();
            j++;
            dist = 0;
        }
    }
    return { coord[coord.size() - 1].x, coord[coord.size() - 1].y };
}

bool MyPartner::isAlive()
{
    if(stats.getCurrentHP() <= 0)
        return false;
    return true;
}

QMap<int, Skill *> MyPartner::getSkills()
{
    return skills;
}

bool MyPartner::canMove() const
{
    return !rooted;
}

bool MyPartner::canAttack() const
{
    return !stunned;
}

int MyPartner::getPartnerID() const
{
    return partnerID;
}

PartnerState MyPartner::getPartnerState() const
{
    return state;
}

int MyPartner::getX() const
{
    return x;
}

int MyPartner::getY() const
{
    return y;
}

int MyPartner::getRange() const
{
    return range;
}

int MyPartner::msBetweenTwoAA() const
{
    return msAuto;
}

Statistics MyPartner::getStatsProperties() const
{
    return stats;
}

void MyPartner::cancelActionsDelay()
{
    for(int i = 0 ; i < actionTimers.size() ; i++)
        delete actionTimers[i];
    actionTimers.clear();
}

void MyPartner::cancelWalking()
{
    for(int i = 0 ; i < walkTimers.size() ; i++)
        delete walkTimers[i];
    walkTimers.clear();
}
