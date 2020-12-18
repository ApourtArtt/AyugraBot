#include "bot.h"

Bot::Bot(QString xHash, QString hash, QString version, QObject *parent)
    : QObject(parent)
{
    qsrand(static_cast<uint>(QTime::currentTime().msecsSinceStartOfDay()));
    world = false;
    serv = nullptr;
    creds = nullptr;
    eventManager = new EventManager(this);
    chat = new ChatInstance(this);
    map = nullptr;
    character = nullptr;
    nosmate = nullptr;
    partner = nullptr;
    mNet = new Network(this);
    mNet->configureCryptography(xHash, hash, version);
    connect(chat, &ChatInstance::sendPacket, this, [=](QString packet, bool privilege){sendPacket(packet, privilege);});
    connect(mNet, &Network::sig_sentPacket, this, &Bot::getSentPacket);
    connect(mNet, &Network::sig_recievedPacket, this, &Bot::recievedPacket);
    connect(mNet, &Network::sig_connected, this, &Bot::connected);
    connect(mNet, &Network::sig_disconnected, this, &Bot::disconnected);
    connect(eventManager, &EventManager::sendPacket, this, [=](QString packet){sendPacket(packet, false);});
    connect(eventManager, &EventManager::newEvent, this, [=](EventType eventType){emit newEvent(eventType);});
}

Bot::~Bot()
{
    delete character;
    delete nosmate;
    delete partner;
    delete map;
    delete mNet;
    delete creds;
    delete eventManager;
    delete chat;
}

void Bot::recievedPacket(QStringList packet)
{
    if(!packet.startsWith("mv"))
        qInfo() << "Rcvd: " << packet;
    if(packet[0] == "guri")
    {
        qDebug() << "Returned : " << packet;
        return;
    }
    emit getRecievedPacket(PacketToHeader.value(packet[0]), packet);
    if(!PacketToHeader.contains(packet[0]))
    {
        //qDebug() << "Unhandled packet header : " << packet[0];
        //qDebug() << packet;
        return;
    }
    parsePacket(packet);
}

void Bot::connected()
{
    if(serv->getServerType() == ServerType::NONE)
        serv->setServerType(ServerType::LOGIN);
    else if(serv->getServerType() == ServerType::LOGIN)
        serv->setServerType(ServerType::GAME);
    if(creds->isValid())
    {
        if(serv->getServerType() == ServerType::LOGIN && serv->getIP() != nullptr && serv->getPort() != 0)
            mNet->connectWithCredentials(creds);
        else if(serv->getServerType() == ServerType::GAME && serv->getServer() > -1 && serv->getChannel() > -1)
            mNet->connectWithCredentials(creds);
    }
}

void Bot::disconnected()
{
    if(serv->getServerType() == ServerType::LOGIN)
    {
        if(serv->isReadyForWorld())
            mNet->connectToGS(serv->getEncryptionKey(), serv->getIP(), serv->getPort());
        /*else
        {
            serv->setServerType(ServerType::NONE);
        }*/
    }
    else if (serv->getServerType() == ServerType::GAME)
    {
        serv->setServerType(ServerType::NONE);
    }
}

bool Bot::login(QString username, QString password, QString gfuid, ConnectionType connectionType, Lang lang,
                QString loginServerIP, unsigned short loginServerPort,
                short server, short channel)
{
    if(serv != nullptr)
    {
        if(serv->getServerType() != ServerType::NONE)
            return false;
        else
            delete serv;
    }
    if(creds != nullptr)
        delete creds;
    creds = new Credentials(username, password, connectionType, lang, gfuid, this);
    serv = new Server(loginServerIP, loginServerPort, server, channel, this);
    if(!mNet->isConfigured() || !mNet->connectToLS(serv))
        return false;
    return true;
}

bool Bot::connectToGame(QString gameIP, unsigned short gamePort, short server, short channel)
{
    serv->setIP(gameIP);
    serv->setPort(gamePort);
    serv->setServer(server);
    serv->setChannel(channel);
    if(serv->isReadyForWorld())
    {
        mNet->connectToGS(serv->getEncryptionKey(), serv->getIP(), serv->getPort());
        return true;
    }
    return false;
}

void Bot::disconnectFromServer()
{
    mNet->disconnectFromServer();
}

bool Bot::sendPacket(QString packet, bool privilege)
{
    if(!privilege)
    {
        if(PacketToType.value(packet.mid(0, packet.indexOf(' '))) == PacketType::SERVER) return false;
    }
    return mNet->send(packet, privilege);
}

