#ifndef ACCOUNTMANAGERWINDOW_H
#define ACCOUNTMANAGERWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QTextStream>
#include "srcs/Net/credentials.h"

namespace Ui {
class AccountManagerWindow;
}

class AccountManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountManagerWindow(QWidget *parent = nullptr);
    ~AccountManagerWindow();

signals:
    void s_closedWindow();

private slots:
    void on_PB_REGENERATE_clicked();
    void on_PB_RANDOMDYNAMIC_clicked();
    void on_PB_RANDOMSTATIC_clicked();
    void on_PB_ADD_clicked();
    void on_PB_DELETE_clicked();

private:
    void closeEvent(QCloseEvent *event);
    void updateAccountList();
    QStringList getAccountInfos();
    void addAccount(QString username, QString password, QString country, ConnectionType cType, QString gfuid);

    Ui::AccountManagerWindow *ui;

    const QString FILENAME = "accounts.txt";
};

#endif // ACCOUNTMANAGERWINDOW_H
