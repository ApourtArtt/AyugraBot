#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include "srcs/bot.h"

class BotManager : public Bot
{
public:
    explicit BotManager(QString xHash, QString hash, QString version, QObject *parent = nullptr);
};

#endif // BOTMANAGER_H
