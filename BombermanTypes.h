#ifndef BOMBERMANTYPES_H
#define BOMBERMANTYPES_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)

Q_LOGGING_CATEGORY(logDebug,    "Debug")
Q_LOGGING_CATEGORY(logInfo,     "Info")
Q_LOGGING_CATEGORY(logWarning,  "Warning")
Q_LOGGING_CATEGORY(logCritical, "Critical")

namespace BombermanTypes {
    enum { Hero = 0, Objects = 1, Username = 10};
    enum HeroEnum { Dead = 0, Live = 1 };
    enum DirectionEnum { Stop = 0, Up = 1, Down = 2, Right = 3, Left = 4 };
    enum ObjectsEnum { None = 0, HeroObject = 1, BookPlace = 2, StoneDestroy = 3, StoneNoDestroy = 4, Bomb = 5, ExplosionCenter = 6, Explosion = 7};
}

#endif // BOMBERMANTYPES_H
