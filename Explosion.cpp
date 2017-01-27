#include "Bomb.h"
#include "Bomberman.h"
#include "Explosion.h"
#include "StoneDestroy.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QApplication>

Explosion::Explosion(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(BombermanTypes::Objects, BombermanTypes::ExplosionCenter);

    texture = new QPixmap(":/32px/images/32px/sprites/spriteExplosionCenter.png");
    currentFrameX = 0;
    countFrames = 11;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Explosion::slotTimerFlicker);
    timerFlicker->start(500 / countFrames);
}

Explosion::~Explosion()
{

}

bool Explosion::checkCollision()
{
    for(QGraphicsItem *item : scene()->collidingItems(this))
    {
        if(item->data(BombermanTypes::Hero).toInt() == BombermanTypes::Live)
        {
            Bomberman *it = qgraphicsitem_cast <Bomberman *> (item);
            it->kill();
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::StoneDestroy)
        {
            StoneDestroy *it = qgraphicsitem_cast <StoneDestroy *> (item);
            it->destroy();
            this->deleteLater();
            return true;
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::StoneNoDestroy)
        {
            this->deleteLater();
            return true;
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Bomb)
        {
            Bomb *it = qgraphicsitem_cast <Bomb *> (item);
            it->destroy();
            this->deleteLater();
            return true;
        }
    }
    return false;
}

void Explosion::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

void Explosion::readXmlConfig()
{
    QFile file(QApplication::applicationDirPath() + "/config/bomb.xml");

    if(file.open(QFile::ReadOnly | QFile::Text))
        qDebug(logDebug()) << "Xml file is open:" << file.fileName();
    else
        qCritical(logCritical()) << "Xml file error" << file.errorString();

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while(xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == "explosions")
        {
            while(xmlReader.readNextStartElement())
            {
                if(xmlReader.name() == "explosion-center")
                {
                    while(xmlReader.readNextStartElement())
                    {
                        if(xmlReader.name() == "model")
                        {
                            parameters["sizeWidth"] = xmlReader.attributes().value("sizeWidth").toString();
                            parameters["sizeHeight"] = xmlReader.attributes().value("sizeHeight").toString();
                            textures["count"] = xmlReader.attributes().value("count").toString();
                            textures["path"] = xmlReader.readElementText();
                            break;
                        }
                    }
                }
                if(xmlReader.name() == "parameter")
                {
                    while(xmlReader.readNextStartElement())
                        parameters[xmlReader.name().toString()] = xmlReader.readElementText();
                }
            }
        }
    }

    if(file.isOpen())
        file.close();

    qDebug(logDebug()) << textures;
    qDebug(logDebug()) << parameters;
    qDebug(logDebug()) << "Xml file is read:"  << file.fileName();
}

QRectF Explosion::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
