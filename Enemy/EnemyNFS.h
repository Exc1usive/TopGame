#ifndef ENEMYNFS_H
#define ENEMYNFS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPixmapCache>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class EnemyNFS : public QObject
{
    Q_OBJECT
public:
    explicit EnemyNFS(QPointF position, QObject *parent = 0);
    ~EnemyNFS();

    void kill();

protected:
    QPixmap *texture;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 4;

    int speed = 4;

    QTimer *timerFlicker;
    QTimer *timerGame;

signals:

public slots:

private slots:
    void slotTimerFlicker();
    void slotTimerGame();

private:
    QPixmap *texture;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 4;

    int speed = 4;

    QTimer *timerFlicker;
    QTimer *timerGame;

    BombermanTypes::DirectionEnum direction = BombermanTypes::Stop;

    void changeDirection(const BombermanTypes::DirectionEnum direct);

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ENEMYNFS_H
