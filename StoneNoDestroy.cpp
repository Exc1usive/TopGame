#include "StoneNoDestroy.h"
#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

StoneNoDestroy::StoneNoDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneNoDestroy);

    readXmlConfig();

    texture = new QPixmap(QApplication::applicationDirPath() + textures["path"]);
    sizeCellWidth = parameters["sizeWidth"].toInt();
    sizeCellHeight = parameters["sizeHeight"].toInt();
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

    while(!xmlReader.atEnd())
    {
        if(xmlReader.tokenType() != QXmlStreamReader::StartElement)
        {
            xmlReader.readNext();
            continue;
        }
        if(xmlReader.name() == "stoneNoDestroy" && xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            while (xmlReader.readNextStartElement())
            {
                if(xmlReader.name() == "model")
                {
                    parameters["sizeWidth"] = xmlReader.attributes().value("sizeWidth").toString();
                    parameters["sizeHeight"] = xmlReader.attributes().value("sizeHeight").toString();
                    xmlReader.readNextStartElement();
                    textures["path"] = xmlReader.readElementText();
                }
                if(xmlReader.name() == "parameter")
                {
                    while(xmlReader.readNextStartElement())
                        parameters[xmlReader.name().toString()] = xmlReader.readElementText();
                }
            }
        }
        xmlReader.readNext();
    }

    if(file.isOpen())
        file.close();

    qDebug(logDebug()) << textures;
    qDebug(logDebug()) << parameters;
    qDebug(logDebug()) << "Xml file is read:"  << file.fileName();
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
