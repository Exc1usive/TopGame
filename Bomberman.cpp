#include "Bomb.h"
#include "Bomberman.h"

#include <QDebug>

Bomberman::Bomberman(QObject *parent) : QObject(parent), QGraphicsItem()
{
    texture = new QPixmap();

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Bomberman::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &Bomberman::slotTimerGame);
    timerGame->start(20);

    changeDirection(BombermanTypes::Down);
}

Bomberman::~Bomberman()
{

}

void Bomberman::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;
    qDebug() << currentFrameX;

    if(currentFrameX >= sizeCellWidth * countFrames)
    {
        qDebug() << "set 0";
        currentFrameX = 0;
    }
}

void Bomberman::slotTimerGame()
{
    if(GetAsyncKeyState(VK_UP))
    {
        changeDirection(BombermanTypes::Up);

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
        changeDirection(BombermanTypes::Down);

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
        changeDirection(BombermanTypes::Right);

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
        changeDirection(BombermanTypes::Left);

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

    if(timerFlicker->isActive())
    {
        if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
        {

        }
        else
        {
            qDebug() << "stop";
            timerFlicker->stop();
        }
    }
}

void Bomberman::changeDirection(const BombermanTypes::Direction direct)
{
    if(direct == direction)
    {
        if(!timerFlicker->isActive())
        {
            slotTimerFlicker();
            timerFlicker->start(100);
        }
        return;
    }

    qDebug() << direct;
    if(direct == BombermanTypes::Up)
        texture->load(":/32px/images/32px/sprites/quandSpriteUp_32px.png");
    else
        if(direct == BombermanTypes::Down)
            texture->load(":/32px/images/32px/sprites/quandSpriteDown_32px.png");
    else
            if(direct == BombermanTypes::Right)
                texture->load(":/32px/images/32px/sprites/quandSpriteRight_32px.png");
    else
                if(direct == BombermanTypes::Left)
                    texture->load(":/32px/images/32px/sprites/quandSpriteLeft_32px.png");

    direction = direct;
    currentFrameX = 0;
    countFrames = 4;
    slotTimerFlicker();
    timerFlicker->start(100);
}

QRectF Bomberman::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void Bomberman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-16, -16, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
