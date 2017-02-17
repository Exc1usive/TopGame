#include "StoneDestroy.h"

#include <QApplication>
#include <QFile>
#include <QXmlStreamReader>

StoneDestroy::StoneDestroy(QPointF position, QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setPos(position);
    this->setData(1, BombermanTypes::StoneDestroy);

    readXmlConfig();

    texture = new QPixmap(QApplication::applicationDirPath() + textures["default"]["path"]);
    currentFrameX = 0;
    sizeCellWidth = parameters["sizeWidth"].toInt();
    sizeCellHeight = parameters["sizeHeight"].toInt();

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &StoneDestroy::slotTimerFlicker);
}

StoneDestroy::~StoneDestroy()
{

}

void StoneDestroy::destroy()
{
    texture->load(QApplication::applicationDirPath() + textures["destroy"]["path"]);
    currentFrameX = 0;
    countFrames = textures["destroy"]["count"].toInt();
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

    while(!xmlReader.atEnd())
    {
        if(xmlReader.tokenType() != QXmlStreamReader::StartElement)
        {
            xmlReader.readNext();
            continue;
        }
        if(xmlReader.name() == "stoneDestroy" && xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            while (xmlReader.readNextStartElement())
            {
                if(xmlReader.name() == "model")
                {
                    parameters["sizeWidth"] = xmlReader.attributes().value("sizeWidth").toString();
                    parameters["sizeHeight"] = xmlReader.attributes().value("sizeHeight").toString();
                    while(xmlReader.readNextStartElement())
                    {
                        textures[xmlReader.name().toString()]["count"] = xmlReader.attributes().value("count").toString();
                        textures[xmlReader.name().toString()]["path"] = xmlReader.readElementText();
                    }
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
