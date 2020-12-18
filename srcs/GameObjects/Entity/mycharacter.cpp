#include "mycharacter.h"

MyCharacter::MyCharacter(QObject *parent)
    : QObject(parent)
{
    characterClass = Class::ADVENTURER;
    gender = Gender::MALE;
    authority = Authority::PLAYER;
    hairStyle = HairStyle::NOHAIR;
    slot = -1;
    groupID = -1;
    familyID = -1;
    characterID = -1;
    familyLevel = -1;
    admiration = -1;
    morph = -1;
    spUpgrade = -1;
    arenaWinner = false;
    invisible = false;
    speed = -1;
    stunned = false;
    rooted = false;
    inventory = new Inventory(this);
    state = CharacterState::WAITING;
    lastTimeTriedSitDown = QDateTime::currentDateTime().addDays(-1);
    //pathfinding = nullptr;
    connect(inventory, &Inventory::sendPacket, this, [=](QString packet){emit sendPacket(packet);});
}

MyCharacter::MyCharacter(PacketClist Packet, QObject *parent)
    : QObject(parent)
{
    characterClass = Packet.getClass();
    gender = Packet.getSexe();
    slot = Packet.getSlot();
    pseudonym = Packet.getPseudonym();
    hairStyle = Packet.getHairStyle();
    hairColor = Packet.getHairColor();
    quest.handleClistPacket(Packet);
    authority = Authority::PLAYER;
    groupID = -1;
    familyID = -1;
    characterID = -1;
    familyLevel = -1;
    admiration = -1;
    morph = -1;
    spUpgrade = -1;
    stunned = false;
    rooted = false;
    arenaWinner = false;
    invisible = false;
    level.handleClistPacket(Packet);
    inventory = new Inventory(this);
    state = CharacterState::WAITING;
    //pathfinding = nullptr;
    connect(inventory, &Inventory::sendPacket, this, [=](QString packet){emit sendPacket(packet);});
}

MyCharacter::~MyCharacter()
{
    delete inventory;
    //delete pathfinding;
    cancelActionsDelay();
    stopMoving();
}

void MyCharacter::handleC_infoPacket(PacketC_info Packet)
{
    reputation.handleC_infoPacket(Packet);
    pseudonym = Packet.getPseudonym();
    groupID = Packet.getGroupID();
    familyID = Packet.getFamilyID();
    characterID = Packet.getCharacterID();
    authority = Packet.getAuthority();
    gender = Packet.getGender();
    hairStyle = Packet.getHairStyle();
    hairColor = Packet.getHairColor();
    characterClass = Packet.getClass();
    admiration = Packet.getAdmiration();
    morph = Packet.getMorph();
    invisible = Packet.isInvisible();
    familyLevel = Packet.getFamilyLevel();
    spUpgrade = Packet.getSpUpgrade();
    arenaWinner = Packet.isArenaWinner();
}

void MyCharacter::handleAtPacket(PacketAt Packet)
{
    x = Packet.getPosX();
    y = Packet.getPosY();
    direction = Packet.getDirection();
    //if(!pathfinding)
    //    pathfinding = PathFinding::getInstance();
    pf.loadMap(DatabaseMap::getMapObstacle(Packet.getMapID()));
    emit characterUpdate();
    emit moved(x, y);
}

void MyCharacter::handleLevPacket(PacketLev Packet)
{
    level.handleLevPacket(Packet);
}

void MyCharacter::handleFdPacket(PacketFd Packet)
{
    reputation.handleFdPacket(Packet);
}

/*
 * Since stat packet is being spammed by Nostale server, I don't think
 * it is usefull to update for every usefull (but not urgent) packet.
 * Cond is really urgent, so update when recieved.
*/

void MyCharacter::handleStatPacket(PacketStat Packet)
{
    stats.handleStatPacket(Packet);
    emit characterUpdate();
}

void MyCharacter::handleCondPacket(PacketCond Packet)
{
    rooted = Packet.isRooted();
    stunned = Packet.isStunned();
    speed = Packet.getSpeed();
    emit characterUpdate();
}

void MyCharacter::handleRsfiPacket(PacketRsfi Packet)
{
    quest.handleRsfiPacket(Packet);
}

void MyCharacter::handleInvPacket(PacketInv Packet)
{
    inventory->treatInvPacket(Packet);
    emit inventoryUpdate();
}

void MyCharacter::handleIvnPacket(PacketIvn Packet)
{
    inventory->treatIvnPacket(Packet);
    emit inventoryUpdate();
}

void MyCharacter::handleGoldPacket(PacketGold Packet)
{
    inventory->treatGoldPacket(Packet);
    emit inventoryUpdate();
}

