#include "botwidget.h"
#include "ui_botwidget.h"

BotWidget::BotWidget(BotManager *Bot, QWidget *parent) :
    FormBase(parent),
    ui(new Ui::BotWidget)
{
    ui->setupUi(this);
    connect(ui->PB_CLEAR, &QPushButton::clicked, [=](bool clicked)
    {
        Q_UNUSED(clicked)
        ui->TB_CHAT->clear();
    });
    ui->TB_CHAT->setStyleSheet("background-color: rgb(105, 105, 105);");
    bot = Bot;
    character = nullptr;
    partner = nullptr;
    nosmate = nullptr;
    botWorking = false;
    chat = nullptr;
    inventoryConnected = false;
    ai = new ArtificialIntelligence(this);
    ai->setSit(ui->W_BEHAVIOUR->getHP(), ui->W_BEHAVIOUR->getMP(), ui->W_BEHAVIOUR->getHPGetUp(), ui->W_BEHAVIOUR->getMPGetUp());
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::petAIChanged, [=](MateAI aiType){ ai->setPetAI(aiType); });
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::partnerAIChanged, [=](MateAI aiType){ ai->setPartnerAI(aiType); });
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::sitLowerThan, [=](int hp, int mp, int hpGU, int mpGU){ ai->setSit(hp, mp, hpGU, mpGU); });
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::goToMinilandEvery, [=](int seconds){ ai->setGoToMLDelay(seconds); });
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::stayInMinilandFor, [=](int seconds){ ai->setStayMLDelay(seconds); });
    connect(ui->W_BEHAVIOUR, &BehaviourWidget::distDropChanged, [=](int range){ ai->setDropDistance(range); });

    connect(ui->W_PATHING, &PathingWidget::onPathingChanged, [=](PathingType pT, QPair<int, int> arg1, QVector<QPair<int, int>> way)
    { ai->setPathing(pT, arg1, way); });

    connect(ui->W_MAP, &MapWidget::leftClicked, [=](QPoint pos)
    {
        if (!character)
            return;
        Vec2i way = character->walk(pos.x(), pos.y());
        if(partner)
            partner->walk(way.x, way.y, qrand()%2 + 1, false);
        if(nosmate)
            nosmate->walk(way.x, way.y, qrand()%2 + 1, false);
    });

    connect(ui->W_MAP, &MapWidget::rightClicked, [=](QPoint pos)
    {
        Portal portal = ui->W_MAP->getNearestPortal(pos);
        if(PathFinding::distance({ portal.getX(), portal.getY() }, { pos.x(), pos.y() }) < 7)
            character->takePortal(portal);
    });
    /*static QVector<QPoint> path; // static = PROBLEM !!!
    connect(ui->L_MAP_1, &ClickableLabel::leftClicked, [=](QPoint point)
    {
        character->walk(point.x()/2, point.y()/2);
        qDebug() << "LC : " << point/2;
        qDebug() << path;
        size_t i = 0;
        connect(character, &MyCharacter::onDestination, [=](int x, int y) mutable
        {
            qDebug() << "Emited";
            qDebug() << i << path.size();
            if(x == path[i].x() && y == path[i].y() && i + 1 < path.size())
            {
                i++;
                qDebug() <<"Point :  "<< i << path[i];
                character->walk(path[i].x(), path[i].y());
            }
            else if(i == path.size() - 1)
            {
                path.clear();
                i = 0;
            }
        });
        if(path.size() > 0)
        {
            qDebug() << "Walk";
            character->walk(path[0].x(), path[0].y());
        }
    });
    connect(ui->L_MAP_1, &ClickableLabel::rightClicked, [=](QPoint point) mutable
    {
        qDebug() << "RC : " << point/2;
        path.push_back(point/2);
        qDebug() << path;
    });*/

    connect(ui->W_SKILLS, &SkillsWidget::usableSkillsChanged, [=](QMap<int, UsableSkill> usableSkills)
    {
        ai->setUsableSkills(usableSkills);
    });
    connect(ui->W_SKILLS, &SkillsWidget::partnerUsableSkillsChanged, [=](QMap<int, UsableSkill> partnerUsableSkills)
    {
        ai->setPartnerUsableSkills(partnerUsableSkills);
    });
    connect(ui->W_SKILLS, &SkillsWidget::nosmateUsableSkillsChanged, [=](QMap<int, UsableSkill> nosmateUsableSkills)
    {
        ai->setNosmateUsableSkills(nosmateUsableSkills);
    });

    connect(ui->W_USERS, &UsersWidget::sendPartyRequest,  [=](Player player){ bot->inviteParty(player);  });
    connect(ui->W_USERS, &UsersWidget::sendBlacklist,     [=](Player player){ bot->blacklist(player);    });
    connect(ui->W_USERS, &UsersWidget::sendFriendRequest, [=](Player player){ bot->inviteFriend(player); });
    connect(ui->W_USERS, &UsersWidget::selectedPlayer,    [=](Player player){ ui->W_MAP->characterTargettedMoved(player.getX(), player.getY()); });

    connect(ui->W_HEADER, &HeaderWidget::disconnectFromGame, [=]
    {
        bot->disconnectFromServer();
        emit disconnectFromServer();
    });
    connect(ui->W_HEADER, &HeaderWidget::botStatusChanged, [=](bool working)
    {
        ai->setState(working);
        ai->resetTarget();
        if(!working)
            character->stopMoving();
    });
    connect(ui->W_HEADER, &HeaderWidget::toggleSP, [=]{ if(character) character->toggleSP(); });
    connect(ui->W_HEADER, &HeaderWidget::leaveGroup, [=]{ if(character->getGroupID() != -1) bot->quitGroup(); });
    connect(ui->W_HEADER, &HeaderWidget::selfishGroup, [=]{ if(character->getGroupID() != -1) bot->toggleOption(BlockingOption::GROUP_SHARING, 1); });
    connect(ui->W_HEADER, &HeaderWidget::sharingGroup, [=]{ if(character->getGroupID() != -1) bot->toggleOption(BlockingOption::GROUP_SHARING, 0); });

    connect(ui->W_HEADER, &HeaderWidget::toggleSPP, [=]
    {
        if(partner)
           partner->toggleSP();
    });

    connect(ui->W_SECURITY, &SecurityWidget::toggleOption, [=](BlockingOption option, bool activated){ bot->toggleOption(option, activated); });
    connect(ui->W_SECURITY, &SecurityWidget::askForStopping, [=]{ ai->setState(false); });
    connect(ui->W_SECURITY, &SecurityWidget::askForDisconnection, [=]{ bot->disconnectFromServer(); });

    connect(bot, &BotManager::worldCreated, this, &BotWidget::worldCreated);
    connect(bot, &BotManager::groupCreated, this, &BotWidget::groupCreated);
    connect(bot, &BotManager::morphChanged, this, &BotWidget::morphChanged);
    connect(bot, &BotManager::getPartner, this, [=](MyPartner *Partner)
    {
        partner = Partner;
        if(partner)
        {
            ai->setWorld(map, partner);
            connect(partner, &MyPartner::newSkills, [=](QMap<int, Skill*> skills){ ui->W_SKILLS->setPartnerSkills(skills); });
            connect(partner, &MyPartner::moved, [=](int x, int y){ ai->sendPartnerPosToCharacter(x, y); });
        }
    });
    connect(bot, &BotManager::getNosmate, this, [=](MyNosmate *Nosmate)
    {
        nosmate = Nosmate;
        if(nosmate)
        {
            ai->setWorld(map, nosmate);
            connect(nosmate, &MyNosmate::newSkills, [=](QMap<int, Skill*> skills){ ui->W_SKILLS->setNosmateSkills(skills); });
            connect(nosmate, &MyNosmate::moved, [=](int x, int y){ ai->sendPetPosToCharacter(x, y); });
        }
    });
    connect(bot, qOverload<PacketDlgi>(&BotManager::newQuestion), [=](PacketDlgi Packet)
    {
        if(Packet.getSentanceID() == 570) // Death
        {
            if(ui->W_BEHAVIOUR->disconnectOnDeath())
                QTimer::singleShot(300 + qrand() % 2500, [=]{ bot->disconnectFromServer(); });
            else if(ui->W_BEHAVIOUR->repopOnDeath())
                QTimer::singleShot(300 + qrand() % 2500, [=]{ qDebug() << Packet.getPacketToAccept(); bot->sendPacket(Packet.getPacketToAccept(), true); });
            else if(ui->W_BEHAVIOUR->worOnDeath())
                QTimer::singleShot(300 + qrand() % 2500, [=]
                {
                    bot->sendPacket(Packet.getPacketToDeny(), true);
                    QTimer::singleShot(300 + qrand() % 2500, [=]
                    {
                        SubInventory *etc = character->getInventory()->getSubinventory(InventoryType::ETC);
                        etc->useItem(etc->getItemSlotFromID(2071), EntityType::PLAYER, character->getCharacterID());
                    });
                });
            else
                QTimer::singleShot(300 + qrand() % 2500, [=]{ bot->sendPacket(Packet.getPacketToDeny()); });
        }
    });
    connect(bot, qOverload<PacketDlgi2>(&BotManager::newQuestion), [=](PacketDlgi2 Packet)
    {
        if(Packet.getSentanceID() == 233) // Group
        {
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText(Packet.getSentanceVariables() + " invited you in group.");
            msgBox->setWindowTitle("Group request");
            msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::No);
            connect(msgBox, &QMessageBox::accepted, [=]{ bot->sendPacket(Packet.getPacketToAccept(), true); delete msgBox; });
            connect(msgBox, &QMessageBox::rejected, [=]{ bot->sendPacket(Packet.getPacketToDeny(), true); delete msgBox; });
            msgBox->show();
        }
    });
    connect(bot, qOverload<PacketRp>(&BotManager::newQuestion), [=](PacketRp Packet)
    {
        QTimer::singleShot(1000+qrand()%2500, [=]{ bot->sendPacket(Packet.getPacketToAccept(), true); });
    });
    connect(ui->W_MONSTERS, &MonsterWidget::monsterFilter, [=](QList<int> monstersID, MonsterListType listType){ ai->setFilter(monstersID, listType); });
    connect(ui->W_DROPS, &DropWidget::dropFilter, [=](QList<int> DropID, DropListType ListType){ ai->setFilter(DropID, ListType); });
}

