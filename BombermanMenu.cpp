#include "BombermanMenu.h"

#include <QDebug>

BombermanMenu::BombermanMenu(QObject *parent) : QObject(parent), QGraphicsItem()
{
    this->setZValue(10);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFocus();

    textureMenu = new QPixmap(":/menu/images/menu/Menu.png");
    textureMenuContinue = new QPixmap(":/menu/images/menu/MenuContinue.png");
    textureMenuContinueSelect = new QPixmap(":/menu/images/menu/MenuContinueSelect.png");
    textureMenuExit = new QPixmap(":/menu/images/menu/menuExit.png");
    textureMenuExitSelect = new QPixmap(":/menu/images/menu/menuExitSelect.png");
}

BombermanMenu::~BombermanMenu()
{
    delete textureMenu;
    delete textureMenuContinue;
    delete textureMenuContinueSelect;
    delete textureMenuExit;
    delete textureMenuExitSelect;
}

QRectF BombermanMenu::boundingRect() const
{
    return QRectF(0, 0, scene()->width(), scene()->height());
}

void BombermanMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *textureMenu, 0, 0, scene()->width(), scene()->height());

    if(currentButton != 1)
        painter->drawPixmap(397, 215, *textureMenuContinue, 0, 0, 244, 34);
    else
        painter->drawPixmap(397, 215, *textureMenuContinueSelect, 0, 0, 244, 34);

    if(currentButton != 2)
        painter->drawPixmap(456, 508, *textureMenuExit, 0, 0, 126, 34);
    else
        painter->drawPixmap(456, 508, *textureMenuExitSelect, 0, 0, 126, 34);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void BombermanMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        if(currentButton == 1)
            currentButton = 2;
        else
            currentButton--;
    }
    if(event->key() == Qt::Key_Down)
    {
        if(currentButton == 2)
            currentButton = 1;
        else
            currentButton++;
    }

    this->update();
}

void BombermanMenu::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
//        if(currentButton == 2)
//        {
//            this->deleteLater();
//            return;
//        }

        emit buttonClicked(currentButton);
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//  BombermanStartMenu
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

BombermanStartMenu::BombermanStartMenu(QObject *parent) : QObject(parent), QGraphicsItem()
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setFocus();

    textureMenu = new QPixmap(":/startMenu/images/startMenu/StartMenu.png");
    textureMenuGame = new QPixmap(":/startMenu/images/startMenu/Game.png");
    textureMenuGameSelect = new QPixmap(":/startMenu/images/startMenu/GameSelect.png");
    textureMenuGameInternet = new QPixmap(":/startMenu/images/startMenu/GameInternet.png");
    textureMenuGameInternetSelect = new QPixmap(":/startMenu/images/startMenu/GameInternetSelect.png");
    textureMenuExit = new QPixmap(":/startMenu/images/startMenu/Exit.png");
    textureMenuExitSelect = new QPixmap(":/startMenu/images/startMenu/ExitSelect.png");
}

BombermanStartMenu::~BombermanStartMenu()
{

}

QRectF BombermanStartMenu::boundingRect() const
{
    return QRectF(0, 0, scene()->width(), scene()->height());
}

void BombermanStartMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *textureMenu, 0, 0, scene()->width(), scene()->height());

    if(currentButton != 1)
        painter->drawPixmap(774, 210, *textureMenuGame, 0, 0, 122, 34);
    else
        painter->drawPixmap(774, 210, *textureMenuGameSelect, 0, 0, 122, 34);

    if(currentButton != 2)
        painter->drawPixmap(689, 251, *textureMenuGameInternet, 0, 0, 282, 34);
    else
        painter->drawPixmap(689, 251, *textureMenuGameInternetSelect, 0, 0, 282, 34);

    if(currentButton != 3)
        painter->drawPixmap(769, 373, *textureMenuExit, 0, 0, 124, 34);
    else
        painter->drawPixmap(769, 373, *textureMenuExitSelect, 0, 0, 124, 34);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void BombermanStartMenu::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        if(currentButton == 1)
            currentButton = 3;
        else
            currentButton--;
    }
    if(event->key() == Qt::Key_Down)
    {
        if(currentButton == 3)
            currentButton = 1;
        else
            currentButton++;
    }

    this->update();
}

void BombermanStartMenu::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        emit buttonClicked(currentButton);
    }
}
