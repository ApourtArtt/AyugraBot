#ifndef ACCOUNTCONNECTIONWIDGET_H
#define ACCOUNTCONNECTIONWIDGET_H

#include "formbase.h"
#include "accountmanagerwindow.h"
#include "ui_accountconnectionwidget.h"

namespace Ui {
class AccountConnectionWidget;
}

class AccountConnectionWidget : public FormBase
{
    Q_OBJECT

public:
    explicit AccountConnectionWidget(QWidget *parent = nullptr);
    ~AccountConnectionWidget();

signals:
    void error(QString msg);
    void createGameConnection(QString username, QString password, QString gfuid, ConnectionType cType, QString locale);

private slots:
    void on_PB_CONNECT_clicked();
    void on_PB_REFRESH_clicked();

private:
    void connectAccount(QStringList infos);
    void updateAccountList();
    QStringList getAccountInfos();
    Ui::AccountConnectionWidget *ui;

    const QString FILENAME = "accounts.txt";
};

#endif // ACCOUNTCONNECTIONWIDGET_H
