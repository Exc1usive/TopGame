#ifndef BOMBERMANTYPES_H
#define BOMBERMANTYPES_H

namespace BombermanTypes {
    enum Hero { Dead = 0, Live = 1 };
    enum Direction { Stop = 0, Up = 1, Down = 2, Right = 3, Left = 4 };
    enum Objects { None = 0, Hero = 1, BookPlace = 2, StoneDestroy = 3, StoneNoDestroy = 4, Bomb = 5 };
}

#endif // BOMBERMANTYPES_H