void MyCharacter::handleSkiPacket(PacketSki Packet)
{
    skills.clear();
    qDebug() << Packet.getPacketToDisplay();
    Skill *Space = new Skill(Packet.getSpaceSkillID());
    Skill *Z = new Skill(Packet.getZSkillID());
    skills.insert(Space->getCastID(), Space);
    skills.insert(Z->getCastID(), Z);
    QVector<int> skillId = Packet.getOtherSkillsID();
    qDebug() << "Vec : " << skillId;
    for(int i = 0 ; i < skillId.size() ; i++)
    {
        Skill *tmp = new Skill(skillId[i]);
        if(tmp->getSkillType() == SkillType::SKILL)
        {
            skills.insert(tmp->getCastID(), tmp);
        }
    }
    qDebug() << "Emit !!!";
    emit newSkills(skills);
}

void MyCharacter::handleCancelPacket(PacketCancel Packet)
{
    // What about drop cancel, what should I do ?
    CancelType reason = Packet.getCancelType();
    if(reason == CancelType::CANCEL_SKILL || reason == CancelType::CANCEL_TARGET)
    {
        Skill *s = skills.value(Packet.getCancelID());
        if(s)
        {
            s->setInCooldow(false);
            s->setAvailableCombo(false);
        }
        else
        {
            QList<int> keys = skills.keys();
            for(int i = 0 ; i < keys.size() ; i++)
            {
                if(skills[keys[i]]->getID() == Packet.getCancelID())
                {
                    skills[keys[i]]->setInCooldow(false);
                    skills[keys[i]]->setAvailableCombo(false);
                }
            }
        }
    }
}

void MyCharacter::handleSrPacket(PacketSr Packet)
{
    // Missing a -10 sr handler. It should set the cd to Packet.getRemainingCooldown()/10 s
    //if(Packet.getRemainingCooldown() == 0)
    //    return;
    skills[Packet.getCastID()]->setInCooldow(false);
}

void MyCharacter::handleMslotPacket(PacketMslot Packet)
{
    Skill *skill = skills.value(Packet.getCastID());
    skill->setAvailableCombo(true);
}

void MyCharacter::handleMs_cPacket(PacketMs_c Packet)
{
    Q_UNUSED(Packet)
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        skills[keys[i]]->setAvailableCombo(false);
}

void MyCharacter::handleDelayPacket(PacketDelay Packet)
{
    // Add cancel on hit etc.
    cancelActionsDelay();
    stopMoving();
    int timerBeforeChanneling  = 0;
    if(state == CharacterState::RESTING)
    {
        rest(false);
        timerBeforeChanneling = 50;
    }
    QTimer::singleShot(timerBeforeChanneling, [=]
    {
        sendPacket(PacketGuri(2).getPacket());
        for(int i = 0 ; i <= (Packet.msToWait() / 1000) ; i++)
        {
            QTimer *tmp = new QTimer(this);
            actionTimers.push_back(tmp);
            tmp->setSingleShot(true);
            tmp->setInterval(i * 1000);
            PacketDelay pTmp = Packet;
            state = CharacterState::CHANNELING;
            connect(tmp, &QTimer::timeout, [=]
            {
                sendPacket(PacketGuri(5, EntityType::PLAYER, characterID,
                                      static_cast<int>((i * 1000) / (Packet.msToWait() / 100)),
                                      Packet.getGuriArgument())
                           .getPacket());
                if((i * 1000) == Packet.msToWait())
                {
                    sendPacket(Packet.getPacketAnswer(), true);
                    state = CharacterState::WAITING;
                }
            });
            tmp->start();
        }
    });
}

// TODO: Add NoDelay and check on rooted
Vec2i MyCharacter::walk(int posX, int posY, double range, bool wallHack)
{
    cancelActionsDelay();
    stopMoving();
    rest(false);
    if(!canMove())
        return {};
    if(x == -1 || y == -1 || (posX == x && posY == y) || speed == -1)// || !pathfinding)
    {
        emit onDestination(x, y);
        return {x, y};
    }
    CoordinateList coord;
    if(range <= 0)
        coord = pf.findPath({ x, y }, { posX, posY });
        //coord = PathFinding::findPath({ x, y }, { posX, posY });
    else
        coord = pf.findPath({ x, y }, { posX, posY }, range, wallHack);
        //coord = PathFinding::findPath({ x, y }, { posX, posY }, range, wallHack);
    int step = static_cast<int>(std::ceil(static_cast<float>(speed/2.5f) - 1));
    float time = step * 2500 / speed; // maybe try to use dist instead of step ? to avoid those speedhack spike
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
                    state = CharacterState::RUNNING;
                    sendPacket(PacketWalk(coord[i].x, coord[i].y, ((coord[i].x + coord[i].y)%3)%2, speed).getPacket());
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
                                stopMoving();
                                emit onDestination(x, y);
                                state = CharacterState::WAITING;
                            }
                        }
                        else
                        {
                            cancelActionsDelay();
                            stopMoving();
                            emit onDestination(x, y);
                            state = CharacterState::WAITING;
                        }
                    });
                }
            });
            walkTimers.push_back(tmp);
            tmp->start();
            j++;
            dist = 0;
        }
    }
    return { coord[coord.size() - 1].x, coord[coord.size() - 1].y };
}

