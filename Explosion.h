#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class Explosion : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Explosion(QPointF position, QObject *parent = 0);
    ~Explosion();

signals:

public slots:
};

#endif // EXPLOSION_H
