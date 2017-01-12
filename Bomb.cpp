#include "Bomb.h"

Bomb::Bomb(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::Bomb);

//    texture = new QPixmap(":/32px/images/32px/stone_destroy_32px.png");
    currentFrameX = 0;
    countFrames = 1;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Bomb::slotTimerFlicker);
    timerFlicker->start(250);

    timerDestroy = new QTimer();
    connect(timerDestroy, &QTimer::timeout, this, &Bomb::slotTimerDestroy);
    timerDestroy->start(2000);
}

Bomb::~Bomb()
{

}

void Bomb::destroy()
{
    slotTimerDestroy();
}

void Bomb::slotTimerFlicker()
{
//    currentFrameX += sizeCellWidth;

//    if(currentFrameX >= sizeCellWidth * countFrames)
//        this->deleteLater();
//    else
//            this->update(0, 0, sizeCellWidth, sizeCellHeight);

    if(color == Qt::black)
        color = Qt::red;
    else
        color = Qt::black;
    this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

void Bomb::slotTimerDestroy()
{
    setData(1, BombermanTypes::None);
    this->deleteLater();
}

QRectF Bomb::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    painter->setBrush(color);
    painter->drawEllipse(QPointF(16, 16), sizeCellWidth / 4, sizeCellHeight / 4);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
