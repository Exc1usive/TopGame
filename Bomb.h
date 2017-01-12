#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class Bomb : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Bomb(QPointF position, QObject *parent = 0);
    ~Bomb();

    void destroy();

signals:

public slots:

private slots:
    void slotTimerFlicker();
    void slotTimerDestroy();

private:
    QPixmap *texture;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 0;

    Qt::GlobalColor color = Qt::black;

    QTimer *timerFlicker;
    QTimer *timerDestroy;

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMB_H
