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
#include "Explosion.h"
#include "ExplosionHorizontal.h"
#include "ExplosionVertical.h"
#include "ExplosionDownFinish.h"
#include "ExplosionUpFinish.h"
#include "ExplosionLeftFinish.h"
#include "ExplosionRightFinish.h"

class Bomb : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Bomb(QPointF position, int size, QObject *parent = 0);
    ~Bomb();

    void destroy();

signals:
    void bombDestroyed(QPointF position);

public slots:

private slots:
    void slotTimerFlicker();
    void slotTimerDestroy();

private:
    QPixmap *texture;

    QMap<QString, QString> textures;
    QMap <QString, QString> parameters;

    int sizeCellWidth = 0;
    int sizeCellHeight = 0;

    int currentFrameX = 0;
    int countFrames = 0;
    int distanceDamage = 0;

//    Qt::GlobalColor color = Qt::black;

    QTimer *timerFlicker;
    QTimer *timerDestroy;

    void readXmlConfig();    // Считывает конфиг с xml файла

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMB_H
