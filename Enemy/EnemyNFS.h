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
#include "Bomb.h"

class EnemyNFS : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit EnemyNFS(QPointF position, QObject *parent = 0);
    ~EnemyNFS();

    void kill();

protected:
    void readXmlConfig(QString tag);
    void setTexture(QString id, int _countFrames, QString path);

signals:

public slots:

private slots:
    void slotTimerFlicker();
    void slotTimerGame();

private:
    QPixmap *texture;

    QMap <QString, QMap<QString, QString> > textures;
    QMap <QString, QString> parameters;

    int currentFrameX = 0;
    int countFrames = 0;

    bool checkInBomb = false;
    QGraphicsItem *inBomb = NULL;

    QTimer *timerFlicker;
    QTimer *timerGame;

    BombermanTypes::DirectionEnum direction = BombermanTypes::Stop;

    void changeDirectionRandom(bool checkCurrent = false);
    void changeDirection(const BombermanTypes::DirectionEnum direct);
    void changeDirectionCollisionBomb();


    //    QGraphicsItem interface
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ENEMYNFS_H
