#ifndef BLOCKINGOPTION_H
#define BLOCKINGOPTION_H

enum class BlockingOption
{
    EXCHANGE        = 1,
    FRIEND          = 2,
    FAMILLY         = 3,
    WHISPER         = 4,
    GROUP           = 5,
    GROUP_SHARING   = 8, // 0 : Share 1 : Selfish
    SPEAKER         = 10,
    MINILAND        = 15
};

#endif // BLOCKINGOPTION_H
