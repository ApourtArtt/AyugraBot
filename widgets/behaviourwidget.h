#ifndef BEHAVIOURWIDGET_H
#define BEHAVIOURWIDGET_H

#include <QWidget>

enum class MateAI
{
    D, // Follow character
    S, // Don't move, don't attack
    A, // Move and attack but don't follow character
    SDS, // Defend but if out of range don't move
    SDR // Defend and if out of range, go to range
    // TODO : Attack in range and don't move
};

namespace Ui {
class BehaviourWidget;
}

class BehaviourWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BehaviourWidget(QWidget *parent = nullptr);
    ~BehaviourWidget();
    bool disconnectOnDeath();
    bool worOnDeath();
    bool repopOnDeath();
    int getHP() const;
    int getMP() const;
    int getHPGetUp() const;
    int getMPGetUp();

signals:
    void petAIChanged(MateAI aiType);
    void partnerAIChanged(MateAI aiType);

    void sitLowerThan(int hpPercent, int mpPercent, int hpPercentGetUp, int mpPercentGetUp);

    void goToMinilandEvery(int seconds);
    void stayInMinilandFor(int seconds);

    void distDropChanged(int detectionRange);

private slots:
    void on_SB_SITHP_valueChanged(int arg1);
    void on_SB_SITMP_valueChanged(int arg1);
    void on_SB_SITHP_2_valueChanged(int arg1);
    void on_SB_SITMP_2_valueChanged(int arg1);

    void on_SB_STAYMINILANDFOR_valueChanged(int arg1);
    void on_SB_GOTOMINILANDEVERY_valueChanged(int arg1);

    void on_RB_PET_D_clicked();
    void on_RB_PET_S_clicked();
    void on_RB_PET_A_clicked();
    void on_RB_PET_SD_clicked();
    void on_RB_PET_SD_RANGE_clicked();

    void on_RB_PART_D_clicked();
    void on_RB_PART_S_clicked();
    void on_RB_PART_A_clicked();
    void on_RB_PART_SD_clicked();
    void on_RB_PART_SD_RANGE_clicked();

    void on_SB_DROP_DIST_valueChanged(int arg1);

    void on_groupBox_4_clicked();
    void on_groupBox_3_clicked();

private:
    Ui::BehaviourWidget *ui;
};

#endif // BEHAVIOURWIDGET_H