void MyCharacter::takePortal(Portal portal)
{
    QObject *context = new QObject(this);
    connect(this, &MyCharacter::onDestination, context, [=](int portX, int portY) {
        delete context;
        if(PathFinding::distance({portX, portY}, {x, y}) < 2)
            sendPacket(PacketPreq().getPacket());
        // Need to manage the case where too many portal change have been done
        // Maybe a timer reset on at packet ?
    });
    walk(portal.getX(), portal.getY(), qrand()%2);
}

void MyCharacter::goIntoTS(TS ts, bool enter, bool record, bool distanceHack)
{
    int portX = -1;
    int portY = -1;
    if(enter)
    {
        TimeSpaceInstance *tsInstance = TimeSpaceInstance::getInstance();
        QObject *context = new QObject(this);
        connect(tsInstance, &TimeSpaceInstance::tsPopUp, context, [=]()
        {
            delete context;
            if(enter)
            {
                if(PathFinding::distance({portX, portY}, {x, y}) < 2 && portX != -1 && portY != -1)
                    sendPacket(PacketWreq(true, record).getPacket());
                else
                    sendPacket(PacketTreq(ts.getX(), ts.getY(), true, record).getPacket());
            }
        });
    }
    if(distanceHack)
        // Official client also send a ncif packet with random ID coded on unsigned int 2^32
        sendPacket(PacketTreq(ts.getX(), ts.getY(), false, false).getPacket());
    else
    {
        QObject *context = new QObject(this);
        connect(this, &MyCharacter::onDestination, context, [=](int pX, int pY) mutable
        {
            delete context;
            portX = pX;
            portY = pY;
            if(PathFinding::distance({portX, portY}, {x, y}) < 2)
                sendPacket(PacketWreq(false, false).getPacket());
            else
                sendPacket(PacketTreq(ts.getX(), ts.getY(), false, false).getPacket());
        });
        walk(ts.getX(), ts.getY(), qrand()%2);
    }
}

