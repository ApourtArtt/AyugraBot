#include "mynosmate.h"

MyNosmate::MyNosmate(int MapID, QObject *parent)
    : QObject(parent)
{
    mapID = MapID;
}

void MyNosmate::handleAtPacket(PacketAt Packet)
{
    mapID = Packet.getMapID();
    pf.loadMap(DatabaseMap::getMapObstacle(Packet.getMapID()));
}

void MyNosmate::handleInPacket(PacketIn23 Packet)
{
    // in 2 2640 861786 5 9 2 100 100 0 0 3 886274 1 0 2706 Jennifer 1 1 0 0 0 0 0 0 0 0 0 0
    vnum = Packet.getName();
    MonsterFromDb tmp = DatabaseMonster::getMonsterProperties(vnum.toInt());
    range = tmp.getRange();
    msAuto = tmp.getMsBasicAuto();
    x = Packet.getX();
    y = Packet.getY();
    nosmateID = Packet.getID();
    pf.loadMap(DatabaseMap::getMapObstacle(mapID));
}

void MyNosmate::handlePetskiPacket(PacketPetski Packet)
{
    skills.clear();
    int skillId = Packet.getSkillID();
    if(skillId != -1)
    {
        Skill *tmp = new Skill(skillId);
        skills.insert(0/*tmp->getCastID()*/, tmp);
    }
    emit newSkills(skills);
}

void MyNosmate::handlePstPacket(PacketPst Packet)
{
    stats.handlePstatPacket(Packet);
}

void MyNosmate::handleCondPacket(PacketCond Packet)
{
    rooted = Packet.isRooted();
    stunned = Packet.isStunned();
    speed = Packet.getSpeed();
}

void MyNosmate::handlePetsrPacket(PacketPetsr Packet)
{
    skills[0/*Packet.getSkillCastID()*/]->setInCooldow(false);
}

bool MyNosmate::useSkill(Skill *skill, BaseEntity entity)
{
    if(!canAttack())
    {
        qDebug() << "Stunned...";
        return false;
    }
    if(!skill)
    {
        qDebug() << "No skill : AA";
        sendPacket(PacketSuctl(mapID, 1, nosmateID, entity.getEntityType(), entity.getID()).getPacket());
        return true;
    }
    if(!(skills.value(0/*skill->getCastID()*/) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    sendPacket(PacketU_pet(nosmateID, entity.getEntityType(), entity.getID(), 0, entity.getX(), entity.getY()).getPacket(), false);
    skill->setInCooldow(true);
    QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    return true;
}

bool MyNosmate::useSkill(Skill *skill, int x, int y)
{
    if(!canAttack())
        return false;
    if(!skill)
        return false;
    if(!(skills.value(0/*skill->getCastID()*/) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    sendPacket(PacketU_pet(nosmateID, EntityType::NOSMATE_NPC, nosmateID, skill->getCastID(), x, y).getPacket(), false);
    skill->setInCooldow(true);
    QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    return true;
}

Vec2i MyNosmate::walk(int posX, int posY, int range, bool wallHack)
{
    cancelActionsDelay();
    cancelWalking();
    if(x == -1 || y == -1 || (posX == x && posY == y) || speed == -1)// || !pathfinding)
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
                    state = NosmateState::RUNNING;
                    sendPacket(PacketPtctl(mapID, 1, nosmateID, coord[i].x, coord[i].y, speed).getPacket());
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
                                state = NosmateState::WAITING;
                            }
                        }
                        else
                        {
                            cancelActionsDelay();
                            cancelWalking();
                            emit onDestination(x, y);
                            state = NosmateState::WAITING;
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

bool MyNosmate::isAlive()
{
    if(stats.getCurrentHP() <= 0)
        return false;
    return true;
}

QMap<int, Skill *> MyNosmate::getSkills()
{
    return skills;
}

bool MyNosmate::canMove() const
{
    return !rooted;
}

bool MyNosmate::canAttack() const
{
    return !stunned;
}

int MyNosmate::getNosmateID() const
{
    return nosmateID;
}

NosmateState MyNosmate::getNosmateState() const
{
    return state;
}

int MyNosmate::getX() const
{
    return x;
}

int MyNosmate::getY() const
{
    return y;
}

int MyNosmate::getRange() const
{
    return range;
}

int MyNosmate::msBetweenTwoAA() const
{
    return msAuto;
}

Statistics MyNosmate::getStatsProperties() const
{
    return stats;
}

void MyNosmate::cancelActionsDelay()
{
    for(int i = 0 ; i < actionTimers.size() ; i++)
        delete actionTimers[i];
    actionTimers.clear();
}

void MyNosmate::cancelWalking()
{
    for(int i = 0 ; i < walkTimers.size() ; i++)
        delete walkTimers[i];
    walkTimers.clear();
}
