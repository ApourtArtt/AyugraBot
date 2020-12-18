#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "formbase.h"
#include "srcs/GameObjects/Entity/mycharacter.h"
#include "modules/clickablelabel.h"
#include "ui_characterwidget.h"

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public FormBase
{
    Q_OBJECT

public:
    CharacterWidget(QVector<MyCharacter*> chars, QWidget *parent = nullptr);
    ~CharacterWidget() = default;
    void loadCharacters(QVector<MyCharacter*> chars);

signals:
    void selectedCharacter(short slot);
    void deletedCharacter(short slot);
    void createdCharacter(Class characterClass, QString pseudo, short slot, Gender gender, HairStyle hStyle, short hColor);

private slots:
    void on_PB_SELECT_clicked();
    void on_PB_DELETE_clicked();
    void on_PB_CREATE_clicked();
    void on_PB_CANCELCREATION_clicked();
    void on_PB_CREATEFINAL_clicked();

private:
    bool isEmptySlot(short slot);
    QString getPBText(MyCharacter *Char);
    void initialiseLabels(QVector<MyCharacter*> chars);
    void initialiseLabel(MyCharacter* Char);
    void handleClick(short slot);
    void enableSelectPB();
    void disableSelectPB();
    void enableDeletePB();
    void disableDeletePB();
    void enableCreatePB();
    void disableCreatePB();
    void colorClicked(ClickableLabel *label);

    Ui::CharacterWidget *ui;
    QVector<MyCharacter*> charList;
    short currentSelectedSlot;
    QMap<short, ClickableLabel*> colorToId;

    Class characterClass;
    HairStyle hairStyle;
    short hairColor;
    Gender gender;
};

#endif // ChHARACTERWIDGET_H
