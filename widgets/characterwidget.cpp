#include "characterwidget.h"

CharacterWidget::CharacterWidget(QVector<MyCharacter*> chars, QWidget *parent)
    : FormBase(parent)
    , ui(new Ui::CharacterWidget)
{
    ui->setupUi(this);
    hairColor = 0;
    characterClass = Class::ADVENTURER;
    hairStyle = HairStyle::HAIRSTYLE_A;
    gender = Gender::MALE;
    colorToId.insert(0, ui->L_0);
    colorToId.insert(1, ui->L_1);
    colorToId.insert(2, ui->L_2);
    colorToId.insert(3, ui->L_3);
    colorToId.insert(4, ui->L_4);
    colorToId.insert(5, ui->L_5);
    colorToId.insert(6, ui->L_6);
    colorToId.insert(7, ui->L_7);
    colorToId.insert(8, ui->L_8);
    colorToId.insert(9, ui->L_9);
    setWindowTitle(tr("Character selection"));
    loadCharacters(chars);
    if(chars.size() == 0)
    {
        ui->stackedWidget->setCurrentIndex(1);
        currentSelectedSlot = 0;
    }
    else
        ui->stackedWidget->setCurrentIndex(0);
    connect(ui->L_SLOT0, &ClickableLabel::leftClicked, this, [this]{handleClick(0);});
    connect(ui->L_SLOT1, &ClickableLabel::leftClicked, this, [this]{handleClick(1);});
    connect(ui->L_SLOT2, &ClickableLabel::leftClicked, this, [this]{handleClick(2);});
    connect(ui->L_SLOT3, &ClickableLabel::leftClicked, this, [this]{handleClick(3);});
    connect(ui->L_HAIRSTYLEA, &ClickableLabel::leftClicked, this, [this]
    {
        hairStyle = HairStyle::HAIRSTYLE_A;
        ui->L_HAIRSTYLEA->setPixmap(QPixmap(":/charcreation/lhairstyleas.png"));
        ui->L_HAIRSTYLEB->setPixmap(QPixmap(":/charcreation/lhairstyleb.png"));
    });
    connect(ui->L_HAIRSTYLEB, &ClickableLabel::leftClicked, this, [this]
    {
        hairStyle = HairStyle::HAIRSTYLE_B;
        ui->L_HAIRSTYLEA->setPixmap(QPixmap(":/charcreation/lhairstylea.png"));
        ui->L_HAIRSTYLEB->setPixmap(QPixmap(":/charcreation/lhairstylebs.png"));
    });
    connect(ui->L_MALE, &ClickableLabel::leftClicked, this, [this]
    {
        gender = Gender::MALE;
        ui->L_MALE->setPixmap(QPixmap(":/charcreation/lmales.png"));
        ui->L_FEMALE->setPixmap(QPixmap(":/charcreation/lfemale.png"));
        if(characterClass == Class::ADVENTURER)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvmalems.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmamalem.png"));
        }
        else if (characterClass == Class::MARTIAL_ARTIST)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvmalem.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmamalems.png"));
        }
    });
    connect(ui->L_FEMALE, &ClickableLabel::leftClicked, this, [this]
    {
        gender = Gender::FEMALE;
        ui->L_MALE->setPixmap(QPixmap(":/charcreation/lmale.png"));
        ui->L_FEMALE->setPixmap(QPixmap(":/charcreation/lfemales.png"));

        if(characterClass == Class::ADVENTURER)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvfemalems.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmafemalem.png"));
        }
        else if (characterClass == Class::MARTIAL_ARTIST)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvfemalem.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmafemalems.png"));
        }
    });
    connect(ui->L_ADV, &ClickableLabel::leftClicked, this, [this]
    {
        characterClass = Class::ADVENTURER;
        if(gender == Gender::FEMALE)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvfemalems.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmafemalem.png"));
        }
        else
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvmalems.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmamalem.png"));
        }
    });
    connect(ui->L_MA, &ClickableLabel::leftClicked, this, [this]
    {
        characterClass = Class::MARTIAL_ARTIST;
        if(gender == Gender::FEMALE)
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvfemalem.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmafemalems.png"));
        }
        else
        {
            ui->L_ADV->setPixmap(QPixmap(":/charcreation/ladvmalem.png"));
            ui->L_MA->setPixmap(QPixmap(":/charcreation/lmamalems.png"));
        }
    });
    connect(ui->L_0, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_0);});
    connect(ui->L_1, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_1);});
    connect(ui->L_2, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_2);});
    connect(ui->L_3, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_3);});
    connect(ui->L_4, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_4);});
    connect(ui->L_5, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_5);});
    connect(ui->L_6, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_6);});
    connect(ui->L_7, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_7);});
    connect(ui->L_8, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_8);});
    connect(ui->L_9, &ClickableLabel::leftClicked, this, [this]{colorClicked(ui->L_9);});
}

