#ifndef COIN_H
#define COIN_H

#include "EnemyNFS.h"

class Coin : public EnemyNFS
{
public:
    explicit Coin(QPointF position, QObject *parent = 0);
    ~Coin();

};

#endif // COIN_H
