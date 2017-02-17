#ifndef EXPLOSIONUPFINISH_H
#define EXPLOSIONUPFINISH_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <windows.h>

#include "BombermanTypes.h"

class ExplosionUpFinish : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit ExplosionUpFinish(QPointF position, QObject *parent = 0);
    ~ExplosionUpFinish();

    bool checkCollision();

signals:

public slots:

private slots:
    void slotTimerFlicker();

private:
    QPixmap *texture;

    QMap<QString, QString> textures;
    QMap <QString, QString> parameters;

    int sizeCellWidth = 0;
    int sizeCellHeight = 0;

    int currentFrameX = 0;
    int countFrames = 0;

    QTimer *timerFlicker;

    void readXmlConfig();    // Считывает конфиг с xml файлаa

    // QGraphicsItem interface
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EXPLOSIONUPFINISH_H