bool Bot::selectCharacter(short slot)
{
    if(serv->getServerType() == ServerType::GAME)
    {
        QVector<MyCharacter*> characters = creds->getAvailableCharacters();
        int i;
        for(i = 0 ; i < characters.size() ; i++)
        {
            if(characters[i]->getSlot() == slot)
            {
                mNet->send(PacketSelect(slot).getPacket());
                return true;
            }
        }
    }
    return false;
}

bool Bot::selectCharacter(QString pseudonym)
{
    if(serv->getServerType() == ServerType::GAME)
    {
        short slot = 0;
        QVector<MyCharacter*> characters = creds->getAvailableCharacters();
        int i;
        for(i = 0 ; i < characters.size() ; i++)
        {
            if(characters[i]->getPseudonym() == pseudonym)
            {
                slot = characters[i]->getSlot();
                mNet->send(PacketSelect(slot).getPacket());
                return true;
            }
        }
    }
    return false;
}

bool Bot::deleteCharacter(short slot)
{
    if(serv->getServerType() == ServerType::GAME)
    {
        QVector<MyCharacter*> characters = creds->getAvailableCharacters();
        for(int i = 0 ; i < characters.size() ; i++)
        {
            if(characters[i]->getSlot() == slot)
            {
                mNet->send(PacketChar_DEL(slot, creds->getUsername()).getPacket());
                return true;
            }
        }
    }
    return false;
}

bool Bot::createCharacter(Class charClass, QString pseudo, short slot, Gender gender, HairStyle hStyle, short hColor)
{
    if(serv->getServerType() == ServerType::GAME)
    {
        bool exist = false;
        QVector<MyCharacter*> characters = creds->getAvailableCharacters();
        for(int i = 0 ; i < characters.size() ; i++)
        {
            if(characters[i]->getSlot() == slot)
                exist = true;
        }
        if(!exist)
        {
            if(charClass == Class::ADVENTURER)
            {
                return mNet->send(PacketChar_NEW(pseudo, slot, gender, hStyle, hColor).getPacket());
            }
            else if(charClass == Class::MARTIAL_ARTIST)
            {
                return mNet->send(PacketChar_NEW_JOB(pseudo, slot, gender, hStyle, hColor).getPacket());
            }
        }
    }
    return false;
}

void Bot::subscribeToEvent(EventType event)
{
    eventManager->subscribeToEvent(event, true);
}

void Bot::unsubscribeFromEvent(EventType event)
{
    eventManager->unsubscribeFromEvent(event);
}

ChatInstance *Bot::getChatInstance()
{
    return chat;
}

void Bot::toggleOption(BlockingOption option, bool activated)
{
    mNet->send(PacketGop(option, activated).getPacket());
}

