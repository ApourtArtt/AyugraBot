#include "accountconnectionwidget.h"

AccountConnectionWidget::AccountConnectionWidget(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::AccountConnectionWidget)
{
    ui->setupUi(this);
    updateAccountList();
}

AccountConnectionWidget::~AccountConnectionWidget()
{
    delete ui;
}

void AccountConnectionWidget::on_PB_CONNECT_clicked()
{
    if(ui->LW_ACCOUNTS->currentItem())
    {
        QStringList accountInfo = getAccountInfos();
        QStringList info;
        for(int i = 0 ; i < accountInfo.size() ; i = i + 5)
        {
            if(accountInfo[i] == ui->LW_ACCOUNTS->currentItem()->text())
            {
                for(int j = 0 ; j <= 4 ; j++)
                    info.push_back(accountInfo[i + j]);
            }
        }
        if(!info.isEmpty())
            connectAccount(info);
    }
}

void AccountConnectionWidget::connectAccount(QStringList accountInfo)
{
    QString username = accountInfo[0];
    QString password = accountInfo[1];
    QString locale = accountInfo[2];
    ConnectionType cType = accountInfo[3] == "0" ? ConnectionType::NORMAL : ConnectionType::GFL;
    QString gfuid = accountInfo[4];
    //qDebug() << username << password << locale << gfuid;
    emit createGameConnection(username, password, gfuid, cType, locale);
}

void AccountConnectionWidget::updateAccountList()
{
    ui->LW_ACCOUNTS->clear();
    QStringList infos = getAccountInfos();
    for (int i = 0 ; i < infos.size() ; i  = i + 5)
        ui->LW_ACCOUNTS->addItem(infos[i]);
}

QStringList AccountConnectionWidget::getAccountInfos()
{
    QStringList infos;
    QFile file(FILENAME);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList fields = line.split("|");
            if(fields.size() == 5)
                infos << fields;
            else
                emit error(tr("accounts.txt seems to be corrupted."));
        }
    }
    else
        emit error(tr("No account loaded"));
    file.close();
    return infos;
}

void AccountConnectionWidget::on_PB_REFRESH_clicked()
{
    updateAccountList();
}
