#include "Bomb.h"
#include "Bomberman.h"

#include <QDebug>

Bomberman::Bomberman(QObject *parent) : QObject(parent), QGraphicsItem()
{
    currentFrameX = 96;
    currentFrameY = 96;

    direction = BombermanTypes::Stop;

    texture = new QPixmap(":/32px/images/32px/sprites/quandSprite_32px.png");

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Bomberman::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &Bomberman::slotTimerGame);
    timerGame->start(20);
}

Bomberman::~Bomberman()
{

}

void Bomberman::slotTimerFlicker()
{

}

void Bomberman::slotTimerGame()
{
    if(GetAsyncKeyState(VK_UP))
    {
        direction = BombermanTypes::Up;
        slotTimerFlicker();

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(0).toInt() == 1)
            {

            }
        }

        this->setY(this->y() - speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                this->setY(this->y() + speed);
                break;
            }
        }
    }
    if(GetAsyncKeyState(VK_DOWN))
    {
        direction = BombermanTypes::Down;
        slotTimerFlicker();

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(0).toInt() == 1)
            {

            }
        }

        this->setY(this->y() + speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                this->setY(this->y() - speed);
                break;
            }
        }
    }
    if(GetAsyncKeyState(VK_RIGHT))
    {
        direction = BombermanTypes::Right;
        slotTimerFlicker();

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(0).toInt() == 1)
            {

            }
        }

        this->setX(this->x() + speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                this->setX(this->x() - speed);
                break;
            }
        }
    }
    if(GetAsyncKeyState(VK_LEFT))
    {
        direction = BombermanTypes::Left;
        slotTimerFlicker();

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(0).toInt() == 1)
            {

            }
        }

        this->setX(this->x() - speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                this->setX(this->x() + speed);
                break;
            }
        }
    }
    if(GetAsyncKeyState(VK_SPACE))
    {
        Bomb *bomb = new Bomb(QPointF((int (this->x()) / 32) * 32, (int (this->y()) / 32) * 32));
        scene()->addItem(bomb);
    }
}

QRectF Bomberman::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void Bomberman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-16, -16, *texture, currentFrameX, currentFrameY, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
