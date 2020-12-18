#ifndef TIMESPACEINSTANCE_H
#define TIMESPACEINSTANCE_H

#include <QObject>

class TimeSpaceInstance : public QObject
{
    Q_OBJECT
public:
    static TimeSpaceInstance *getInstance();

signals:
    void tsPopUp();

private:
    TimeSpaceInstance();
    ~TimeSpaceInstance();

    TimeSpaceInstance(const TimeSpaceInstance&) = delete;
    TimeSpaceInstance& operator=(const TimeSpaceInstance&) = delete;

    static TimeSpaceInstance *tsInstance;
};

#endif // TIMESPACEINSTANCE_H
