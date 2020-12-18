#include "behaviourwidget.h"
#include "ui_behaviourwidget.h"

BehaviourWidget::BehaviourWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BehaviourWidget)
{
    ui->setupUi(this);
}

BehaviourWidget::~BehaviourWidget()
{
    delete ui;
}

bool BehaviourWidget::disconnectOnDeath()
{
    return ui->RB_DISCONNECT->isChecked();
}

bool BehaviourWidget::worOnDeath()
{
    return ui->RB_WOR->isChecked();
}

bool BehaviourWidget::repopOnDeath()
{
    return ui->RB_RESURECTION->isChecked();
}

void BehaviourWidget::on_SB_SITHP_valueChanged(int arg1)
{
    emit sitLowerThan(arg1, ui->SB_SITMP->value(), ui->SB_SITHP_2->value(), ui->SB_SITMP_2->value());
}

void BehaviourWidget::on_SB_SITMP_valueChanged(int arg1)
{
    emit sitLowerThan(ui->SB_SITHP->value(), arg1, ui->SB_SITHP_2->value(), ui->SB_SITMP_2->value());
}

void BehaviourWidget::on_SB_SITHP_2_valueChanged(int arg1)
{
    emit sitLowerThan(ui->SB_SITHP->value(), ui->SB_SITMP->value(), arg1, ui->SB_SITMP_2->value());
}

void BehaviourWidget::on_SB_SITMP_2_valueChanged(int arg1)
{
    emit sitLowerThan(ui->SB_SITHP->value(), ui->SB_SITMP->value(), ui->SB_SITHP_2->value(), arg1);
}

void BehaviourWidget::on_SB_STAYMINILANDFOR_valueChanged(int arg1)
{
    emit stayInMinilandFor(arg1);
}

void BehaviourWidget::on_SB_GOTOMINILANDEVERY_valueChanged(int arg1)
{
    emit goToMinilandEvery(arg1);
}

void BehaviourWidget::on_SB_DROP_DIST_valueChanged(int arg1)
{
    emit distDropChanged(arg1);
}

void BehaviourWidget::on_RB_PET_D_clicked()
{
    emit petAIChanged(MateAI::D);
}

void BehaviourWidget::on_RB_PET_S_clicked()
{
    emit petAIChanged(MateAI::S);
}

void BehaviourWidget::on_RB_PET_A_clicked()
{
    emit petAIChanged(MateAI::A);
}

void BehaviourWidget::on_RB_PET_SD_clicked()
{
    emit petAIChanged(MateAI::SDS);
}

void BehaviourWidget::on_RB_PET_SD_RANGE_clicked()
{
    emit petAIChanged(MateAI::SDS);
}


void BehaviourWidget::on_RB_PART_D_clicked()
{
    emit partnerAIChanged(MateAI::D);
}

void BehaviourWidget::on_RB_PART_S_clicked()
{
    emit partnerAIChanged(MateAI::S);
}

void BehaviourWidget::on_RB_PART_A_clicked()
{
    emit partnerAIChanged(MateAI::A);
}

void BehaviourWidget::on_RB_PART_SD_clicked()
{
    emit partnerAIChanged(MateAI::SDS);
}

void BehaviourWidget::on_RB_PART_SD_RANGE_clicked()
{
    emit partnerAIChanged(MateAI::SDR);
}

int BehaviourWidget::getHP() const
{
    return ui->SB_SITHP->value();
}

int BehaviourWidget::getMP() const
{
    return ui->SB_SITMP->value();
}

int BehaviourWidget::getHPGetUp() const
{
    return ui->SB_SITHP_2->value();
}

int BehaviourWidget::getMPGetUp()
{
    return ui->SB_SITMP_2->value();
}

void BehaviourWidget::on_groupBox_4_clicked()
{
    if (ui->groupBox_3->isChecked())
        emit sitLowerThan(-1, -1, -1, -1);
    else
        emit sitLowerThan(ui->SB_SITHP->value(), ui->SB_SITMP->value(), ui->SB_SITHP_2->value(), ui->SB_SITMP_2->value());
}

void BehaviourWidget::on_groupBox_3_clicked()
{
    if (ui->groupBox_3->isChecked())
        emit goToMinilandEvery(INT_MAX);
    else
        emit goToMinilandEvery(ui->SB_GOTOMINILANDEVERY->value());
}
