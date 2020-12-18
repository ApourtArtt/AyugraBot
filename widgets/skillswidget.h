#ifndef SKILLSWIDGET_H
#define SKILLSWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDateTime>
#include "srcs/GameObjects/Properties/skill.h"

#include <QtDebug>

namespace Ui {
class SkillsWidget;
}

enum class SkillTypeUI
{
    Character = 1,
    Partner = 2,
    Nosmate = 3
};

enum class Target
{
    SELF = 0,
    MONSTER = 1,
    PET = 2,
    PARTNER = 3
};

class UsableSkill
{
public:
    UsableSkill(){}
    UsableSkill(Skill *RawSkill);
    void configure(int MsCast, int DistanceMax, Target Target);
    Skill *getSkill();
    Target getTarget() { return target; }
    int getSecondBetweenCast() { return msCast; }
    int getMaxRange() { return distanceMax; }
    void setPseudoCooldown(QDateTime current) { lastCast = current; }
    bool isCastablePseudoCooldown() { return QDateTime::currentDateTime() > lastCast.addMSecs(msCast); }

private:
    Skill *skill;
    int msCast;
    int distanceMax;
    Target target;
    QDateTime lastCast;
};

class SkillsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SkillsWidget(QWidget *parent = nullptr);
    ~SkillsWidget();
    void setSkills(QMap<int, Skill*> Skills);
    void setPartnerSkills(QMap<int, Skill*> Skills);
    void setNosmateSkills(QMap<int, Skill*> Skills);
    QMap<int, UsableSkill> getUsableSkills();
    QMap<int, UsableSkill> getPartnerUsableSkills();
    QMap<int, UsableSkill> getNosmateUsableSkills();

signals:
    void usableSkillsChanged(QMap<int, UsableSkill> UsableSkills);
    void partnerUsableSkillsChanged(QMap<int, UsableSkill> UsableSkills);
    void nosmateUsableSkillsChanged(QMap<int, UsableSkill> UsableSkills);

private slots:
    void on_LW_SKILLS_itemDoubleClicked(QListWidgetItem *item);
    void on_PB_DEFAULT_clicked();
    void on_PB_SAVE_clicked();
    void on_PB_DELETE_clicked();
    void on_PB_CLEAR_clicked();
    void on_RB_CASTSECONDS_clicked();
    void on_RB_CASTAVAILABLE_clicked();

private:
    void changeStatusWidget(bool enabled);
    Ui::SkillsWidget *ui;
    QMap<int, Skill*> skills, partnerSkills, nosmateSkills;
    QMap<int, UsableSkill> usableSkills, partnerUsableSkills, nosmateUsableSkills;
    int currentSkillIndex;
    SkillTypeUI skillTypeUI;
};

#endif // SKILLSWIDGET_H
