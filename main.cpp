#include "BombermanWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BombermanWidget w;
    w.show();

    return a.exec();
}
