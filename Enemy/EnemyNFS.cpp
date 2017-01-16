#include "EnemyNFS.h"

EnemyNFS::EnemyNFS(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
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

EnemyNFS::~EnemyNFS()
{

}

void EnemyNFS::kill()
{
    timerFlicker->stop();
    texture->load("");
    currentFrameX = 0;
}

void EnemyNFS::slotTimerFlicker()
{

}

void EnemyNFS::slotTimerGame()
{

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

QRectF EnemyNFS::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void EnemyNFS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-16, -16, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
