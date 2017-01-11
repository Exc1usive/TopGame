#include "BombermanWidget.h"
#include "ui_BombermanWidget.h"

BombermanWidget::BombermanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BombermanWidget)
{
    ui->setupUi(this);
}

BombermanWidget::~BombermanWidget()
{
    delete ui;
}
