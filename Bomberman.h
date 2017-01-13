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
    explicit Bomberman(QObject *parent = 0);
    ~Bomberman();

signals:
    void setBomb();

public slots:

private slots:
    void slotTimerFlicker();
    void slotTimerGame();

private:
    QPixmap *texture;
    QPixmapCache *textures;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 4;

    int speed = 4;

    QTimer *timerFlicker;
    QTimer *timerGame;

    BombermanTypes::Direction direction = BombermanTypes::Stop;

    void changeDirection(const BombermanTypes::Direction direct);

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMBERMAN_H
