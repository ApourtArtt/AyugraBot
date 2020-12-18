#include "headerwidget.h"
#include "ui_headerwidget.h"
#include <QDebug>

HeaderWidget::HeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderWidget)
{
    ui->setupUi(this);
    working = false;

    characterMenu = new QMenu(this);
    characterMenu->setTitle("Player pannel");

    spRequest = new QAction("Toggle SP", characterMenu);
    characterMenu->addAction(spRequest);
    connect(spRequest, &QAction::triggered, [=]{ emit toggleSP(); });

    leaveGroupRequest = new QAction("Leave group", characterMenu);
    characterMenu->addAction(leaveGroupRequest);
    connect(leaveGroupRequest, &QAction::triggered, [=]{ emit leaveGroup(); });

    setSelfishGroup = new QAction("Set selfish group", characterMenu);
    characterMenu->addAction(setSelfishGroup);
    connect(setSelfishGroup, &QAction::triggered, [=]{ emit selfishGroup(); });

    setSharingGroup = new QAction("Set sharing group", characterMenu);
    characterMenu->addAction(setSharingGroup);
    connect(setSharingGroup, &QAction::triggered, [=]{ emit sharingGroup(); });

    partnerMenu = new QMenu(this);
    partnerMenu->setTitle("Parner pannel");
    sppRequest = new QAction("Toggle SPP", partnerMenu);
    partnerMenu->addAction(sppRequest);
    connect(sppRequest, &QAction::triggered, [=]{ emit toggleSPP(); });
}

HeaderWidget::~HeaderWidget()
{
    delete ui;
    delete characterMenu;
    delete partnerMenu;
}

void HeaderWidget::setServerConnectionInfos(short serv, short chan, QString locale)
{
    ui->L_REG->setText(locale);
    ui->L_SERV_CHAN->setText(QString::number(serv) + " - " + QString::number(chan));
}

void HeaderWidget::setOwnCharacterInformation(QString pseudonym, QPixmap image)
{
    if(pseudonym != nullptr)
        ui->L_CHARAC->setText(pseudonym);
    if(image != QPixmap())
        ui->L_PERS->setPixmap(image);
}

void HeaderWidget::setStatistics(Statistics stats)
{
    ui->P_HP->setFormat(QString::number(stats.getCurrentHP()) + "/" + QString::number(stats.getMaxHP()) + " (" + QString::number(static_cast<int>(stats.getPercentHP() * 100)) + "%)");
    ui->P_HP->setValue(static_cast<int>(stats.getPercentHP() * 100));
    ui->P_MP->setFormat(QString::number(stats.getCurrentMP()) + "/" + QString::number(stats.getMaxMP()) + " (" + QString::number(static_cast<int>(stats.getPercentMP() * 100)) + "%)");
    ui->P_MP->setValue(static_cast<int>(stats.getPercentMP() * 100));
}

void HeaderWidget::setLevels(Level level)
{
    ui->P_XP->setFormat(QString::number(level.getPercentNormalXP()) + "%");
    ui->P_XP->setValue(static_cast<int>(level.getPercentNormalXP()));
    ui->P_XPJOB->setFormat(QString::number(level.getPercentJobXP()) + "%");
    ui->P_XPJOB->setValue(static_cast<int>(level.getPercentJobXP()));
    ui->P_XPHERO->setFormat(QString::number(level.getPercentHeroXP()) + "%");
    ui->P_XPHERO->setValue(static_cast<int>(level.getPercentHeroXP()));
    ui->L_LVL->setText(QString::number(level.getLevel())     + "+" +
                       QString::number(level.getLevelHero()) + " " +
                       QString::number(level.getLevelJob()));
}

void HeaderWidget::setGroup(Group group, int characterID)
{
    SubEntityGroup *pet = group.getPet();
    SubEntityGroup *partner = group.getPartner();
    QVector<SubEntityGroup *> mates = group.getMates();
    if(pet != nullptr)
        ui->L_FAM->setPixmap(QPixmap(QApplication::applicationDirPath() + "/images/" + DatabaseMonster::getMonsterImageIDFromID(pet->getMorphID()) + ".png"));
    else
        ui->L_FAM->clear();
    if(partner != nullptr)
    {
        int file = partner->getMorphID() > 2000 ? partner->getMorphID() + 25000 : DatabaseMonster::getMonsterImageIDFromID(partner->getMorphID()).toInt();
        ui->L_PART->setPixmap(QPixmap(QApplication::applicationDirPath() + "/images/" + QString::number(file) + ".png"));
    }
    else
        ui->L_PART->clear();
    ui->L_T1->clear();
    ui->L_T2->clear();
    ui->L_PSEUDOMATE_1->clear();
    ui->L_PSEUDOMATE_2->clear();
    int j = 0;
    for(int i = 0 ; i < mates.size() ; i++)
    {
        if(mates[i] != nullptr && mates[i]->getEntityID() != characterID)
        {
            bool isSp = mates[i]->getMorphID() == 0 ? false : true;
            int imgId = isSp ? 32498 + mates[i]->getMorphID() * 2 + static_cast<int>(mates[i]->getGender()) : 32000 + static_cast<int>(mates[i]->getClass()) * 40 + static_cast<int>(mates[i]->getGender()) * 20;
            if(j == 0)
            {
                ui->L_T1->setPixmap(QPixmap(QApplication::applicationDirPath() + "/images/" + QString::number(imgId) + ".png"));
                ui->L_PSEUDOMATE_1->setText(mates[i]->getPseudonym());
            }
            else
            {
                ui->L_T2->setPixmap(QPixmap(QApplication::applicationDirPath() + "/images/" + QString::number(imgId) + ".png"));
                ui->L_PSEUDOMATE_2->setText(mates[i]->getPseudonym());
            }
            j++;
        }
    }
}

void HeaderWidget::toggleBot()
{
    working = !working;
    emit botStatusChanged(working);
    if(working)
        ui->PB_ONOFF->setText("Toggle off");
    else
        ui->PB_ONOFF->setText("Toggle on");
}

void HeaderWidget::on_PB_DC_clicked()
{
    emit disconnectFromGame();
}

void HeaderWidget::on_PB_ONOFF_clicked()
{
    toggleBot();
}

void HeaderWidget::on_L_PERS_customContextMenuRequested(const QPoint &pos)
{
    characterMenu->exec(ui->L_PERS->mapToGlobal(pos));
}

void HeaderWidget::on_L_PART_customContextMenuRequested(const QPoint &pos)
{
    partnerMenu->exec(ui->L_PART->mapToGlobal(pos));
}
