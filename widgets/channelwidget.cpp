#include "channelwidget.h"

ChannelWidget::ChannelWidget(QVector<serverIdentity> serv, QWidget *parent) :
    FormBase(parent),
    ui(new Ui::ChannelWidget)
{
    ui->setupUi(this);
    channelID = 0;
    servName = "";
    servChanInfo = serv;
    QVector<int> chan;
    for(int i = 0 ; i < serv.size() ; i++)
    {
        if(!servPrinted.contains(serv[i].name))
            servPrinted.push_back(serv[i].name);
    }
    ui->TW_LISTSERV->setRowCount(servPrinted.size());
    for(int i = 0 ; i < servPrinted.size() ; i++)
        ui->TW_LISTSERV->setItem(i, 0, new QTableWidgetItem(servPrinted[i]));
}

ChannelWidget::~ChannelWidget()
{
    delete ui;
}

void ChannelWidget::on_TW_LISTSERV_cellClicked(int row, int column)
{
    QTableWidgetItem *a = ui->TW_LISTSERV->item(row, column);
    if(a == nullptr) return;
    if(column == 0)
    {
        servName = a->text();
        QStringList chanToDisplay;
        for(int i = 0 ; i < servChanInfo.size() ; i++)
        {
            if(servChanInfo[i].name == servName && !chanToDisplay.contains(QString::number(servChanInfo[i].channel)))
                chanToDisplay.push_back(QString::number(servChanInfo[i].channel) + " " + QString::number(servChanInfo[i].population));
        }
        chanToDisplay.sort();
        ui->TW_LISTSERV->setRowCount(servPrinted.size() > chanToDisplay.size() ? servPrinted.size() : chanToDisplay.size());
        for(int i = 0 ; i < servPrinted.size() ; i++)
        {
            ui->TW_LISTSERV->setItem(i, 0, new QTableWidgetItem(servPrinted[i]));
        }
        QVector<QTableWidgetItem*> items;
        for(int i = 0 ; i < chanToDisplay.size() ; i++)
        {
            items.push_back(new QTableWidgetItem(chanToDisplay[i].split(" ")[0]));
            items[i]->setForeground(getColorFromPopulation(chanToDisplay[i].split(" ")[1].toShort()));
            ui->TW_LISTSERV->setItem(i, 1, items[i]);
        }
    }
    else if(column == 1)
    {
        channelID = a->text().toShort();
    }
    if(channelID != 0 && servName != "")
    {
        ui->PB_CONNECT->setText(tr("Connect", "In serv/channel choice") + "\n(" + servName  + " - " + QString::number(channelID) + ")");
        ui->PB_CONNECT->setEnabled(true);
    }
}

void ChannelWidget::on_PB_CONNECT_clicked()
{
    if(channelID != 0 && servName != "")
    {
        QString gameIP = "";
        unsigned short gamePort = 0;
        short server = 0;
        for(int i = 0 ; i < servChanInfo.size() ; i++)
        {
            if(servChanInfo[i].name == servName && servChanInfo[i].channel == channelID)
            {
                gameIP = servChanInfo[i].add.ip;
                gamePort = servChanInfo[i].add.port;
                server = servChanInfo[i].server;
            }
        }
        if(gameIP != "" && gamePort != 0)
            emit connect(gameIP, gamePort, server, channelID);
    }
}

QColor ChannelWidget::getColorFromPopulation(short population)
{
    int r = 0 + population * 12;
    int g = 240 - population * 12;
    int b = 0 + population * 3;
    return QColor(r, g, b);
}
