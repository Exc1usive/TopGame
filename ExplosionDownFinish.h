#ifndef EXPLOSIONDOWNFINISH_H
#define EXPLOSIONDOWNFINISH_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class ExplosionDownFinish : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ExplosionDownFinish(QPointF position, QObject *parent = 0);
    ~ExplosionDownFinish();

    bool checkCollision();

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

#endif // EXPLOSIONDOWNFINISH_H
