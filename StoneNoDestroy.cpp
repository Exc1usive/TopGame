#include "StoneNoDestroy.h"
#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

StoneNoDestroy::StoneNoDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneNoDestroy);

    texture = new QPixmap(":/32px/images/32px/stone_no_destroy_32px.png");

    sizeCellWidth = 32;
    sizeCellHeight = 32;
}

StoneNoDestroy::~StoneNoDestroy()
{

}

void StoneNoDestroy::readXmlConfig()
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
        if(xmlReader.name() == "stoneNoDestroy")
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
}

QRectF StoneNoDestroy::boundingRect() const
{
    return QRectF(0, 0, 32, 32);
}

void StoneNoDestroy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, 0, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
