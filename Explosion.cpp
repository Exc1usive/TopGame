#include "Bomb.h"
#include "Bomberman.h"
#include "Explosion.h"
#include "StoneDestroy.h"

Explosion::Explosion(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(BombermanTypes::Objects, BombermanTypes::ExplosionCenter);

    texture = new QPixmap(":/32px/images/32px/sprites/spriteExplosionCenter.png");
    currentFrameX = 0;
    countFrames = 11;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Explosion::slotTimerFlicker);
    timerFlicker->start(500 / countFrames);
}

Explosion::~Explosion()
{

}

bool Explosion::checkCollision()
{
    for(QGraphicsItem *item : scene()->collidingItems(this))
    {
        if(item->data(BombermanTypes::Hero).toInt() == BombermanTypes::Live)
        {
            Bomberman *it = qgraphicsitem_cast <Bomberman *> (item);
            it->kill();
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::StoneDestroy)
        {
            StoneDestroy *it = qgraphicsitem_cast <StoneDestroy *> (item);
            it->destroy();
            this->deleteLater();
            return true;
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::StoneNoDestroy)
        {
            this->deleteLater();
            return true;
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Bomb)
        {
            Bomb *it = qgraphicsitem_cast <Bomb *> (item);
            it->destroy();
            this->deleteLater();
            return true;
        }
    }
    return false;
}

void Explosion::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

QRectF Explosion::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
