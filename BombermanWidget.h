#ifndef BOMBERMANWIDGET_H
#define BOMBERMANWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QKeyEvent>

#include "BombermanTypes.h"
#include "Bomberman.h"
#include "StoneDestroy.h"
#include "StoneNoDestroy.h"
#include "BombermanMenu.h"

namespace Ui {
class BombermanWidget;
}

class BombermanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BombermanWidget(QWidget *parent = 0);
    ~BombermanWidget();

signals:
    void sendInstallBomb(QGraphicsItem *item);

private slots:
    void slotSetBomb(QPointF position, QString username, int damage);
    void slotBombDestroyes(QPointF position);
    void slotStartMenuClick(int index);
    void slotMenuClick(int index);

private:
    Ui::BombermanWidget *ui;

    BombermanStartMenu *bombermanStartMenu;
    BombermanMenu *bombermanMenu;

    QMap <QString, QString> parameters;

    QGraphicsScene *scene;          // Graphics Scene
    int countRows = 0;              // Count Rows Game Field
    int countCols = 0;              // Count Columns Game Field
    int sizeCellWidth = 32;         // Width Cell Game Field
    int sizeCellHeight = 32;        // Height Cell Game Field

    QVector <QVector <int> > map;

    void generateStoneNoDestroy();
    void generateStoneDestroy();
    void generateEnemy();
    void paintMap();

    void showStartMenu();
    void showMenu();
    void startComputerGame();
    void startInternetGame();

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // BOMBERMANWIDGET_H
