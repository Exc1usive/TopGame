#include "Coin.h"

Coin::Coin(QPointF position, QObject *parent) : EnemyNFS(position, parent)
{
    setTexture("up", 1, "pathpath");
}

Coin::~Coin()
{

}
