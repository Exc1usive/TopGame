#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPixmapCache>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class Bomberman : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Bomberman(QString _username, int _idType, QObject *parent = 0);
    ~Bomberman();
    
    void kill();
    void setStartPos(const QPointF pos);
    void setStartPos(const qreal posX, const qreal posY);

signals:
    void setBomb(QPointF _position, QString _username, int _damage);

public slots:
    void getInstallBomb(QGraphicsItem *item);

private slots:
    void slotTimerFlicker();
    void slotTimerGame();
    void slotTimerRestart();

private:
    QPixmap *texture;
    QPixmap *textureHeart;

    QMap <int, QMap<QString, QMap<QString, QString> > > textures;
    QMap <QString, QString> parameters;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 4;

    int idType;
    int speed = 4;
    int health = 3;

    bool checkInBomb = false;
    QGraphicsItem *inBomb = NULL;
    QGraphicsItem *inBomb2 = NULL;

    QTimer *timerFlicker;
    QTimer *timerGame;
    QTimer *timerRestart;

    QString username;
    int damage = 3;

    QPointF startPos;

    BombermanTypes::DirectionEnum direction = BombermanTypes::Stop;

    void changeDirection(const BombermanTypes::DirectionEnum direct);

    void readXmlConfig();    // Считывает конфиг с xml файла

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMBERMAN_H
