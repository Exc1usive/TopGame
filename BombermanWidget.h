#ifndef BOMBERMANWIDGET_H
#define BOMBERMANWIDGET_H

#include <QWidget>

namespace Ui {
class BombermanWidget;
}

class BombermanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BombermanWidget(QWidget *parent = 0);
    ~BombermanWidget();

private:
    Ui::BombermanWidget *ui;
};

#endif // BOMBERMANWIDGET_H
