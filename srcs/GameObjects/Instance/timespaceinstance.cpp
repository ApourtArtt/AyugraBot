#include "timespaceinstance.h"

TimeSpaceInstance *TimeSpaceInstance::tsInstance = nullptr;

TimeSpaceInstance *TimeSpaceInstance::getInstance()
{
    if(tsInstance == nullptr)
        tsInstance = new TimeSpaceInstance;
    return tsInstance;
}

TimeSpaceInstance::TimeSpaceInstance()
{

}

TimeSpaceInstance::~TimeSpaceInstance()
{

}