BotWidget::~BotWidget()
{
    delete ui;
    delete bot;
    delete ai;
}

void BotWidget::setServerConnectionInfos(short serv, short chan, QString locale)
{
    ui->W_HEADER->setServerConnectionInfos(serv, chan, locale);
}

void BotWidget::on_LE_CHAT_returnPressed()
{
    QString msg = ui->LE_CHAT->text();
    chat->sendRawMessage(msg);
    ui->TB_CHAT->insertPlainText("> " + msg + "\n");
    ui->LE_CHAT->clear();
}

void BotWidget::worldCreated(MyCharacter *Character, Map *Map)
{
    map = Map;
    character = Character;
    chat = bot->getChatInstance();

    ai->setWorld(map, character);
    ui->W_MAP->setMap(map);
    ui->W_USERS->setMap(map);
    ui->L_MAP_NAME->setText(map->getMapName());
    setWindowTitle(character->getPseudonym());
    int imgId = 32000 + static_cast<int>(character->getGender()) * 20 + static_cast<int>(character->getClass()) * 40;
    ui->W_HEADER->setOwnCharacterInformation(character->getPseudonym(), QPixmap(QApplication::applicationDirPath() + "/images/" + QString::number(imgId) + ".png"));
    connect(map, &Map::newPlayer, this, &BotWidget::newPlayer);
    connect(map, &Map::mapInOut, [=](){ ui->W_USERS->inOut(); ui->W_MAP->characterTargettedMoved(-1, -1); });
    connect(chat, &ChatInstance::messageReceived, this, &BotWidget::handleMessages);
    connect(map, &Map::mapUpdate, this, &BotWidget::mapUpdated);
    connect(map, &Map::mapChanged, this, &BotWidget::mapChanged);
    connect(character, &MyCharacter::characterUpdate, this, &BotWidget::characterUpdate);
    connect(character, &MyCharacter::inventoryUpdate, this, &BotWidget::inventoryUpdate);
    connect(character, &MyCharacter::moved, [=](int x, int y){ ui->W_MAP->characterMoved(x, y); });
    qDebug() << "Connection...";
    connect(character, &MyCharacter::newSkills, [=](QMap<int, Skill*> skills)
    {
        qDebug() << "New skills detected";
        ui->W_SKILLS->setSkills(skills);
        ai->newCharacterSkills();
    });
    qDebug() << "... ok";
    ui->W_MAP->characterMoved(character->getX(), character->getY());
    ui->W_SKILLS->setSkills(character->getSkills());
    ai->newCharacterSkills();
    ui->W_DROPS->mapUpdated(map);
    ui->W_PATHING->setMap(map);
}

