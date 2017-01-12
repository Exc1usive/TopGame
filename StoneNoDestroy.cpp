#include "StoneNoDestroy.h"

StoneNoDestroy::StoneNoDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneNoDestroy);

    texture = new QPixmap(":/32px/images/32px/stone_no_destroy_32px.png");

    sizeCellWidth = 32;
    sizeCellHeight = 32;
}

StoneNoDestroy::~StoneNoDestroy()
{

}

QRectF StoneNoDestroy::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void StoneNoDestroy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, 0, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
