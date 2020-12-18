#ifndef USERSWIDGET_H
#define USERSWIDGET_H

#include <QWidget>
#include <QMenu>
#include "srcs/GameObjects/Map/map.h"

namespace Ui {
class UsersWidget;
}

class UsersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UsersWidget(QWidget *parent = nullptr);
    ~UsersWidget();
    void setMap(Map *Map);
    void inOut();
    void clear();

signals:
    void sendPartyRequest(Player player);
    void sendBlacklist(Player player);
    void sendFriendRequest(Player player);
    void selectedPlayer(Player player);

private slots:
    void on_TW_USERS_1_customContextMenuRequested(const QPoint &pos);
    void on_TW_USERS_1_cellActivated(int row, int column);

private:
    Ui::UsersWidget *ui;
    Map *map;
    QMenu *menuUsers;
    Player currentPlayer;
    bool selected;
};

#endif // USERSWIDGET_H