void Bot::parsePacket(QStringList packet)
{
    PacketIdentifier header = PacketToHeader.value(packet[0]);
    if(header == PacketIdentifier::NsTeST)              emit recievedAvailableServers(serv->handleServerPacket(packet));
    else if(header == PacketIdentifier::failc)          emit loginError(serv->getError(packet));
    else if(header == PacketIdentifier::info)           emit info(PacketInfo(packet).getMessage());
    else if(header == PacketIdentifier::at)             handlePacket_at(packet);
    else if(header == PacketIdentifier::clist_end)      handlePacket_clist_end();
    else if(header == PacketIdentifier::OK)             handlePacket_OK();
    else if(header == PacketIdentifier::c_info)         handlePacket_c_info(packet);
    else if(header == PacketIdentifier::sc_p_stc)       handlePacket_sc_p_stc(packet);
    else if(header == PacketIdentifier::clist_start)    creds->emptyCharacterList();
    else if(header == PacketIdentifier::clist)          creds->newCharacter(packet);
    else if(header == PacketIdentifier::lev)            character->handleLevPacket(packet);
    else if(header == PacketIdentifier::fd)             character->handleFdPacket(packet);
    else if(header == PacketIdentifier::stat)           character->handleStatPacket(packet);
    else if(header == PacketIdentifier::rsfi)           character->handleRsfiPacket(packet);
    else if(header == PacketIdentifier::cond)           handleCondPacket(packet);
    else if(header == PacketIdentifier::inv)            character->handleInvPacket(packet);
    else if(header == PacketIdentifier::ivn)            character->handleIvnPacket(packet);
    else if(header == PacketIdentifier::gold)           character->handleGoldPacket(packet);
    else if(header == PacketIdentifier::ski)            character->handleSkiPacket(packet);
    else if(header == PacketIdentifier::cancel)         character->handleCancelPacket(packet);
    else if(header == PacketIdentifier::sr)             character->handleSrPacket(packet);
    else if(header == PacketIdentifier::mslot)          character->handleMslotPacket(packet);
    else if(header == PacketIdentifier::c_map)          map->handleC_mapPacket(packet);
    else if(header == PacketIdentifier::in)             handleInPacket(packet);
    else if(header == PacketIdentifier::wp)             map->handleWpPacket(packet);
    else if(header == PacketIdentifier::gp)             map->handleGpPacket(packet);
    else if(header == PacketIdentifier::drop)           map->handleDropPacket(packet);
    else if(header == PacketIdentifier::get)            map->handleGetPacket(packet);
    else if(header == PacketIdentifier::out)            handleOutPacket(packet);
    else if(header == PacketIdentifier::die)            map->handleDiePacket(packet);
    else if(header == PacketIdentifier::mv)             map->handleMvPacket(packet);
    else if(header == PacketIdentifier::shop)           map->handleShopPacket(packet);
    else if(header == PacketIdentifier::su)             map->handleSuPacket(packet);
    else if(header == PacketIdentifier::qnamli)         eventManager->handleQnamliPacket(packet);
    else if(header == PacketIdentifier::esf)            eventManager->handleEsfPacket(packet);
    else if(header == PacketIdentifier::pinit)          handlePacket_pinit(packet);
    else if(header == PacketIdentifier::c_mode)         handlePacket_c_mode(packet);
    else if(header == PacketIdentifier::sayi2)          chat->handleSayi2Packet(packet);
    else if(header == PacketIdentifier::say)            handleSayPacket(packet);
    else if(header == PacketIdentifier::sayt)           chat->handleSaytPacket(packet);
    else if(header == PacketIdentifier::spk)            chat->handleSpkPacket(packet);
    else if(header == PacketIdentifier::delay)          character->handleDelayPacket(packet);
    else if(header == PacketIdentifier::pski)           partner->handlePskiPacket(packet);
    else if(header == PacketIdentifier::pdelay)         partner->handlePdelayPacket(packet);
    else if(header == PacketIdentifier::dpski)          handleDpskiPacket(packet);
    else if(header == PacketIdentifier::pst)            handlePstPacket(packet);
    else if(header == PacketIdentifier::psr)            partner->handlePsrPacket(packet);
    else if(header == PacketIdentifier::petski)         handlePetskiPacket(packet);
    else if(header == PacketIdentifier::petsr)          nosmate->handlePetsrPacket(packet);
    else if(header == PacketIdentifier::dlgi)           emit newQuestion(PacketDlgi(packet));
    else if(header == PacketIdentifier::dlgi2)          emit newQuestion(PacketDlgi2(packet));
    else if(header == PacketIdentifier::rp)             emit newQuestion(PacketRp(packet));
    else if(header == PacketIdentifier::eff)            map->handleEffPacket(packet);
    else if(header == PacketIdentifier::rest)           handleRestPacket(packet);

    else
    {
        //qDebug() << " -- Unhandled packet : " << packet;
    }

}

void Bot::sendCloseFStashEnd()
{
    mNet->send(PacketC_close(1).getPacket());
    mNet->send(PacketF_stash_end().getPacket());
    mNet->send(PacketC_close(0).getPacket());
}

void Bot::handlePacket_OK()
{
    mNet->send(PacketGame_start().getPacket());
    mNet->send(PacketLbs(0).getPacket());
    mNet->startPulsing();
    map = new Map(this);
    character = new MyCharacter(this);
    connect(character, &MyCharacter::sendPacket, this, [this](QString packet, bool privilege){ sendPacket(packet, privilege); });
}

void Bot::handlePacket_c_info(QStringList packet)
{
    character->handleC_infoPacket(packet);
    mNet->send(PacketC_close(1).getPacket());
}

void Bot::handlePacket_at(QStringList packet)
{
    map->handleAtPacket(packet);
    character->handleAtPacket(packet);
    if(partner)
        partner->handleAtPacket(packet);
    if(nosmate)
        nosmate->handleAtPacket(packet);
    if(!world)
    {
        world = true;
        emit worldCreated(character, map);
    }
}

void Bot::handlePacket_pinit(QStringList packet)
{
    group.handlePinitPacket(packet);
    emit groupCreated(group);
}

void Bot::handlePacket_c_mode(QStringList packet)
{
    PacketC_mode Packet(packet);
    if(Packet.getEntityID() == character->getCharacterID())
        emit morphChanged(packet);
    if(group.handleC_modePacket(Packet))
        emit groupCreated(group);
}

