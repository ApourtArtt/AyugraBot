#ifndef BOTWIDGET_H
#define BOTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QScrollBar>
#include <QMessageBox>
#include <QMenu>
#include "srcs/Database/databasemonster.h"
#include "botmanager.h"
#include "formbase.h"
#include "headerwidget.h"
#include "itemusewidget.h"
#include "monsterwidget.h"
#include "intelligence/artificialintelligence.h"

namespace Ui {
class BotWidget;
}

class BotWidget : public FormBase
{
    Q_OBJECT
public:
    explicit BotWidget(BotManager *Bot, QWidget *parent);
    void setServerConnectionInfos(short serv, short chan, QString locale);
    ~BotWidget();

signals:
    void disconnectFromServer();

private slots:
    void on_LE_CHAT_returnPressed();
    void worldCreated(MyCharacter *Character, Map *Map);
    void mapChanged(/*Map *Map*/);
    void characterUpdate(/*MyCharacter *Character*/);
    void inventoryUpdate(/*Inventory *inv*/);
    void morphChanged(PacketC_mode Packet);
    void groupCreated(Group group);
    void handleMessages();
    void mapUpdated(/*Map *Map*/);
    void newPlayer(Player player);

private:
    Ui::BotWidget *ui;
    BotManager *bot;
    MyCharacter *character;
    MyPartner *partner;
    MyNosmate *nosmate;
    Map *map;
    ChatInstance *chat;
    bool botWorking;
    QMenu *menuUsers;
    bool inventoryConnected;
    ArtificialIntelligence *ai;
};

#endif // BOTWIDGET_H
