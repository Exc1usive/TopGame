#include "EnemyNFS.h"

#include <QDebug>

EnemyNFS::EnemyNFS(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    texture = new QPixmap();
//    this->setData(BombermanTypes::Hero, BombermanTypes::Live);

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &EnemyNFS::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &EnemyNFS::slotTimerGame);
    timerGame->start(50);

//    changeDirectionRandom();
    changeDirection(BombermanTypes::Right);
}

EnemyNFS::~EnemyNFS()
{

}

void EnemyNFS::kill()
{
    timerFlicker->stop();
    texture->load("");
    currentFrameX = 0;
}

void EnemyNFS::changeDirectionRandom(bool checkCurrent)
{
    int newDirection = 1 + rand() % 4;

    if(newDirection == BombermanTypes::Up && (direction != newDirection || !checkCurrent))
    {
        changeDirection(BombermanTypes::Up);
        return;
    }

    if(newDirection == BombermanTypes::Down && (direction != newDirection || !checkCurrent))
    {
        changeDirection(BombermanTypes::Down);
        return;
    }

    if(newDirection == BombermanTypes::Left && (direction != newDirection || !checkCurrent))
    {
        changeDirection(BombermanTypes::Left);
        return;
    }

    if(newDirection == BombermanTypes::Right && (direction != newDirection || !checkCurrent))
    {
        changeDirection(BombermanTypes::Right);
        return;
    }
}

void EnemyNFS::changeDirection(const BombermanTypes::DirectionEnum direct)
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

void EnemyNFS::changeDirectionCollisionBomb()
{
    if(direction == BombermanTypes::Up)
        changeDirection(BombermanTypes::Down);
    else
        if(direction == BombermanTypes::Down)
            changeDirection(BombermanTypes::Up);
    else
            if(direction == BombermanTypes::Right)
                changeDirection(BombermanTypes::Left);
    else
                if(direction == BombermanTypes::Left)
                    changeDirection(BombermanTypes::Right);
}

QRectF EnemyNFS::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void EnemyNFS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EnemyNFS::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        currentFrameX = 0;
}

void EnemyNFS::slotTimerGame()
{
    if(direction != BombermanTypes::Stop)
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

        if(direction == BombermanTypes::Up)
            this->setY(this->y() - speed);
        if(direction == BombermanTypes::Down)
            this->setY(this->y() + speed);
        if(direction == BombermanTypes::Left)
            this->setX(this->x() - speed);
        if(direction == BombermanTypes::Right)
            this->setX(this->x() + speed);

        bool change = false;

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                qDebug() << "Bomb";
                if(!inBomb)
                {
                    qDebug() << "set True";
                    changeDirectionCollisionBomb();
                    inBomb = true;
                    break;
                }
            }
            else
                if(inBomb)
                {
                    qDebug() << "set False";
                    inBomb = false;
                }

            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                if(direction == BombermanTypes::Up)
                {
                    this->setY(this->y() + speed);
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Down)
                {
                    this->setY(this->y() - speed);
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Left)
                {
                    this->setX(this->x() + speed);
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Right)
                {
                    this->setX(this->x() - speed );
                    changeDirectionRandom();
                    change = true;
                    break;
                }
            }
        }
        if(scene()->collidingItems(this).isEmpty())
        {
            if()
                inBomb = NULL;
        }

        if(!change)
            if(int (this->x()) % 32 == 0 && int (this->y()) % 32 == 0 && (rand() % 5 == 0 || rand() % 5 == 0))
                changeDirectionRandom();

    }
}
