#include "StoneDestroy.h"

StoneDestroy::StoneDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneDestroy);

    texture = new QPixmap(":/32px/images/32px/stone_destroy_32px.png");
    currentFrameX = 0;
    countFrames = 1;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &StoneDestroy::slotTimerFlicker);
}

StoneDestroy::~StoneDestroy()
{

}

void StoneDestroy::destroy()
{
    texture->load(":/32px/images/32px/sprites/stone_destroy_sprite_32.png");
    currentFrameX = 0;
    countFrames = 6;
    timerFlicker->start(500 / countFrames);
}

void StoneDestroy::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

QRectF StoneDestroy::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void StoneDestroy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
