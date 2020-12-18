#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QString>
#include "srcs/GameObjects/Properties/level.h"
#include "srcs/GameObjects/Properties/statistics.h"
#include "srcs/GameObjects/Properties/group.h"
#include "srcs/Database/databasemonster.h"

namespace Ui {
class HeaderWidget;
}

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);
    ~HeaderWidget();
    void setServerConnectionInfos(short serv, short chan, QString locale);
    void setOwnCharacterInformation(QString pseudonym = nullptr, QPixmap image = QPixmap());
    void setStatistics(Statistics stats);
    void setLevels(Level level);
    void setGroup(Group group, int characterID);
    void toggleBot();

signals:
    void botStatusChanged(bool working);
    void disconnectFromGame();

    void toggleSP();
    void leaveGroup();
    void selfishGroup();
    void sharingGroup();

    void toggleSPP();

private slots:
    void on_PB_DC_clicked();
    void on_PB_ONOFF_clicked();
    void on_L_PERS_customContextMenuRequested(const QPoint &pos);
    void on_L_PART_customContextMenuRequested(const QPoint &pos);

private:
    Ui::HeaderWidget *ui;
    bool working;
    QMenu *characterMenu;
    QAction *spRequest;
    QAction *leaveGroupRequest;
    QAction *setSharingGroup;
    QAction *setSelfishGroup;

    QMenu *partnerMenu;
    QAction *sppRequest;
};

#endif // HEADERWIDGET_H
