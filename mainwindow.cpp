#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadedDb = 0;
    accountConnectionWidget = nullptr;
    if(!loadVersion())
    {
        if(!craftVersion())
            ui->statusbar->showMessage(tr("Could not retrieve Nostale's hashes and version"), 5000);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loaded()
{
    loadedDb++;
    if(loadedDb >= NB_DATABASE_TO_LOAD)
        ui->actionConnect->setEnabled(true);
}

void MainWindow::on_actionManage_triggered()
{
    AccountManagerWindow *accMngW = new AccountManagerWindow(this);
    accMngW->show();
    connect(accMngW, &AccountManagerWindow::s_closedWindow, this, [=](){ delete accMngW; });
}

void MainWindow::on_actionConnect_triggered()
{
    if(accountConnectionWidget == nullptr)
    {
        accountConnectionWidget = new AccountConnectionWidget(this);
        accountConnectionWidget->ownSubWindow(loadSubWindow(accountConnectionWidget, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint, false));
        connect(accountConnectionWidget, &AccountConnectionWidget::error, [=](QString error) { ui->statusbar->showMessage(error, 5000); });
        connect(accountConnectionWidget, &AccountConnectionWidget::createGameConnection, [=](QString username, QString password, QString gfuid, ConnectionType cType, QString locale)
        {
            BotManager *botMng = new BotManager(dxhash, glhash, version, nullptr);
            qDebug() << botMng;
            connect(botMng, &BotManager::recievedAvailableServers, [=](QVector<serverIdentity> servList)
            {
                ChannelWidget *channelW = new ChannelWidget(servList, this);
                connect(channelW, &ChannelWidget::connect, [=](QString gameIp, ushort gamePort, short serv, short chan)
                {
                    connect(botMng, &BotManager::recievedAvailableCharacters, [=](QVector<MyCharacter *> characterList)
                    {
                        CharacterWidget *characterW = new CharacterWidget(characterList, this);
                        connect(characterW, &CharacterWidget::selectedCharacter, [=](short slot)
                        {
                            if(botMng->selectCharacter(slot))
                            {
                                characterW->close();
                                delete characterW;
                                BotWidget *bot = new BotWidget(botMng, this);
                                //bots.push_back(bot);
                                bot->setServerConnectionInfos(serv, chan, locale);
                                bot->ownSubWindow(loadSubWindow(bot, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint, true));
                                connect(bot, &BotWidget::disconnectFromServer, [=]
                                {
                                    bot->close();
                                    delete bot;
                                    //bots.removeAt(bots.indexOf(bot));
                                });
                            }
                        });
                        connect(characterW, &CharacterWidget::deletedCharacter, [=](short slot)
                        {
                            if(botMng->deleteCharacter(slot))
                            {
                                characterW->close();
                                delete characterW;
                            }
                        });
                        connect(characterW, &CharacterWidget::createdCharacter, [=]
                                (Class characterClass, QString pseudo, short slot, Gender gender, HairStyle hStyle, short hColor)
                        {
                            if(botMng->createCharacter(characterClass, pseudo, slot, gender, hStyle, hColor))
                            {
                                characterW->close();
                                delete characterW;
                            }
                        });
                        characterW->ownSubWindow(loadSubWindow(characterW, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint, true));
                    });
                    botMng->connectToGame(gameIp, gamePort, serv, chan);
                    channelW->close();
                    delete channelW;
                });
                channelW->ownSubWindow(loadSubWindow(channelW, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint, true));
            });
            botMng->login(username, password, gfuid, cType, langToIdString.value(locale), loginIp, RegionPort.value(locale));
            //BotWidget *bot = new BotWidget(username, password, gfuid, cType, locale, dxhash, glhash, version, this);
            //bot->ownSubWindow(loadSubWindow(accountConnectionWidget, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint, false));
        });
    }
    if(!accountConnectionWidget->isVisible())
        accountConnectionWidget->show();
}

QMdiSubWindow *MainWindow::loadSubWindow(QWidget *wid, Qt::WindowFlags flags, bool show)
{
    QMdiSubWindow *sub = ui->MDI->addSubWindow(wid, flags);
    if(show)
        sub->show();
    return sub;
}

bool MainWindow::craftVersion()
{
    QJsonObject json;
    dxhash = Cryptography::getMd5FileHash(NTX_FILENAME);
    glhash = Cryptography::getMd5FileHash(NT_FILENAME);
    version = Cryptography::getVersionFile(NTX_FILENAME);

    json["dxhash"]   = dxhash;
    json["glhash"]   = glhash;
    json["version"]  = version;
    json["loginip"]  = loginIp;

    QFile saveFile(CONFIG_FILENAME);
    if (!saveFile.open(QIODevice::WriteOnly))
        return false;
    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
    return true;
}

bool MainWindow::loadVersion()
{
    QJsonObject json;
    QFile loadFile(CONFIG_FILENAME);
    if (!loadFile.open(QIODevice::ReadOnly))
        return false;
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    json = loadDoc.object();

    if(json.contains("dxhash") && json["dxhash"].isString())
        dxhash = loadDoc["dxhash"].toString();
    else return false;

    if(json.contains("glhash") && json["glhash"].isString())
        glhash = loadDoc["glhash"].toString();
    else return false;

    if(json.contains("version") && json["version"].isString())
        version = loadDoc["version"].toString();
    else return false;

    if(json.contains("loginip") && json["loginip"].isString())
        loginIp = loadDoc["loginip"].toString();
    else return false;

    if(dxhash.isEmpty() || glhash.isEmpty() || version.isEmpty() || loginIp.isEmpty())
        return false;
    return true;
}

void MainWindow::on_actionContact_me_on_Discord_triggered()
{
    QDesktopServices::openUrl(QUrl("https://discord.gg/9BhdbRw"));
}

void MainWindow::on_actionUpdate_config_triggered()
{
    craftVersion();
}