void CharacterWidget::loadCharacters(QVector<MyCharacter *> chars)
{
    initialiseLabels(chars);
    charList = chars;
    currentSelectedSlot = -1;
}

bool CharacterWidget::isEmptySlot(short slot)
{
    for(int i = 0 ; i < charList.size() ; i++)
    {
        if(charList[i]->getSlot() == slot)
            return false;
    }
    return true;
}

void CharacterWidget::initialiseLabels(QVector<MyCharacter *> chars)
{
    for(int i = 0 ; i < chars.size() ; i++)
    {
        if(chars[i]->getSlot() == 0)
            ui->L_SLOT0->setText(getPBText(chars[i]));
        else if(chars[i]->getSlot() == 1)
            ui->L_SLOT1->setText(getPBText(chars[i]));
        else if(chars[i]->getSlot() == 2)
            ui->L_SLOT2->setText(getPBText(chars[i]));
        else if(chars[i]->getSlot() == 3)
            ui->L_SLOT3->setText(getPBText(chars[i]));
    }
}

QString CharacterWidget::getPBText(MyCharacter *Char)
{

    Level lvl = Char->getLevelProperties();
    Class charClass = Char->getClass();
    QString classLabel =
            charClass == Class::ADVENTURER     ? tr("Adventurer")     :
            charClass == Class::SWORDSMAN      ? tr("Swordsman")      :
            charClass == Class::ARCHER         ? tr("Archer")         :
            charClass == Class::MAGICIAN       ? tr("Magician")       :
            charClass == Class::MARTIAL_ARTIST ? tr("Martial Artist") :
            "";
    return Char->getPseudonym() + " - " + classLabel + "\n" +
            QString::number(lvl.getLevel()) + "+" + QString::number(lvl.getLevelHero());
}

void CharacterWidget::on_PB_DELETE_clicked()
{
    QString pseudo = "";
    for(int i = 0 ; i < charList.size() ; i++)
    {
        if(charList[i]->getSlot() == currentSelectedSlot)
            pseudo = charList[i]->getPseudonym();
    }
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setText(tr("Do you really want to delete %1 ?").arg(pseudo));
    if(msgBox.exec() == QMessageBox::Yes)
        emit deletedCharacter(currentSelectedSlot);
}

void CharacterWidget::on_PB_CREATEFINAL_clicked()
{
    QString pseudonym = ui->LE_PSEUDONYM->text();
    if(pseudonym.isEmpty())
        return;
    if(hairColor == -1)
        return;
    ui->stackedWidget->setCurrentIndex(0);
    emit createdCharacter(characterClass, pseudonym, currentSelectedSlot, gender, hairStyle, hairColor);
}

void CharacterWidget::on_PB_SELECT_clicked()
{
    emit selectedCharacter(currentSelectedSlot);
}

void CharacterWidget::colorClicked(ClickableLabel *label)
{
    hairColor = colorToId.key(label);
    for(int i = 0 ; i < colorToId.size() ; i++)
    {
        ClickableLabel *tmp = colorToId.value(static_cast<short>(i));
        if(tmp != label)
            tmp->setPixmap(QPixmap(":/charcreation/l" + QString::number(i) + ".png"));
        else
            label->setPixmap(QPixmap(":/charcreation/l" + QString::number(i) + "s.png"));
    }
}

void CharacterWidget::handleClick(short slot)
{
    currentSelectedSlot = slot;
    if(!isEmptySlot(slot))
    {
        enableSelectPB();
        enableDeletePB();
        disableCreatePB();
    }
    else
    {
        disableSelectPB();
        disableDeletePB();
        enableCreatePB();
    }
}

void CharacterWidget::on_PB_CANCELCREATION_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CharacterWidget::on_PB_CREATE_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CharacterWidget::enableSelectPB()
{
    if(!ui->PB_SELECT->isEnabled())
        ui->PB_SELECT->setEnabled(true);
}

void CharacterWidget::disableSelectPB()
{
    if(ui->PB_SELECT->isEnabled())
        ui->PB_SELECT->setEnabled(false);
}

void CharacterWidget::enableDeletePB()
{
    if(!ui->PB_DELETE->isEnabled())
        ui->PB_DELETE->setEnabled(true);
}

void CharacterWidget::disableDeletePB()
{
    if(ui->PB_DELETE->isEnabled())
        ui->PB_DELETE->setEnabled(false);
}

void CharacterWidget::enableCreatePB()
{
    if(!ui->PB_CREATE->isEnabled())
        ui->PB_CREATE->setEnabled(true);
}

void CharacterWidget::disableCreatePB()
{
    if(ui->PB_CREATE->isEnabled())
        ui->PB_CREATE->setEnabled(false);
}
