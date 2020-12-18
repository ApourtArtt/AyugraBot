#include "skillswidget.h"
#include "ui_skillswidget.h"
#include <QDebug>

SkillsWidget::SkillsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkillsWidget)
{
    ui->setupUi(this);
}

SkillsWidget::~SkillsWidget()
{
    delete ui;
}

void SkillsWidget::setSkills(QMap<int, Skill*> Skills)
{
    skills = Skills;
    ui->LW_SKILLS->clear();
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(skills[keys[i]]->getID()) + " " + skills[keys[i]]->getName());
    keys = partnerSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(partnerSkills[keys[i]]->getID()) + " " + partnerSkills[keys[i]]->getName());
    keys = nosmateSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(nosmateSkills[keys[i]]->getID()) + " " + nosmateSkills[keys[i]]->getName());
}

void SkillsWidget::setPartnerSkills(QMap<int, Skill *> Skills)
{
    partnerSkills = Skills;
    ui->LW_SKILLS->clear();
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(skills[keys[i]]->getID()) + " " + skills[keys[i]]->getName());
    keys = partnerSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(partnerSkills[keys[i]]->getID()) + " " + partnerSkills[keys[i]]->getName());
    keys = nosmateSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(nosmateSkills[keys[i]]->getID()) + " " + nosmateSkills[keys[i]]->getName());
}

void SkillsWidget::setNosmateSkills(QMap<int, Skill *> Skills)
{
    nosmateSkills = Skills;
    ui->LW_SKILLS->clear();
    QList<int> keys = skills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(skills[keys[i]]->getID()) + " " + skills[keys[i]]->getName());
    keys = partnerSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(partnerSkills[keys[i]]->getID()) + " " + partnerSkills[keys[i]]->getName());
    keys = nosmateSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
        ui->LW_SKILLS->addItem(QString::number(nosmateSkills[keys[i]]->getID()) + " " + nosmateSkills[keys[i]]->getName());
}

QMap<int, UsableSkill> SkillsWidget::getUsableSkills()
{
    return usableSkills;
}

QMap<int, UsableSkill> SkillsWidget::getPartnerUsableSkills()
{
    return partnerUsableSkills;
}

QMap<int, UsableSkill> SkillsWidget::getNosmateUsableSkills()
{
    return nosmateUsableSkills;
}

void SkillsWidget::on_LW_SKILLS_itemDoubleClicked(QListWidgetItem *item)
{
    if(!item)
        return;
    int index = ui->LW_SKILLS->currentRow();
    if(index >= (skills.size() + partnerSkills.size() + nosmateSkills.size()) || index < 0)
        return;
    if(index < skills.size())
    {
        QList<int> keys = skills.keys();
        changeStatusWidget(true);
        currentSkillIndex = keys[index];
        ui->SB_DISTANCECAST->setRange(0, skills[keys[index]]->getRange() + 3);
        ui->LE_SKILLNAME->setText(QString::number(skills[keys[index]]->getID()) + " " + skills[keys[index]]->getName());
        skillTypeUI = SkillTypeUI::Character;
    }
    else if(index >= skills.size() && index < skills.size() + partnerSkills.size())
    {
        QList<int> keys = partnerSkills.keys();
        changeStatusWidget(true);
        index -= skills.size();
        currentSkillIndex = keys[index];
        ui->SB_DISTANCECAST->setRange(0, partnerSkills[keys[index]]->getRange() + 3);
        ui->LE_SKILLNAME->setText(QString::number(partnerSkills[keys[index]]->getID()) + " " + partnerSkills[keys[index]]->getName());
        skillTypeUI = SkillTypeUI::Partner;
    }
    else if(index >= (skills.size() + partnerSkills.size()) && index < (skills.size() + partnerSkills.size() + nosmateSkills.size()))
    {
        QList<int> keys = nosmateSkills.keys();
        changeStatusWidget(true);
        index -= (skills.size() + partnerSkills.size());
        currentSkillIndex = keys[index];
        ui->SB_DISTANCECAST->setRange(0, nosmateSkills[keys[index]]->getRange() + 3);
        ui->LE_SKILLNAME->setText(QString::number(nosmateSkills[keys[index]]->getID()) + " " + nosmateSkills[keys[index]]->getName());
        skillTypeUI = SkillTypeUI::Nosmate;
    }
}

void SkillsWidget::on_PB_DEFAULT_clicked()
{
    ui->RB_CASTAVAILABLE->setChecked(true);
    ui->SB_PRIORITY->setValue(0);
    ui->SB_CASTSECOND->setValue(0);
    ui->SB_DISTANCECAST->setValue(0);
}