void BotWidget::mapChanged(/*Map *Map*/)
{
    ui->L_MAP_NAME->setText(map->getMapName());
    ui->W_MAP->setMap(map);
    ui->W_MAP->characterMoved(character->getX(), character->getY());
    ui->W_MAP->mapUpdated();
    ui->W_USERS->clear();
    ui->W_MONSTERS->mapUpdated(map);
    ui->W_DROPS->mapUpdated(map);
    ui->W_PATHING->setMap(map);
}

void BotWidget::characterUpdate(/*MyCharacter *Character*/)
{
    Statistics stats = character->getStatsProperties();
    ui->W_HEADER->setStatistics(stats);
    if(ai->isWorking() || ui->W_ITEMS->shouldContinueOnStop())
    {
        QVector<ItemCondition*> items = ui->W_ITEMS->getItemsCondition();
        for(int i = 0 ; i < items.size() ; i++)
        {
            ItemCondition* tmp = items[i];
            if(!tmp->mustBeUsed(stats))
                continue;
            int timer = i * 1000 + qrand() % 150;
            tmp->setLastUsage(QDateTime::currentDateTime().addMSecs(timer));
            QTimer::singleShot(timer, [=]
            {
                SubInventory *subInv = character->getInventory()->getSubinventory(tmp->getItem().first);
                subInv->useItem(subInv->getItemSlotFromID(tmp->getItem().second), EntityType::PLAYER, character->getCharacterID());
            });
        }
    }

    Level level = character->getLevelProperties();
    ui->W_HEADER->setLevels(level);
}

