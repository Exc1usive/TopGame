#ifndef STONENODESTROY_H
#define STONENODESTROY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class StoneNoDestroy : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit StoneNoDestroy(QPointF position, QObject *parent = 0);
    ~StoneNoDestroy();

signals:

public slots:

private slots:

private:
    QPixmap *texture;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // STONENODESTROY_H
