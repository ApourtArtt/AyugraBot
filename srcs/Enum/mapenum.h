#ifndef MAPENUM_H
#define MAPENUM_H

enum class WorldMap
{
    LEFT    = 1,
    RIGHT   = 2
};

enum class MiniMapType
{
    DEFAULT = 0, // Common map (no resize, no special show)
    ACT5    = 1, // Typical Act5 map : resize and showing mob
    ACT6    = 2, // I can't remember how it looks like
    ACT7    = 3, // I can't remember how it looks like
};

#endif // MAPENUM_H
