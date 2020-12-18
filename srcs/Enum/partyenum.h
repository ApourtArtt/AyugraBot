#ifndef PARTYENUM_H
#define PARTYENUM_H

enum class PartyRequestType
{
    REQUESTED      = 0,
    INVITED        = 1,
    ACCEPTED       = 3,
    DECLINED       = 4,
    SHARING        = 5,
    ACCEPTED_SHARE = 6,
    DECLINED_SHARE = 7
};

#endif // PARTYENUM_H
