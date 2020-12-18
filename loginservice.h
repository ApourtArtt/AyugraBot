#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QMainWindow>
#include <QtConcurrent>
#include "ui_loginservice.h"
#include "mainwindow.h"
#include "srcs/Net/networkrequester.h"


//#include "srcs/Database/databasemonster.h"
// To remove once used anywhere else

namespace Ui {
class LoginService;
}

class LoginService : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginService(QWidget *parent = nullptr);
    ~LoginService();

private slots:
    void on_PB_CONNECT_clicked();

private:
    Ui::LoginService *ui;
    MainWindow *mW;

    QString LINK_REGISTER = "";
    QString LINK_FORGET = "";
    QString LINK_REQUEST = "";
};

#endif // LOGINSERVICE_H