// Also send ncif packet and continue after skill's casted
bool MyCharacter::useSkill(Skill *skill, BaseEntity entity, int posX, int posY)
{
    if(!canAttack())
        return false;
    if(!skill)
        return false;
    if(!(skills.value(skill->getCastID()) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    if(skill->getSkillTarget() == SkillTarget::SKILLSHOT)
    {
        cancelActionsDelay();
        PacketU_as packet(skill->getCastID(), posX == -1 ? entity.getX() : posX, posY == -1 ? entity.getY() : posY);
        sendPacket(packet.getPacket());
        skill->setInCooldow(true); // or use su packet...
        QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    }
    else
    {
        if(skill->isDash())
        {
            cancelActionsDelay();
            PacketU_s packet(skill->getCastID(), entity.getEntityType(), entity.getID(), posX == -1 ? entity.getX() : posX, posY == -1 ? entity.getY() : posY);
            sendPacket(packet.getPacket());
            skill->setInCooldow(true); // or use su packet...
            QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
        }
        else
        {
            cancelActionsDelay();
            PacketU_s packet(skill->getCastID(), entity.getEntityType(), entity.getID());
            sendPacket(packet.getPacket());
            skill->setInCooldow(true); // or use su packet...
            QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
        }
    }
    return true;
}

// Also send ncif packet and continue after skill's casted
bool MyCharacter::useSkill(Skill *skill, int posX, int posY)
{
    if(!canAttack())
        return false;
    if(!skill)
        return false;
    if(!(skills.value(skill->getCastID()) == skill))
        return false;
    if(!skill->isUsable())
        return false;
    if(skill->getSkillTarget() == SkillTarget::SKILLSHOT)
    {
        cancelActionsDelay();
        PacketU_as packet(skill->getCastID(), posX, posY);
        sendPacket(packet.getPacket());
        skill->setInCooldow(true); // or use su packet...
        QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    }
    else
    {
        cancelActionsDelay();
        PacketU_s packet(skill->getCastID(), EntityType::PLAYER, characterID, posX == -1 ? x : posX, posY == -1 ? y : posY);
        sendPacket(packet.getPacket());
        skill->setInCooldow(true); // or use su packet...
        QTimer::singleShot(skill->getCooldown(), [=]{ skill->setInCooldow(false); });
    }
    return true;
}

void MyCharacter::toggleSP()
{
    cancelActionsDelay();
    stopMoving();
    QTimer::singleShot(500+qrand()%100, [=]{ sendPacket(PacketSl(0).getPacket()); });
}

bool MyCharacter::drop(Drop drop, double range, bool wallHack, bool forceTrying)
{
    if(!drop.isPublic() && (characterID != drop.getOwnerID() && drop.getOwnerID() != -1) && !forceTrying)
        return false;
    if(PathFinding::distance({ x, y }, { drop.getX(), drop.getY() }) > range)
    {
        QObject *context = new QObject(this);
        connect(this, &MyCharacter::onDestination, context, [=](int dropX, int dropY) {
            delete context;
            if(PathFinding::distance({ dropX, dropY }, { x, y }) < range)
                sendPacket(PacketGet(EntityType::PLAYER, characterID, drop.getID()).getPacket());
        });
        walk(drop.getX(), drop.getY(), range, wallHack);
    }
    else
        sendPacket(PacketGet(EntityType::PLAYER, characterID, drop.getID()).getPacket());
    return true;
}

void MyCharacter::rest(bool sitDown)
{
    qDebug() << "Sit : " << sitDown << (state == CharacterState::RESTING);
    if((sitDown && state != CharacterState::RESTING) || (!sitDown && state == CharacterState::RESTING))
    {
        if(lastTimeTriedSitDown < QDateTime::currentDateTime())
        {
            lastTimeTriedSitDown = QDateTime::currentDateTime().addMSecs(500);
            stopMoving();
            sendPacket(PacketRest(1, { { EntityType::PLAYER, characterID } }).getPacket());
        }
    }
}

void MyCharacter::stopMoving()
{
    cancelWalking();
    if(state == CharacterState::RUNNING)
        state = CharacterState::WAITING;
}

bool MyCharacter::isAlive()
{
    if(stats.getCurrentHP() == 0)
        return false;
    return true;
}

short MyCharacter::getSlot() const
{
    return slot;
}

QString MyCharacter::getPseudonym() const
{
    return pseudonym;
}

Gender MyCharacter::getGender() const
{
    return gender;
}

Authority MyCharacter::getAuthority() const
{
    return authority;
}

HairStyle MyCharacter::getHairStyle() const
{
    return hairStyle;
}

short MyCharacter::getHairColor() const
{
    return hairColor;
}

Class MyCharacter::getClass() const
{
    return characterClass;
}

const Level MyCharacter::getLevelProperties() const
{
    return level;
}

const Reputation MyCharacter::getReputationProperties() const
{
    return reputation;
}

const Statistics MyCharacter::getStatsProperties() const
{
    return stats;
}

const Quest MyCharacter::getQuestProperties() const
{
    return quest;
}

Inventory *MyCharacter::getInventory() const
{
    return inventory;
}

int MyCharacter::getGroupID() const
{
    return groupID;
}

int MyCharacter::getFamilyID() const
{
    return familyID;
}

int MyCharacter::getCharacterID() const
{
    return characterID;
}

short MyCharacter::getFamilyLevel() const
{
    return familyLevel;
}

short MyCharacter::getMorph() const
{
    return morph;
}

short MyCharacter::getSpUpgrade() const
{
    return spUpgrade;
}

bool MyCharacter::isArenaWinner() const
{
    return arenaWinner;
}

bool MyCharacter::isInvisible() const
{
    return invisible;
}

short MyCharacter::getSpeed() const
{
    return speed;
}

bool MyCharacter::canAttack() const
{
    return !stunned && stats.getCurrentHP() > 0;
}

bool MyCharacter::canMove() const
{
    if(rooted)
        return false;
    if(stats.getCurrentHP() == 0)
        return false;
    if(state == CharacterState::RESTING)
        return false;
    if(state == CharacterState::ATTACKING)
        return false;
    return true;
}

int MyCharacter::getX() const
{
    return x;
}

int MyCharacter::getY() const
{
    return y;
}

short MyCharacter::getDirection() const
{
    return direction;
}

QMap<int, Skill*> MyCharacter::getSkills() const
{
    return skills;
}

CharacterState MyCharacter::getState() const
{
    return state;
}

void MyCharacter::setResting(bool Rest)
{
    qDebug() << "SetResting : "<< Rest << static_cast<int>(state);
    state = (Rest ? CharacterState::RESTING : CharacterState::WAITING);
    qDebug() << "SetResting : "<< Rest << static_cast<int>(state);
}

void MyCharacter::cancelActionsDelay()
{
    for(int i = 0 ; i < actionTimers.size() ; i++)
        delete actionTimers[i];
    actionTimers.clear();
}

void MyCharacter::cancelWalking()
{
    for(int i = 0 ; i < walkTimers.size() ; i++)
        delete walkTimers[i];
    walkTimers.clear();
}
