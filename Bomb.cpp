#include "Bomb.h"

Bomb::Bomb(QPointF position, int size, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::Bomb);
    distanceDamage = size;

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

    bool explosionLHBreak = false;
    for(int i = 1; i < distanceDamage + 1; i++)
    {
        ExplosionHorizontal *explosionLH = new ExplosionHorizontal(QPointF(this->x() - sizeCellWidth * i, this->y()));
        explosionLH->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionLH);
        explosionLHBreak = explosionLH->checkCollision();
//        if(explosionHBreak)
//            break;
    }

    bool explosionRHBreak = false;
    for(int i = 1; i < distanceDamage + 1; i++)
    {
        ExplosionHorizontal *explosionRH = new ExplosionHorizontal(QPointF(this->x() + sizeCellWidth * i, this->y()));
        explosionRH->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionRH);
        explosionRHBreak = explosionRH->checkCollision();
//        if(explosionHBreak)
//            break;
    }

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
