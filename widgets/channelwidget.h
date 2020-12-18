#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include "formbase.h"
#include "srcs/Net/server.h"
#include "ui_channelwidget.h"

namespace Ui {
class ChannelWidget;
}

class ChannelWidget : public FormBase
{
    Q_OBJECT
public:
    explicit ChannelWidget(QVector<serverIdentity> serv, QWidget *parent = nullptr);
    ~ChannelWidget();

signals:
    void connect(QString gameIP, unsigned short gamePort, short server, short channel);

private slots:
    void on_TW_LISTSERV_cellClicked(int row, int column);
    void on_PB_CONNECT_clicked();

private:
    QColor getColorFromPopulation(short population);
    Ui::ChannelWidget *ui;
    QVector<serverIdentity> servChanInfo;
    QString servName;
    short channelID;
    QStringList servPrinted;
};

#endif // CHANNELWIDGET_H
