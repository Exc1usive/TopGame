#ifndef BOMBERMANTYPES_H
#define BOMBERMANTYPES_H

namespace BombermanTypes {
    enum { Hero = 0, Objects = 1, Username = 10};
    enum HeroEnum { Dead = 0, Live = 1 };
    enum DirectionEnum { Stop = 0, Up = 1, Down = 2, Right = 3, Left = 4 };
    enum ObjectsEnum { None = 0, HeroObject = 1, BookPlace = 2, StoneDestroy = 3, StoneNoDestroy = 4, Bomb = 5, Explosion = 6 };
}

#endif // BOMBERMANTYPES_H
