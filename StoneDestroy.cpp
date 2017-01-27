#include "StoneDestroy.h"

#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

StoneDestroy::StoneDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneDestroy);

    texture = new QPixmap(":/32px/images/32px/stone_destroy_32px.png");
    currentFrameX = 0;
    countFrames = 1;

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &StoneDestroy::slotTimerFlicker);
}

StoneDestroy::~StoneDestroy()
{

}

void StoneDestroy::destroy()
{
    texture->load(":/32px/images/32px/sprites/stone_destroy_sprite_32.png");
    currentFrameX = 0;
    countFrames = 6;
    timerFlicker->start(500 / countFrames);
}

void StoneDestroy::slotTimerFlicker()
{
    currentFrameX += sizeCellWidth;

    if(currentFrameX >= sizeCellWidth * countFrames)
        this->deleteLater();
    else
        this->update(0, 0, sizeCellWidth, sizeCellHeight);
}

void StoneDestroy::readXmlConfig()
{
    QFile file(QApplication::applicationDirPath() + "/config/stones.xml");

    if(file.open(QFile::ReadOnly | QFile::Text))
        qDebug(logDebug()) << "Xml file is open:" << file.fileName();
    else
        qCritical(logCritical()) << "Xml file error" << file.errorString();

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while(xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == "stoneDestroy")
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

QRectF StoneDestroy::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void StoneDestroy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
