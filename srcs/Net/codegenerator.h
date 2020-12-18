#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "networkrequester.h"
#include <QMap>

const QMap <QString, QString> langToLocale
{
    { "EN", "en_uk" },
    { "DE", "de_DE" },
    { "FR", "fr_FR" },
    { "IT", "it_IT" },
    { "PL", "pl_PL" },
    { "ES", "es_ES" },
    { "RU", "ru_RU" },
    { "CZ", "cs_CZ" },
    { "TR", "tr_TR" }
};

const QMap <QString, int> langToId
{
    { "EN", 0 },
    { "DE", 1 },
    { "FR", 2 },
    { "IT", 3 },
    { "PL", 4 },
    { "ES", 5 },
    { "RU", 6 },
    { "CZ", 7 },
    { "TR", 8 }
};

class CodeGenerator : public QObject
{
    Q_OBJECT
public:
    CodeGenerator(QString username, QString password, QString lang, QString gfuid = nullptr, QObject *parent = nullptr);
    QString connectToAccount(QString username, QString password, QString lang, QString gfuid = nullptr);
    QString getCode();

signals:
    void codeRecieved(QString code);

private:
    void retrieveEmailAddress();
    void connectWithEmail();
    void retrieveCode();

    NetworkRequester netRequester;
    QString token;
    QString platformGameAccountID;
    QString email;
    QString code;
    QString currentUsername, currentPassword, currentGfuid;
    QString local, gflang;

    const QString PLATFORMGAMEID = "dd4e22d6-00d1-44b9-8126-d8b40e0cd7c9";
    const QString POSSIBLE_CHARACTER = "0123456789abcdef";
};

#endif // CODEGENERATOR_H