void Bot::handleSayPacket(PacketSayR packet)
{
    QString pseudonym = map->getPlayerList().value(packet.getEntityID()).getName();
    chat->handleSayRPacket(packet, pseudonym);
}

void Bot::handleInPacket(BasePacketIn packet)
{
    map->handleInPacket(packet);
    if(packet.getEntityType() != EntityType::NOSMATE_NPC)
        return;
    PacketIn23 p = packet.getPacketsPart();
    if(p.getOwnerID() == character->getCharacterID())
    {
        if(p.isPartner())
        {
            if(!partner)
            {
                partner = new MyPartner(map->getMapID(), this);
                connect(partner, &MyPartner::sendPacket, this, [=](QString packet, bool privilege){ sendPacket(packet, privilege); });
            }
            partner->handleInPacket(p);
            emit getPartner(partner);
        }
        else
        {
            if(!nosmate)
            {
                nosmate = new MyNosmate(map->getMapID(), this);
                connect(nosmate, &MyNosmate::sendPacket, this, [=](QString packet, bool privilege){ sendPacket(packet, privilege); });
            }
            nosmate->handleInPacket(p);
            emit getNosmate(nosmate);
        }
    }
}

void Bot::handleCondPacket(PacketCond packet)
{
    if(packet.getEntityType() == EntityType::PLAYER)
        character->handleCondPacket(packet);
    else if(packet.getEntityType() == EntityType::NOSMATE_NPC)
    {
       if(partner)
       {
           if(packet.getID() == partner->getPartnerID())
               partner->handleCondPacket(packet);
       }
       if(nosmate)
       {
           if(packet.getID() == nosmate->getNosmateID())
               nosmate->handleCondPacket(packet);
       }
    }
}

void Bot::handleOutPacket(PacketOut packet)
{
    map->handleOutPacket(packet);
    if(partner)
    {
        //if(packet.getID() == partner->getPartnerID())
          //  delete partner;
    }
    if(nosmate)
    {

    }
}

void Bot::handlePetskiPacket(QStringList packet)
{
    if(nosmate)
        nosmate->handlePetskiPacket(packet);
}

void Bot::handleRestPacket(PacketRestR Packet)
{
    qDebug() << "Packet Rest : " << Packet.getPacketToDisplay();
    qDebug() << Packet.getEntityID() << QString::number(static_cast<int>(Packet.getEntityType()));
    if(Packet.getEntityID() == character->getCharacterID() && Packet.getEntityType() == EntityType::PLAYER)
    {
        character->setResting(Packet.isResting());
        return; // To avoid function going to map object
    }
    else if(Packet.getEntityType() == EntityType::NOSMATE_NPC)
    {
        if(nosmate && Packet.getEntityID() == nosmate->getNosmateID())
        {}
        else if(partner && Packet.getEntityID() == partner->getPartnerID())
        {}
    }
    map->handleRestPacket(Packet);
}

void Bot::handlePstPacket(PacketPst packet)
{
    if(partner)
    {
        if(partner->getPartnerID() == packet.getEntityID())
            partner->handlePstPacket(packet);
    }
    if(nosmate)
    {
        if(nosmate->getNosmateID() == packet.getEntityID())
            nosmate->handlePstPacket(packet);
    }
}

void Bot::handlePacket_sc_p_stc(QStringList packet)
{
    //send to character and then
    mNet->send(PacketNpinfo(0).getPacket());
}

void Bot::handleDpskiPacket(QStringList packet)
{
    if (!partner)
        return;
    partner->handleDpskiPacket(packet);
}

void Bot::handlePacket_clist_end()
{
    sendCloseFStashEnd();
    emit recievedAvailableCharacters(creds->getAvailableCharacters());
}

void Bot::blacklist(Player player)
{
    mNet->send(PacketBlins(player.getID()).getPacket());
}

void Bot::blacklist(QString pseudo)
{
    mNet->send("$bl " + pseudo, true);
}

void Bot::inviteParty(Player player)
{
    if (player.getGroupID() != -1)
        mNet->send(PacketPjoin(PartyRequestType::INVITED, player.getID()).getPacket());
    else
        mNet->send(PacketPjoin(PartyRequestType::REQUESTED, player.getID()).getPacket());
}

void Bot::inviteParty(QString pseudo)
{
    mNet->send("$pinv " + pseudo, true);
}

void Bot::inviteFriend(Player player)
{
    mNet->send(PacketFins(player.getID()).getPacket());
}

void Bot::inviteFriend(QString pseudo)
{
    mNet->send("$fl " + pseudo, true);
}

void Bot::quitGroup()
{
    mNet->send(PacketPleave().getPacket());
}
