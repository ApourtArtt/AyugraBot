#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include "srcs/Net/cryptography.h"
#include "srcs/Net/codegenerator.h"
#include "accountmanagerwindow.h"
#include "widgets/accountconnectionwidget.h"
#include "widgets/botwidget.h"
#include "widgets/channelwidget.h"
#include "widgets/characterwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loaded();

private slots:
    void on_actionManage_triggered();
    void on_actionConnect_triggered();
    void on_actionContact_me_on_Discord_triggered();
    void on_actionUpdate_config_triggered();

private:
    QMdiSubWindow *loadSubWindow(QWidget *wid, Qt::WindowFlags flags, bool show);
    bool loadVersion();
    bool craftVersion();

    Ui::MainWindow *ui;
    AccountConnectionWidget *accountConnectionWidget;

    int loadedDb;
    QString dxhash, glhash, version, loginIp;

    //QVector<BotWidget*> bots;

    const QString CONFIG_FILENAME = "config.json";
    const QString NTX_FILENAME = "NostaleClientX.exe";
    const QString NT_FILENAME = "NostaleClient.exe";
    const int NB_DATABASE_TO_LOAD = 4;
};

#endif // MAINWINDOW_H
