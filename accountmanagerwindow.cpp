#include "accountmanagerwindow.h"
#include "ui_accountmanagerwindow.h"

AccountManagerWindow::AccountManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccountManagerWindow)
{
    ui->setupUi(this);
#ifdef _WIN32
    QSettings settings("HKEY_CURRENT_USER\\Software\\Gameforge4d\\TNTClient\\MainApp", QSettings::NativeFormat);
    ui->LE_GFUID->setText(settings.value("InstallationId", "").toString());
#else
    ui->LE_GFUID->setText(Credentials::generateGFUID());
#endif
    updateAccountList();
}

AccountManagerWindow::~AccountManagerWindow()
{
    delete ui;
}

QStringList AccountManagerWindow::getAccountInfos()
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
                ui->statusbar->showMessage(tr("accounts.txt seems to be corrupted."));
        }
    }
    else
        ui->statusbar->showMessage(tr("No account loaded"), 5000);
    file.close();
    return infos;
}

void AccountManagerWindow::updateAccountList()
{
    ui->LW_ACCOUNTS->clear();
    QStringList infos = getAccountInfos();
    for (int i = 0 ; i < infos.size() ; i  = i + 5)
        ui->LW_ACCOUNTS->addItem(infos[i]);
}

void AccountManagerWindow::addAccount(QString username, QString password, QString country, ConnectionType cType, QString gfuid)
{
    QFile file(FILENAME);
    if (!file.open(QIODevice::Append))
    {
        ui->statusbar->showMessage(tr("Something went wrong in accounts.txt opening."));
        return;
    }
    QTextStream stream(&file);
    stream << username << "|" << password << "|" << country << "|" << QString::number(cType == ConnectionType::NORMAL ? 0 : 1) << "|" << gfuid << endl;
    file.close();
    ui->LW_ACCOUNTS->addItem(username);
}

void AccountManagerWindow::on_PB_ADD_clicked()
{
    QString username            = ui->LE_USERNAME->text();
    QString password            = ui->LE_PASSWORD->text();
    QString gfuid               = ui->LE_GFUID->text();
    ConnectionType accountType  = ui->CB_ACCOUNTTYPE->currentIndex() == 0 ? ConnectionType::NORMAL : ConnectionType::GFL;
    QString locale              = ui->CB_COUNTRY->currentText();
    if(!username.isEmpty() && !password.isEmpty() && !gfuid.isEmpty() && !locale.isEmpty())
    {
        QStringList infos = getAccountInfos();
        bool addAcc = true;
        for(int i = 0 ; i < infos.size() ; i = i + 4)
        {
            if(infos[i] == username && infos[i+2] == locale)
            {
                addAcc = false;
                break;
            }
        }
        if(addAcc)
        {
            addAccount(username, password, locale, accountType, gfuid);
            ui->statusbar->clearMessage();
        }
        else
            ui->statusbar->showMessage(tr("Account already exists."), 5000);
    }
    else
        ui->statusbar->showMessage(tr("At least one information is lacking."), 5000);
}

void AccountManagerWindow::on_PB_REGENERATE_clicked()
{
#ifdef _WIN32
    QSettings settings("HKEY_CURRENT_USER\\Software\\Gameforge4d\\TNTClient\\MainApp", QSettings::NativeFormat);
    ui->LE_GFUID->setText(settings.value("InstallationId", "").toString());
#else
    ui->LE_GFUID->setText(tr("Error : only for Windows"));
#endif
}

void AccountManagerWindow::on_PB_RANDOMDYNAMIC_clicked()
{
    ui->LE_GFUID->setText("DYNAMIC_GFUID_CHOSEN");
}

void AccountManagerWindow::on_PB_RANDOMSTATIC_clicked()
{
    ui->LE_GFUID->setText(Credentials::generateGFUID());
}

void AccountManagerWindow::closeEvent(QCloseEvent *event)
{
    emit s_closedWindow();
    event->accept();
}

void AccountManagerWindow::on_PB_DELETE_clicked()
{
    if(ui->LW_ACCOUNTS->currentItem())
    {
        QString username = ui->LW_ACCOUNTS->currentItem()->text();
        QFile file(FILENAME);
        if(file.open(QIODevice::ReadWrite))
        {
            QString s;
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QString line = in.readLine();
                QStringList fields = line.split("|");
                if(!(fields[0] == username))
                    s.append(line + "\n");
            }
            file.resize(0);
            in << s;
            file.close();
            ui->LW_ACCOUNTS->takeItem(ui->LW_ACCOUNTS->currentRow());
        }
        else
            ui->statusbar->showMessage(tr("Something went wrong in accounts.txt opening."));
    }
}
