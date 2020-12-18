#ifndef CHATENUM_H
#define CHATENUM_H

enum class ChatType {
    GENERAL_1               = 0,
    NOT_SHOWN_IN_CHAT       = 1,
    NOSMATE_1               = 2,
    PARTY                   = 3,
    NOSMATE_2               = 4,
    WHISPER_PLAYER          = 5,
    FAMILLY                 = 6,
    TS                      = 7,
    WHISPER_TO_GM           = 8,
    WHISPER_FROM_GM         = 9,
    SYSTEM_YELLOW           = 10,
    SYSTEM_RED              = 11,
    SYSTEM_GREEN            = 12,
    MESSAGE_SPEAKER         = 13,
    SYSTEM_GREY             = 14,
    WHISPER_GM_PURPLE       = 15,
    WHISPER_PLAYER_2        = 16,
    MESSAGE_SPEAKER_ITEM    = 17,
    MESSAGE_FROM_NOSCITY    = 30,
    MESSAGE_FROM_CYLLOAN    = 31
};

#endif // CHATENUM_H
