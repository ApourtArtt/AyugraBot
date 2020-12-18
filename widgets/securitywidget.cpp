#include "securitywidget.h"
#include "ui_securitywidget.h"

SecurityWidget::SecurityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecurityWidget)
{
    ui->setupUi(this);
    securityTimer = new QTimer(this);
    securityTimer->setSingleShot(true);
    connect(securityTimer, &QTimer::timeout, [=]
    {
        if(ui->CB_TIMER_STOP->isChecked())
            emit askForStopping();
        if(ui->CB_TIMER_ALERT->isChecked())
            alert();
        if(ui->CB_TIMER_DISCONNECT->isChecked())
            emit askForDisconnection();
    });
    // TODO : stop doing it and just parse stat packet to properly show checked/unchecked combobox option
    QTimer::singleShot(50  + qrand() % 50, [this]{ emit toggleOption(BlockingOption::FRIEND,   true); });
    QTimer::singleShot(120 + qrand() % 50, [this]{ emit toggleOption(BlockingOption::FAMILLY,  true); });
    QTimer::singleShot(190 + qrand() % 50, [this]{ emit toggleOption(BlockingOption::MINILAND, true); });
    QTimer::singleShot(260 + qrand() % 50, [this]{ emit toggleOption(BlockingOption::EXCHANGE, true); });
    QTimer::singleShot(330 + qrand() % 50, [this]{ emit toggleOption(BlockingOption::GROUP,    true); });
    QTimer::singleShot(400 + qrand() % 50, [this]{ emit toggleOption(BlockingOption::WHISPER,  true); });
}

SecurityWidget::~SecurityWidget()
{
    delete ui;
}

void SecurityWidget::alert()
{
    QSound::play("beep.wav");
}

void SecurityWidget::on_CB_FRIEND_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::FRIEND, !ui->CB_FRIEND->isChecked());
}

void SecurityWidget::on_CB_FAMILLY_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::FAMILLY, !ui->CB_FAMILLY->isChecked());
}

void SecurityWidget::on_CB_MINILAND_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::MINILAND, !ui->CB_MINILAND->isChecked());
}

void SecurityWidget::on_CB_EXCHANGE_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::EXCHANGE, !ui->CB_EXCHANGE->isChecked());
}

void SecurityWidget::on_CB_GROUP_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::GROUP, !ui->CB_GROUP->isChecked());
}

void SecurityWidget::on_CB_WHISPER_stateChanged(int arg1)
{
    emit toggleOption(BlockingOption::WHISPER, !ui->CB_WHISPER->isChecked());
}

void SecurityWidget::on_LE_TIMER_textChanged(const QString &arg1)
{
    securityTimer->stop();
    securityTimer->start(ui->LE_TIMER->text().toInt() * 60000);
    ui->L_TIMER_INFORMATION->setText("Action will be effective at " + QTime::currentTime().addSecs(ui->LE_TIMER->text().toInt()*60).toString());
}

bool SecurityWidget::shouldDisconnectOnGMPop()
{
    return ui->CB_GMPOP_DISCONNECT->isChecked();
}

bool SecurityWidget::shouldStopOnGMPop()
{
    return ui->CB_GMPOP_STOP->isChecked();
}

bool SecurityWidget::shouldBeepOnGMPop()
{
    return ui->CB_GMPOP_ALERT->isChecked();
}

bool SecurityWidget::shouldDisconnectOnPlayerPop()
{
    return ui->CB_PLAYERPOP_DISCONNECT->isChecked();
}

bool SecurityWidget::shouldStopOnPlayerPop()
{
    return ui->CB_PLAYERPOP_STOP->isChecked();
}

bool SecurityWidget::shouldBeepOnPlayerPop()
{
    return ui->CB_PLAYERPOP_ALERT->isChecked();
}

bool SecurityWidget::shouldBlacklistOnWhisper()
{
    return ui->CB_BLACKLIST_WHISPER->isChecked();
}

bool SecurityWidget::shouldBlacklistOnGroup()
{
    return ui->CB_BLACKLIST_GROUP->isChecked();
}

bool SecurityWidget::isSpeakerBlocked()
{
    return ui->CB_SPEAKER->isChecked();
}
