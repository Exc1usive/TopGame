#ifndef BOMBERMANWIDGET_H
#define BOMBERMANWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>

#include "BombermanTypes.h"
#include "Bomberman.h"
#include "StoneDestroy.h"
#include "StoneNoDestroy.h"

namespace Ui {
class BombermanWidget;
}

class BombermanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BombermanWidget(QWidget *parent = 0);
    ~BombermanWidget();

private slots:
    void slotSetBomb(QPointF position, QString username, int damage);

private:
    Ui::BombermanWidget *ui;

    QGraphicsScene *scene;          // Graphics Scene
    int countRows = 0;              // Count Rows Game Field
    int countCols = 0;              // Count Columns Game Field
    int sizeCellWidth = 32;         // Width Cell Game Field
    int sizeCellHeight = 32;        // Height Cell Game Field

    QVector <QVector <int> > map;

    void generateStoneNoDestroy();
    void generateStoneDestroy();
    void paintMap();
};

#endif // BOMBERMANWIDGET_H
