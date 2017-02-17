#include "Bomb.h"
#include "Bomberman.h"
#include "ExplosionVertical.h"
#include "StoneDestroy.h"

#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

ExplosionVertical::ExplosionVertical(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(BombermanTypes::Objects, BombermanTypes::Explosion);

    readXmlConfig();

    texture = new QPixmap(QApplication::applicationDirPath() + textures["path"]);
    currentFrameX = 0;
    countFrames = textures["count"].toInt();
    sizeCellWidth = parameters["sizeWidth"].toInt();
    sizeCellHeight = parameters["sizeHeight"].toInt();

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &ExplosionVertical::slotTimerFlicker);
    timerFlicker->start(500 / countFrames);
}

ExplosionVertical::~ExplosionVertical()
{

}

bool ExplosionVertical::checkCollision()
{
    for(QGraphicsItem *item : scene()->collidingItems(this))
    {
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::ExplosionCenter)
        {
            this->deleteLater();
            return true;
        }
        if(item->data(BombermanTypes::Objects).toInt() == BombermanTypes::Explosion)
        {
            this->deleteLater();
        }
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

void ExplosionVertical::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

void ExplosionVertical::readXmlConfig()
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
                if(xmlReader.name() == "explosion-vertical")
                {
                    while(xmlReader.readNextStartElement())
                    {
                        if(xmlReader.name() == "model")
                        {
                            parameters["sizeWidth"] = xmlReader.attributes().value("sizeWidth").toString();
                            parameters["sizeHeight"] = xmlReader.attributes().value("sizeHeight").toString();
                            textures["count"] = xmlReader.attributes().value("count").toString();
                            textures["path"] = xmlReader.readElementText();
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

QRectF ExplosionVertical::boundingRect() const
{
    return QRectF(0, 0, sizeCellWidth, sizeCellHeight);
}

void ExplosionVertical::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
