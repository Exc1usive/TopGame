#ifndef STONEDESTROY_H
#define STONEDESTROY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class StoneDestroy : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit StoneDestroy(QPointF position, QObject *parent = 0);
    ~StoneDestroy();

    void destroy();

signals:

public slots:

private slots:
    void slotTimerFlicker();

private:
    QPixmap *texture;

    QMap<QString, QString> textures;
    QMap <QString, QString> parameters;

    int sizeCellWidth = 32;
    int sizeCellHeight = 32;

    int currentFrameX = 0;
    int countFrames = 0;

    QTimer *timerFlicker;

    void readXmlConfig();    // Считывает конфиг с xml файла

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // STONEDESTROY_H
