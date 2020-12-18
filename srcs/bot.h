#ifndef BOT_H
#define BOT_H

#include <QtConcurrent>
#include <QObject>
#include <QTime>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/GameObjects/Entity/mypartner.h"
#include "srcs/GameObjects/Entity/mynosmate.h"
#include "srcs/Net/network.h"
#include "srcs/Net/credentials.h"
#include "srcs/Net/server.h"
#include "srcs/GameObjects/Instance/chatinstance.h"
#include "srcs/Packets/Client/World/packetselect.h"
#include "srcs/Packets/Client/World/packetgame_start.h"
#include "srcs/Packets/Client/World/packetlbs.h"
#include "srcs/Packets/Client/World/packetc_close.h"
#include "srcs/Packets/Client/World/packetf_stash_end.h"
#include "srcs/Packets/Client/World/packetchar_del.h"
#include "srcs/Packets/Client/World/packetchar_new.h"
#include "srcs/Packets/Client/World/packetchar_new_job.h"
#include "srcs/Packets/Server/World/packetinfo.h"
#include "srcs/Packets/Client/World/packetnpinfo.h"
#include "srcs/Packets/Client/World/packetmvi.h"
#include "srcs/Packets/Server/World/packetpinit.h"
#include "srcs/Packets/Server/World/packetc_mode.h"
#include "srcs/GameObjects/Event/eventmanager.h"
#include "srcs/GameObjects/Properties/group.h"
#include "srcs/Packets/Client/World/packetgop.h"
#include "srcs/Packets/Client/World/packetblins.h"
#include "srcs/Packets/Client/World/packetpjoin.h"
#include "srcs/Packets/Client/World/packetfins.h"
#include "srcs/Packets/Server/World/packetdlgi.h"
#include "srcs/Packets/Server/World/packetdlgi2.h"
#include "srcs/Packets/Server/World/packetrp.h"
#include "srcs/Packets/Client/World/packetpleave.h"

class Bot : public QObject
{
    Q_OBJECT
public:
    explicit Bot(QString xHash, QString hash, QString version, QObject *parent = nullptr);
    ~Bot();
    bool login(QString username, QString password, QString gfuid, ConnectionType connectionType, Lang lang, QString loginServerIP, unsigned short loginServerPort, short server = -1, short channel = -1);
    bool connectToGame(QString gameIP, unsigned short gamePort, short server, short channel);
    bool selectCharacter(short slot);
    bool selectCharacter(QString pseudonym);
    bool deleteCharacter(short slot);
    bool createCharacter(Class charClass, QString pseudo, short slot, Gender gender, HairStyle hStyle, short hColor);
    void disconnectFromServer();
    bool sendPacket(QString packet, bool privilege = false);
    void subscribeToEvent(EventType event);
    void unsubscribeFromEvent(EventType event);
    ChatInstance *getChatInstance();
    void toggleOption(BlockingOption option, bool activated);
    void blacklist(Player player);
    void blacklist(QString pseudo);
    void inviteParty(Player player);
    void inviteParty(QString pseudo);
    void inviteFriend(Player player);
    void inviteFriend(QString pseudo);
    void quitGroup();

signals:
    void newQuestion(PacketDlgi Packet);
    void newQuestion(PacketDlgi2 Packet);
    void newQuestion(PacketRp Packet);
    void newEvent(EventType eventType);
    void worldCreated(MyCharacter *character, Map *map);
    void getSentPacket(QString packet);
    void getRecievedPacket(PacketIdentifier header, QStringList packet);
    void recievedAvailableCharacters(QVector<MyCharacter*> charList);
    void recievedAvailableServers(QVector<serverIdentity> servList);
    void getPartner(MyPartner *partner);
    void getNosmate(MyNosmate *nosmate);
    void loginError(FailcType error);
    void info(QString msg);
    void groupCreated(Group group);
    void morphChanged(PacketC_mode Packet);

public slots:
    void recievedPacket(QStringList packet);
    void connected();
    void disconnected();

private:
    void sendCloseFStashEnd();
    void parsePacket(QStringList packet);
    void handlePacket_OK();
    void handlePacket_clist_end();
    void handlePacket_sc_p_stc(QStringList packet);
    void handlePacket_c_info(QStringList packet);
    void handlePacket_at(QStringList packet);
    void handlePacket_pinit(QStringList packet);
    void handlePacket_c_mode(QStringList packet);
    void handleSayPacket(PacketSayR packet);
    void handleInPacket(BasePacketIn packet);
    void handleCondPacket(PacketCond packet);
    void handleOutPacket(PacketOut packet);
    void handlePstPacket(PacketPst packet);
    void handlePetskiPacket(QStringList packet);
    void handleRestPacket(PacketRestR Packet);
    void handleDpskiPacket(QStringList packet);

protected:
    MyCharacter *character;
    MyPartner *partner;
    MyNosmate *nosmate;
    Map *map;
    Network *mNet;
    Credentials *creds;
    Server *serv;
    EventManager *eventManager;
    Group group;
    ChatInstance *chat;
    bool world;
};

#endif // BOT_H
