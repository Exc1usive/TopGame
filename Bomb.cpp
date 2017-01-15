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
    emit bombDestroyed(this->pos());

    Explosion *explosion = new Explosion(this->pos());
    explosion->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
    scene()->addItem(explosion);
    explosion->checkCollision();

    bool explosionLHBreak = false;
    for(int i = 1; i < distanceDamage; i++)
    {
        ExplosionHorizontal *explosionLH = new ExplosionHorizontal(QPointF(this->x() - sizeCellWidth * i, this->y()));
        explosionLH->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionLH);
        explosionLHBreak = explosionLH->checkCollision();
        if(explosionLHBreak)
            break;
    }
    if(!explosionLHBreak)
    {
        ExplosionLeftFinish *explosionLF = new ExplosionLeftFinish(QPointF(this->x() - sizeCellWidth * distanceDamage, this->y()));
        explosionLF->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionLF);
        explosionLF->checkCollision();
    }

    bool explosionRHBreak = false;
    for(int i = 1; i < distanceDamage; i++)
    {
        ExplosionHorizontal *explosionRH = new ExplosionHorizontal(QPointF(this->x() + sizeCellWidth * i, this->y()));
        explosionRH->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionRH);
        explosionRHBreak = explosionRH->checkCollision();
        if(explosionRHBreak)
            break;
    }
    if(!explosionRHBreak)
    {
        ExplosionRightFinish *explosionRF = new ExplosionRightFinish(QPointF(this->x() + sizeCellWidth * distanceDamage, this->y()));
        explosionRF->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionRF);
        explosionRF->checkCollision();
    }

    bool explosionUVBreak = false;
    for(int i = 1; i < distanceDamage; i++)
    {
        ExplosionVertical *explosionUV = new ExplosionVertical(QPointF(this->x(), this->y() - sizeCellWidth * i));
        explosionUV->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionUV);
        explosionUVBreak = explosionUV->checkCollision();
        if(explosionUVBreak)
            break;
    }
    if(!explosionUVBreak)
    {
        ExplosionUpFinish *explosionUF = new ExplosionUpFinish(QPointF(this->x(), this->y() - sizeCellWidth * distanceDamage));
        explosionUF->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionUF);
        explosionUF->checkCollision();
    }

    bool explosionDVBreak = false;
    for(int i = 1; i < distanceDamage; i++)
    {
        ExplosionVertical *explosionDV = new ExplosionVertical(QPointF(this->x(), this->y() + sizeCellWidth * i));
        explosionDV->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionDV);
        explosionDVBreak = explosionDV->checkCollision();
        if(explosionDVBreak)
            break;
    }
    if(!explosionDVBreak)
    {
        ExplosionDownFinish *explosionDF = new ExplosionDownFinish(QPointF(this->x(), this->y() + sizeCellWidth * distanceDamage));
        explosionDF->setData(BombermanTypes::Username, this->data(BombermanTypes::Username).toString());
        scene()->addItem(explosionDF);
        explosionDF->checkCollision();
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