void SkillsWidget::on_PB_SAVE_clicked()
{
    if(skillTypeUI == SkillTypeUI::Character)
    {
        QList<int> sKeys = skills.keys();
        if(!sKeys.contains(currentSkillIndex))
            return;
        int priority = ui->SB_PRIORITY->value();
        QList<int> keys = usableSkills.keys();
        if(keys.contains(priority) && priority >= 0)
        {
            ui->L_SAVESTATUS->setText("Another skill has the same priority.");
            return;
        }
        QList<QListWidgetItem*> items = ui->LW_ACTIVESKILLS->findItems(ui->LE_SKILLNAME->text(), Qt::MatchFlag::MatchExactly);
        if(items.size() != 0)
        {
            ui->L_SAVESTATUS->setText("This skill is already saved.");
            return;
        }
        usableSkills.insert(priority, UsableSkill(skills[currentSkillIndex]));
        usableSkills[priority].configure(ui->RB_CASTSECONDS->isChecked() ? ui->SB_CASTSECOND->value() : -1, ui->SB_DISTANCECAST->value(), static_cast<Target>(ui->CB_TARGET->currentIndex()));
        keys = usableSkills.keys();
        ui->LW_ACTIVESKILLS->insertItem(keys.indexOf(priority), QString::number(skills[currentSkillIndex]->getID()) + " " + skills[currentSkillIndex]->getName());
        ui->L_SAVESTATUS->setText("Saving successfull.");
        emit usableSkillsChanged(usableSkills);
        ui->SB_PRIORITY->setValue(ui->SB_PRIORITY->value() + 1);
    }
    else if(skillTypeUI == SkillTypeUI::Partner)
    {
        QList<int> sKeys = partnerSkills.keys();
        if(!sKeys.contains(currentSkillIndex))
            return;
        int priority = ui->SB_PRIORITY->value();
        QList<int> keys = partnerUsableSkills.keys();
        if(keys.contains(priority) && priority >= 0)
        {
            ui->L_SAVESTATUS->setText("Another skill has the same priority.");
            return;
        }
        QList<QListWidgetItem*> items = ui->LW_ACTIVESKILLS->findItems(ui->LE_SKILLNAME->text(), Qt::MatchFlag::MatchExactly);
        if(items.size() != 0)
        {
            ui->L_SAVESTATUS->setText("This skill is already saved.");
            return;
        }
        partnerUsableSkills.insert(priority, UsableSkill(partnerSkills[currentSkillIndex]));
        partnerUsableSkills[priority].configure(ui->RB_CASTSECONDS->isChecked() ? ui->SB_CASTSECOND->value() : -1, ui->SB_DISTANCECAST->value(), static_cast<Target>(ui->CB_TARGET->currentIndex()));
        keys = partnerUsableSkills.keys();
        ui->LW_ACTIVESKILLS->insertItem(keys.indexOf(priority), QString::number(partnerSkills[currentSkillIndex]->getID()) + " " + partnerSkills[currentSkillIndex]->getName());
        ui->L_SAVESTATUS->setText("Saving successfull.");
        emit partnerUsableSkillsChanged(partnerUsableSkills);
        ui->SB_PRIORITY->setValue(ui->SB_PRIORITY->value() + 1);
    }
    else if(skillTypeUI == SkillTypeUI::Nosmate)
    {
        QList<int> sKeys = nosmateSkills.keys();
        if(!sKeys.contains(currentSkillIndex))
            return;
        int priority = ui->SB_PRIORITY->value();
        QList<int> keys = nosmateUsableSkills.keys();
        if(keys.contains(priority) && priority >= 0)
        {
            ui->L_SAVESTATUS->setText("Another skill has the same priority.");
            return;
        }
        QList<QListWidgetItem*> items = ui->LW_ACTIVESKILLS->findItems(ui->LE_SKILLNAME->text(), Qt::MatchFlag::MatchExactly);
        if(items.size() != 0)
        {
            ui->L_SAVESTATUS->setText("This skill is already saved.");
            return;
        }
        nosmateUsableSkills.insert(priority, UsableSkill(nosmateSkills[currentSkillIndex]));
        nosmateUsableSkills[priority].configure(ui->RB_CASTSECONDS->isChecked() ? ui->SB_CASTSECOND->value() : -1, ui->SB_DISTANCECAST->value(), static_cast<Target>(ui->CB_TARGET->currentIndex()));
        keys = nosmateUsableSkills.keys();
        ui->LW_ACTIVESKILLS->insertItem(keys.indexOf(priority), QString::number(nosmateSkills[currentSkillIndex]->getID()) + " " + nosmateSkills[currentSkillIndex]->getName());
        ui->L_SAVESTATUS->setText("Saving successfull.");
        emit nosmateUsableSkillsChanged(nosmateUsableSkills);
        ui->SB_PRIORITY->setValue(ui->SB_PRIORITY->value() + 1);
    }
}

