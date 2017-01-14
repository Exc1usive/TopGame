#include "Bomb.h"
#include "Bomberman.h"
#include "ExplosionVertical.h"
#include "StoneDestroy.h"

ExplosionVertical::ExplosionVertical(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(BombermanTypes::Objects, BombermanTypes::Explosion);

    texture = new QPixmap(":/32px/images/32px/sprites/spriteExplosionVertical.png");
    currentFrameX = 0;
    countFrames = 11;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &ExplosionVertical::slotTimerFlicker);
    timerFlicker->start(500 / countFrames);
}

ExplosionVertical::~ExplosionVertical()
{

}

bool ExplosionVertical::checkCollision()
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

void ExplosionVertical::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

QRectF ExplosionVertical::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void ExplosionVertical::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
