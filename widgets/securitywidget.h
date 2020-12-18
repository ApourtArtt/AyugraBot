#ifndef SECURITYWIDGET_H
#define SECURITYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSound>
#include <QDate>
#include "srcs/Enum/blockingoption.h"

namespace Ui {
class SecurityWidget;
}

class SecurityWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecurityWidget(QWidget *parent = nullptr);
    ~SecurityWidget();
    void alert();
    bool shouldDisconnectOnGMPop();
    bool shouldStopOnGMPop();
    bool shouldBeepOnGMPop();
    bool shouldDisconnectOnPlayerPop();
    bool shouldStopOnPlayerPop();
    bool shouldBeepOnPlayerPop();
    bool shouldBlacklistOnWhisper();
    bool shouldBlacklistOnGroup();
    bool isSpeakerBlocked();

signals:
    void toggleOption(BlockingOption option, bool blocked);
    void askForDisconnection();
    void askForStopping();

private slots:
    void on_CB_FRIEND_stateChanged(int arg1);
    void on_CB_FAMILLY_stateChanged(int arg1);
    void on_CB_MINILAND_stateChanged(int arg1);
    void on_CB_EXCHANGE_stateChanged(int arg1);
    void on_CB_GROUP_stateChanged(int arg1);
    void on_CB_WHISPER_stateChanged(int arg1);
    void on_LE_TIMER_textChanged(const QString &arg1);

private:
    Ui::SecurityWidget *ui;
    QTimer *securityTimer;
};

#endif // SECURITYWIDGET_H