void SkillsWidget::changeStatusWidget(bool enabled)
{
    ui->LE_SKILLNAME->setEnabled(enabled);
    ui->PB_SAVE->setEnabled(enabled);
    ui->PB_DEFAULT->setEnabled(enabled);
    ui->SB_PRIORITY->setEnabled(enabled);
    ui->LE_SKILLNAME->setEnabled(enabled);
    //ui->SB_CASTSECOND->setEnabled(enabled);
    ui->CB_TARGET->setEnabled(enabled);
    ui->SB_DISTANCECAST->setEnabled(enabled);
    ui->RB_CASTSECONDS->setEnabled(enabled);
    ui->RB_CASTAVAILABLE->setEnabled(enabled);
}

void SkillsWidget::on_PB_DELETE_clicked()
{
    int index = ui->LW_ACTIVESKILLS->currentRow();
    if(index < 0 || index >= ui->LW_ACTIVESKILLS->count())
        return;
    QListWidgetItem *row = ui->LW_ACTIVESKILLS->item(index);
    if(!row)
        return;
    int skillId = row->text().split(" ")[0].toInt();
    QList<int> keys = usableSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        if(usableSkills[keys[i]].getSkill()->getID() == skillId)
        {
            usableSkills.remove(keys[index]);
            ui->LW_ACTIVESKILLS->takeItem(index);
            emit usableSkillsChanged(usableSkills);
        }
    }
    keys = partnerUsableSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        if(partnerUsableSkills[keys[i]].getSkill()->getID() == skillId)
        {
            partnerUsableSkills.remove(keys[i/*ndex*/]);
            ui->LW_ACTIVESKILLS->takeItem(index);
            emit partnerUsableSkillsChanged(partnerUsableSkills);
        }
    }
    keys = nosmateUsableSkills.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        if(nosmateUsableSkills[keys[i]].getSkill()->getID() == skillId)
        {
            nosmateUsableSkills.remove(keys[i/*index*/]);
            ui->LW_ACTIVESKILLS->takeItem(index);
            emit nosmateUsableSkillsChanged(nosmateUsableSkills);
        }
    }
    /*if(!(index < 0 || index >= usableSkills.size()))
    {
        QList<int> keys = usableSkills.keys();
        usableSkills.remove(keys[index]);
        ui->LW_ACTIVESKILLS->takeItem(index);
        emit usableSkillsChanged(usableSkills);
    }
    if(!(index < 0 || index >= partnerUsableSkills.size()))
    {
        QList<int> keys = partnerUsableSkills.keys();
        partnerUsableSkills.remove(keys[index]);
        ui->LW_ACTIVESKILLS->takeItem(index);
        emit usableSkillsChanged(partnerUsableSkills);
    }*/
}

void SkillsWidget::on_RB_CASTSECONDS_clicked()
{
    if(ui->RB_CASTSECONDS->isChecked())
        ui->SB_CASTSECOND->setEnabled(true);
}

void SkillsWidget::on_PB_CLEAR_clicked()
{
    ui->LW_ACTIVESKILLS->clear();
    usableSkills.clear();
    partnerUsableSkills.clear();
    nosmateUsableSkills.clear();
    emit usableSkillsChanged(usableSkills);
    emit partnerUsableSkillsChanged(partnerUsableSkills);
    emit nosmateUsableSkillsChanged(nosmateUsableSkills);
}

UsableSkill::UsableSkill(Skill *RawSkill)
{
    skill = RawSkill;
}

void UsableSkill::configure(int MsCast, int DistanceMax, Target Target)
{
    msCast = MsCast;
    target = Target;
    if(msCast != -1)
        lastCast = QDateTime::currentDateTime().addMSecs(-msCast);
    distanceMax = DistanceMax;
}

Skill *UsableSkill::getSkill()
{
    return skill;
}

void SkillsWidget::on_RB_CASTAVAILABLE_clicked()
{
    if(ui->RB_CASTAVAILABLE->isChecked())
        ui->SB_CASTSECOND->setEnabled(false);
}
