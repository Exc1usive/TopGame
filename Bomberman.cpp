#include "Bomb.h"
#include "Bomberman.h"

#include <QDebug>

Bomberman::Bomberman(QString _username, QObject *parent) : QObject(parent), QGraphicsItem()
{
    setZValue(10);
    texture = new QPixmap();
    username = _username;
    this->setData(BombermanTypes::Hero, BombermanTypes::Live);

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Bomberman::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &Bomberman::slotTimerGame);
    timerGame->start(20);

    changeDirection(BombermanTypes::Down);
}

Bomberman::~Bomberman()
{
    disconnect(this);
}

void Bomberman::kill()
{
    timerFlicker->stop();
    texture->load("");
    currentFrameX = 0;
}

void Bomberman::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        currentFrameX = 0;
}

void Bomberman::slotTimerGame()
{
    if(this->data(BombermanTypes::Hero).toInt() == BombermanTypes::Dead)
        return;

    if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT))
    {
        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion
                    || item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
            {
                kill();
                return;
            }
        }

        if(GetAsyncKeyState(VK_UP))
        {
            changeDirection(BombermanTypes::Up);
            this->setY(this->y() - speed);

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setY(this->y() + speed);

                }

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setY(this->y() + speed);
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            changeDirection(BombermanTypes::Down);
            this->setY(this->y() + speed);

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setY(this->y() - speed);
                }

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setY(this->y() - speed);
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            changeDirection(BombermanTypes::Right);
            this->setX(this->x() + speed);

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setX(this->x() - speed);

                }

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setX(this->x() - speed);
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            changeDirection(BombermanTypes::Left);
            this->setX(this->x() - speed);

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setX(this->x() + speed);

                }

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setX(this->x() + speed);
                    break;
                }
            }
        }

        if(scene()->collidingItems(this).isEmpty())
        {
                inBomb = NULL;
                checkInBomb = false;
        }
    }

    if(GetAsyncKeyState(VK_SPACE))
        emit setBomb(QPointF((int (this->x()) / 32) * 32, (int (this->y()) / 32) * 32), this->data(BombermanTypes::Username).toString(), damage);

    if(timerFlicker->isActive())
    {
        if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
        {

        }
        else
            timerFlicker->stop();
    }
/*
    if(GetAsyncKeyState(VK_UP))
    {
        changeDirection(BombermanTypes::Up);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion
                    || item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
            {
                kill();
                return;
            }
        }

        this->setY(this->y() - speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                qDebug() << "Bomb";
                if(item != inBomb)
                {
                    qDebug() << "set True";
                    inBomb = item;
                    checkInBomb = true;
                    break;
                }
            }

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
            if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion
                    || item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
            {
                kill();
                return;
            }
        }

        this->setY(this->y() + speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                qDebug() << "Bomb";
                if(item != inBomb)
                {
                    qDebug() << "set True";
                    inBomb = item;
                    checkInBomb = true;
                    break;
                }
            }

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
            if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion
                    || item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
            {
                kill();
                return;
            }
        }

        this->setX(this->x() + speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                qDebug() << "Bomb";
                if(item != inBomb)
                {
                    qDebug() << "set True";
                    inBomb = item;
                    checkInBomb = true;
                    break;
                }
            }

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
            if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion
                    || item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
            {
                kill();
                return;
            }
        }

        this->setX(this->x() - speed);

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                qDebug() << "Bomb";
                if(item != inBomb)
                {
                    qDebug() << "set True";
                    inBomb = item;
                    checkInBomb = true;
                    break;
                }
            }

            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                this->setX(this->x() + speed);
                break;
            }
        }
    }

    if(scene()->collidingItems(this).isEmpty())
    {
            inBomb = NULL;
            checkInBomb = false;
    }

    if(GetAsyncKeyState(VK_SPACE))
    {
        emit setBomb(QPointF((int (this->x()) / 32) * 32, (int (this->y()) / 32) * 32), this->data(BombermanTypes::Username).toString(), damage);
    }

    if(timerFlicker->isActive())
    {
        if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
        {

        }
        else
            timerFlicker->stop();
    }
    */
}

void Bomberman::getInstallBomb(QGraphicsItem *item)
{
    inBomb = item;
}

void Bomberman::changeDirection(const BombermanTypes::DirectionEnum direct)
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
