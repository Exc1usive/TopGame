#include "EnemyNFS.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

EnemyNFS::EnemyNFS(QPointF position, QString _type, QObject *parent) : QObject(parent), QGraphicsItem()
{
    type = _type;
    readXmlConfig(type);

    health = parameters["health"].toInt();

    this->setPos(position);
    this->setZValue(9);
    texture = new QPixmap();
    this->setData(BombermanTypes::EnemyObject, BombermanTypes::Live);
    qDebug(logDebug()) << "Enemy is created:" << type << "pos:" << this->pos();

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &EnemyNFS::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &EnemyNFS::slotTimerGame);
    timerGame->start(parameters["timeoutGame"].toInt());

//    changeDirectionRandom();
    changeDirection(BombermanTypes::Right);

}

EnemyNFS::~EnemyNFS()
{

}

void EnemyNFS::kill()
{
    if(--health > 0)
        return;

    timerGame->stop();
    timerFlicker->stop();
    direction = BombermanTypes::Stop;
    texture->load(QApplication::applicationDirPath() + textures["dead"]["path"]);
    countFrames = textures["dead"]["count"].toInt();
    currentFrameX = 0;
    slotTimerFlicker();
    timerFlicker->start(parameters["timeoutUpdatePicture"].toInt());
}

void EnemyNFS::readXmlConfig(QString tag)
{
    qDebug(logDebug()) << "Read Xml Start" << "tag:" << tag;
    QFile file(QApplication::applicationDirPath() + "/enemy/enemy.xml");

    if(file.open(QFile::ReadOnly | QFile::Text))
        qDebug(logDebug()) << "Xml file is open";
    else
        qCritical(logCritical()) << "Xml file error" << file.errorString();

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while(xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == tag)
        {
            while(xmlReader.readNextStartElement())
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
            break;
        }
    }
    qDebug(logDebug()) << textures;
    qDebug(logDebug()) << parameters;
    qDebug(logDebug()) << "Xml file is read tag:" << tag;
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
            timerFlicker->start(parameters["timeoutUpdatePicture"].toInt());
        }
        return;
    }

    if(direct == BombermanTypes::Up)
    {
        qDebug(logDebug()) << texture->load(QApplication::applicationDirPath() + textures["up"]["path"]);
        countFrames = textures["up"]["count"].toInt();
    }
    else
        if(direct == BombermanTypes::Down)
        {
            qDebug(logDebug()) << texture->load(QApplication::applicationDirPath() + textures["down"]["path"]);
            countFrames = textures["down"]["count"].toInt();
        }
    else
            if(direct == BombermanTypes::Right)
            {
                qDebug(logDebug()) << texture->load(QApplication::applicationDirPath() + textures["right"]["path"]);
                countFrames = textures["right"]["count"].toInt();
            }
    else
                if(direct == BombermanTypes::Left)
                {
                    qDebug(logDebug()) << texture->load(QApplication::applicationDirPath() + textures["left"]["path"]);
                    countFrames = textures["left"]["count"].toInt();
                }

    qDebug(logDebug()) << "Enemy change direction" << direction << "-" << direct;
    direction = direct;
    currentFrameX = 0;
    slotTimerFlicker();
    timerFlicker->start(parameters["timeoutUpdatePicture"].toInt());
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
    return QRectF(0, 0, parameters["sizeWidth"].toInt(), parameters["sizeHeight"].toInt());
}

void EnemyNFS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *texture, currentFrameX, 0, parameters["sizeWidth"].toInt(), parameters["sizeHeight"].toInt());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void EnemyNFS::slotTimerFlicker()
{
    currentFrameX += parameters["sizeWidth"].toInt();

    if(currentFrameX >= parameters["sizeWidth"].toInt() * countFrames)
    {
        if(direction != BombermanTypes::Stop)
            currentFrameX = 0;
        else
        {
            qDebug(logDebug()) << "Enemy destroy (" << type << ")";
            this->deleteLater();
        }
    }
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
            this->setY(this->y() - parameters["speed"].toInt());
        if(direction == BombermanTypes::Down)
            this->setY(this->y() + parameters["speed"].toInt());
        if(direction == BombermanTypes::Left)
            this->setX(this->x() - parameters["speed"].toInt());
        if(direction == BombermanTypes::Right)
            this->setX(this->x() + parameters["speed"].toInt());

        bool change = false;

        for(QGraphicsItem *item : scene()->collidingItems(this))
        {
            if(item->data(1).toInt() == BombermanTypes::Bomb)
            {
                if(item != inBomb)
                {
                    changeDirectionCollisionBomb();
                    inBomb = item;
                    checkInBomb = true;
                    break;
                }
            }

            if(item->data(1).toInt() == BombermanTypes::StoneDestroy || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
            {
                if(direction == BombermanTypes::Up)
                {
                    this->setY(this->y() + parameters["speed"].toInt());
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Down)
                {
                    this->setY(this->y() - parameters["speed"].toInt());
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Left)
                {
                    this->setX(this->x() + parameters["speed"].toInt());
                    changeDirectionRandom();
                    change = true;
                    break;
                }
                if(direction == BombermanTypes::Right)
                {
                    this->setX(this->x() - parameters["speed"].toInt());
                    changeDirectionRandom();
                    change = true;
                    break;
                }
            }
        }
        if(scene()->collidingItems(this).isEmpty())
        {
                inBomb = NULL;
                checkInBomb = false;
        }

        if(!change)
            if(int (this->x()) % parameters["sizeWidth"].toInt() == 0 && int (this->y()) % parameters["sizeHeight"].toInt() == 0 && (rand() % 5 == 0 || rand() % 5 == 0))
                changeDirectionRandom();

    }
}
