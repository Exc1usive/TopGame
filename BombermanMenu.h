#ifndef BOMBERMANMENU_H
#define BOMBERMANMENU_H

#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>

class BombermanMenu : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BombermanMenu(QObject *parent = 0);
    ~BombermanMenu();

signals:
    void buttonClicked(int index);

public slots:


private:
    QPixmap *textureMenu;
    QPixmap *textureMenuContinue;
    QPixmap *textureMenuContinueSelect;
    QPixmap *textureMenuExit;
    QPixmap *textureMenuExitSelect;

    int     currentButton = 1;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};

class BombermanStartMenu : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BombermanStartMenu(QObject *parent = 0);
    ~BombermanStartMenu();

protected:

public slots:

signals:
    void buttonClicked(int index);

private:
    QPixmap *textureMenu;
    QPixmap *textureMenuGame;
    QPixmap *textureMenuGameSelect;
    QPixmap *textureMenuGameInternet;
    QPixmap *textureMenuGameInternetSelect;
    QPixmap *textureMenuExit;
    QPixmap *textureMenuExitSelect;

    int     currentButton = 1;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // BOMBERMANMENU_H
