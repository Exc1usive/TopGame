#ifndef EXPLOSIONHORIZONTAL_H
#define EXPLOSIONHORIZONTAL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class ExplosionHorizontal : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit ExplosionHorizontal(QPointF position, QObject *parent = 0);
    ~ExplosionHorizontal();

    bool checkCollision();

signals:

public slots:

private slots:
    void slotTimerFlicker();

private:
    QPixmap *texture;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 0;

    QTimer *timerFlicker;

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EXPLOSIONHORIZONTAL_H