void BotWidget::inventoryUpdate(/*Inventory *inv*/)
{
    Inventory *inv = character->getInventory();
    if(!inventoryConnected)
    {
        inventoryConnected = true;
        connect(ui->W_INVENTORY, &InventoryWidget::tryToUseItem, this, [=](InventoryType type, short cell)
        {
            inv->getSubinventory(type)->useItem(cell, EntityType::PLAYER, character->getCharacterID());
        });
        connect(ui->W_INVENTORY, &InventoryWidget::tryToShowItem, this, [=](int type, int cell)
        {
            inv->getSubinventory(static_cast<InventoryType>(type))->getItemsInfos(type, cell);
        });
    }
    ui->W_INVENTORY->treatInventory(inv);
    ui->W_ITEMS->treatInventory(inv);
}

void BotWidget::morphChanged(PacketC_mode Packet)
{
    bool isSp = Packet.getMorphID() != 0 ? true : false;
    int imgId = isSp ? 32498 + Packet.getMorphID() * 2 + static_cast<int>(character->getGender()) * 2 : 32000 + static_cast<int>(character->getGender()) * 20 + static_cast<int>(character->getClass()) * 40;
    ui->W_HEADER->setOwnCharacterInformation(nullptr, QPixmap(QApplication::applicationDirPath() + "/images/" + QString::number(imgId) + ".png"));
}

void BotWidget::groupCreated(Group group)
{
    if(character != nullptr)
        ui->W_HEADER->setGroup(group, character->getCharacterID());
}

void BotWidget::handleMessages()
{
    QVector<Message*> msg = chat->getPendingMessages();
    QTextCursor textCursor = ui->TB_CHAT->textCursor();
    textCursor.movePosition(QTextCursor::End);
    ui->TB_CHAT->setTextCursor(textCursor);
    for(int i = 0 ; i < msg.size() ; i++)
    {
        if(ui->W_SECURITY->isSpeakerBlocked())
        {
            if(msg[i]->getChatType() == ChatType::MESSAGE_SPEAKER || msg[i]->getChatType() == ChatType::MESSAGE_SPEAKER_ITEM)
                continue;
        }
        ui->TB_CHAT->setTextColor(msg[i]->getColor());
        ui->TB_CHAT->insertPlainText("[" + msg[i]->getPseudonym() + "]: " + msg[i]->getMessage() + "\n");
        if(ui->W_SECURITY->shouldBlacklistOnWhisper() && (msg[i]->getChatType() == ChatType::WHISPER_PLAYER || msg[i]->getChatType() == ChatType::WHISPER_PLAYER_2))
            QTimer::singleShot(1500 + qrand() % 5000, [=]{bot->blacklist(msg[i]->getPseudonym());});
    }
    ui->TB_CHAT->verticalScrollBar()->setValue(ui->TB_CHAT->verticalScrollBar()->maximum());
    chat->flush();
}

void BotWidget::mapUpdated(/*Map *Map*/)
{
    ui->W_MAP->mapUpdated();
    ui->W_MONSTERS->mapUpdated(map);
    ui->W_DROPS->mapUpdated(map);
}

void BotWidget::newPlayer(Player player)
{
    if(ui->W_SECURITY->shouldBeepOnPlayerPop())
        ui->W_SECURITY->alert();
    if(ui->W_SECURITY->shouldStopOnPlayerPop())
    {
        if(ai->isWorking())
            ui->W_HEADER->toggleBot();
    }
    if(ui->W_SECURITY->shouldDisconnectOnPlayerPop())
        bot->disconnectFromServer();
    if(player.getAuthority() == Authority::GM)
    {
        if(ui->W_SECURITY->shouldBeepOnGMPop())
            ui->W_SECURITY->alert();
        if(ui->W_SECURITY->shouldStopOnGMPop())
        {
            if(ai->isWorking())
                ui->W_HEADER->toggleBot();
        }
        if(ui->W_SECURITY->shouldDisconnectOnGMPop())
            bot->disconnectFromServer();
    }
}
