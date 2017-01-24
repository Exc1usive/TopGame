#include "Bomb.h"
#include "Bomberman.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

#define WALKBOMB true
#define LOGCHANGEDIRECTION true

Bomberman::Bomberman(QString _username, int _idType, QObject *parent) : QObject(parent), QGraphicsItem()
{
    readXmlConfig();

    setZValue(10);
    texture = new QPixmap();
    username = _username;
    idType = _idType;
    qDebug(logDebug()) << "Bomberman:" << username << "is created. Type:" << idType;

    this->setData(BombermanTypes::Objects, BombermanTypes::HeroObject);
    this->setData(BombermanTypes::Hero, BombermanTypes::Live);

    timerFlicker = new QTimer();
    connect(timerFlicker, &QTimer::timeout, this, &Bomberman::slotTimerFlicker);

    timerGame = new QTimer();
    connect(timerGame, &QTimer::timeout, this, &Bomberman::slotTimerGame);
    timerGame->start(20);

    changeDirection(BombermanTypes::Down);
}

Bomberman::~Bomberman()
{
    disconnect(this);
}

void Bomberman::kill()
{
//    timerGame->stop();
//    timerFlicker->stop();
//    direction = BombermanTypes::Stop;
//    this->setData(BombermanTypes::Hero, BombermanTypes::Dead);
//    texture->load(QApplication::applicationDirPath() + textures[idType]["dead"]["path"]);
//    countFrames = textures[idType]["dead"]["count"].toInt();
//    currentFrameX = 0;
//    slotTimerFlicker();
//    timerFlicker->start(parameters["timeoutUpdatePicture"].toInt());
}

void Bomberman::slotTimerFlicker()
{
    currentFrameX += parameters["sizeWidth"].toInt();

    if(currentFrameX >= parameters["sizeWidth"].toInt() * countFrames)
    {
        if(this->data(BombermanTypes::Hero).toInt() != BombermanTypes::Dead)
            currentFrameX = 0;
        else
        {
            this->update(-parameters["sizeWidth"].toInt() / 2, -parameters["sizeHeight"].toInt() / 2, parameters["sizeWidth"].toInt(), parameters["sizeHeight"].toInt());
            qDebug(logDebug()) << "Bomberman destroy (" << idType << ";" << username << ")";
//            this->deleteLater();
        }
    }
}

void Bomberman::slotTimerGame()
{
    if(this->data(BombermanTypes::Hero).toInt() == BombermanTypes::Dead)
        return;

    if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT))
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

        if(GetAsyncKeyState(VK_UP))
        {
            changeDirection(BombermanTypes::Up);
            this->setY(this->y() - parameters["speed"].toInt());

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
#if WALKBOMB == true
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
//                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setY(this->y() + parameters["speed"].toInt());

                }
#endif

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setY(this->y() + parameters["speed"].toInt());
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            changeDirection(BombermanTypes::Down);
            this->setY(this->y() + parameters["speed"].toInt());

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
#if WALKBOMB == true
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
//                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setY(this->y() - parameters["speed"].toInt());

                }
#endif
                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setY(this->y() - parameters["speed"].toInt());
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            changeDirection(BombermanTypes::Right);
            this->setX(this->x() + parameters["speed"].toInt());

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
#if WALKBOMB == true
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
//                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setX(this->x() - parameters["speed"].toInt());

                }
#endif

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setX(this->x() - parameters["speed"].toInt());
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            changeDirection(BombermanTypes::Left);
            this->setX(this->x() - parameters["speed"].toInt());

            for(QGraphicsItem *item : scene()->collidingItems(this))
            {
#if WALKBOMB == true
                if(item->data(1).toInt() == BombermanTypes::Bomb)
                {
//                    qDebug() << inBomb;
                    if(item != inBomb)
                        this->setX(this->x() + parameters["speed"].toInt());
                }
#endif

                if(item->data(1).toInt() == BombermanTypes::StoneDestroy
                        || item->data(1).toInt() == BombermanTypes::StoneNoDestroy)
                {
                    this->setX(this->x() + parameters["speed"].toInt());
                    break;
                }
            }
        }

        if(scene()->collidingItems(this).isEmpty())
        {
                inBomb = NULL;
                checkInBomb = false;
        }
    }

    if(GetAsyncKeyState(VK_SPACE))
        emit setBomb(QPointF((int (this->x()) / parameters["sizeWidth"].toInt()) * parameters["sizeWidth"].toInt(),
            (int (this->y()) / parameters["sizeHeight"].toInt()) * parameters["sizeHeight"].toInt()), this->data(BombermanTypes::Username).toString(), damage);

    if(timerFlicker->isActive())
    {
        if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
        {

        }
        else
            timerFlicker->stop();
    }
}

void Bomberman::slotTimerRestart()
{

}

void Bomberman::getInstallBomb(QGraphicsItem *item)
{
    inBomb = item;
}

void Bomberman::changeDirection(const BombermanTypes::DirectionEnum direct)
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
        texture->load(QApplication::applicationDirPath() + textures[idType]["up"]["path"]);
        countFrames = textures[idType]["up"]["count"].toInt();
    }
    else
        if(direct == BombermanTypes::Down)
        {
            texture->load(QApplication::applicationDirPath() + textures[idType]["down"]["path"]);
            countFrames = textures[idType]["down"]["count"].toInt();
        }
    else
            if(direct == BombermanTypes::Right)
            {
                texture->load(QApplication::applicationDirPath() + textures[idType]["right"]["path"]);
                countFrames = textures[idType]["right"]["count"].toInt();
            }
    else
                if(direct == BombermanTypes::Left)
                {
                    texture->load(QApplication::applicationDirPath() + textures[idType]["left"]["path"]);
                    countFrames = textures[idType]["left"]["count"].toInt();
                }
#if LOGCHANGEDIRECTION == true
    qDebug(logDebug()) << "Bomberman change direction" << direction << "-" << direct << "(name:" << username << ")";
#endif

    direction = direct;
    currentFrameX = 0;
    slotTimerFlicker();
    timerFlicker->start(parameters["timeoutUpdatePicture"].toInt());
}

void Bomberman::readXmlConfig()
{
    QFile file(QApplication::applicationDirPath() + "/config/bomberman.xml");

    if(file.open(QFile::ReadOnly | QFile::Text))
        qDebug(logDebug()) << "Xml file is open:" << file.fileName();
    else
        qCritical(logCritical()) << "Xml file error" << file.errorString();

    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();

    while(xmlReader.readNextStartElement())
    {
        if(xmlReader.name() == "bomberman")
        {
            while(xmlReader.readNextStartElement())
            {
                if(xmlReader.name() == "model")
                {
                    int tmpId = xmlReader.attributes().value("id").toInt();
                    while(xmlReader.readNextStartElement())
                    {
                        textures[tmpId][xmlReader.name().toString()]["count"] = xmlReader.attributes().value("count").toString();
                        textures[tmpId][xmlReader.name().toString()]["path"] = xmlReader.readElementText();
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

QRectF Bomberman::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void Bomberman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-16, -16, *texture, currentFrameX, 0, sizeCellWidth, sizeCellHeight);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
