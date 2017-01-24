#include "Bomb.h"
#include "Enemy/EnemyNFS.h"
#include "BombermanWidget.h"
#include "ui_BombermanWidget.h"

#include <ctime>

BombermanWidget::BombermanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BombermanWidget)
{
    ui->setupUi(this);

    srand(time(0));

    this->resize(994, 674);
//    this->setFixedSize(992, 672);

    countCols = 31;
    countRows = 21;
    sizeCellWidth = 32;
    sizeCellHeight = 32;

    map.resize(countRows);
    for(int i = 0; i < countRows; i++)
    {
        map[i].resize(countCols);
        map[i].fill(BombermanTypes::None);
    }

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0, 0, 992, 672);

    generateStoneNoDestroy();
    generateStoneDestroy();
    generateEnemy();
    paintMap();

    Bomberman *bomberman = new Bomberman("username1", 0);
    connect(bomberman, &Bomberman::setBomb, this, &BombermanWidget::slotSetBomb);
    connect(this, &BombermanWidget::sendInstallBomb, bomberman, &Bomberman::getInstallBomb);
    bomberman->setPos(48, 80);
    scene->addItem(bomberman);

//    EnemyNFS *enemy = new EnemyNFS(QPointF(64, 32), "codin");
//    scene->addItem(enemy);

}

BombermanWidget::~BombermanWidget()
{
    qDebug(logDebug()) << "Game finish";
    delete ui;
}

void BombermanWidget::slotSetBomb(QPointF position, QString username, int damage)
{
    int intX = (int (position.x()) / 32) * 32;
    int intY = (int (position.y()) / 32) * 32;
    int row = intY / 32;
    int col = intX / 32;

    if(map[row][col] == BombermanTypes::Bomb)
        return;

    map[row][col] = BombermanTypes::Bomb;
    Bomb *bomb = new Bomb(QPointF(intX, intY), damage);
    connect(bomb, &Bomb::bombDestroyed, this, &BombermanWidget::slotBombDestroyes);
    bomb->setData(BombermanTypes::Username, username);
    scene->addItem(bomb);

    emit  sendInstallBomb(bomb);
}

void BombermanWidget::slotBombDestroyes(QPointF position)
{
    int row = position.y() / 32;
    int col = position.x() / 32;

    map[row][col] = BombermanTypes::None;
}

void BombermanWidget::generateStoneNoDestroy()
{
    for(int i = 0; i < countCols; i++)
    {
        map[0][i] = BombermanTypes::StoneNoDestroy;
        map[countRows - 1][i] = BombermanTypes::StoneNoDestroy;
    }
    for(int i = 1; i < countRows - 1; i++)
    {
        map[i][0] = BombermanTypes::StoneNoDestroy;
        map[i][countCols - 1] = BombermanTypes::StoneNoDestroy;
    }

    for(int row = 1; row < countRows; row++)
        for(int col = 1; col < countCols; col++)
            if(row % 2 == 0 && col % 2 == 0)
                map[row][col] = BombermanTypes::StoneNoDestroy;

    map[1][1] = BombermanTypes::BookPlace;
    map[2][1] = BombermanTypes::BookPlace;
    map[1][2] = BombermanTypes::BookPlace;

    map[countRows - 2][1] = BombermanTypes::BookPlace;
    map[countRows - 3][1] = BombermanTypes::BookPlace;
    map[countRows - 2][2] = BombermanTypes::BookPlace;
}

void BombermanWidget::generateStoneDestroy()
{
    for(int row = 1; row < countRows; row++)
        for(int col = 1; col < countCols; col++)
            if(map[row][col] == BombermanTypes::None && (rand() % 5 == 0 || rand() % 5 == 0))
//            if(map[row][col] == BombermanTypes::None)
                map[row][col] = BombermanTypes::StoneDestroy;
}

void BombermanWidget::generateEnemy()
{
    parameters["countEnemy"] = "4";
    int countEnemy = 0;
    while(countEnemy <= parameters["countEnemy"].toInt())
    {
        int row = 1 + rand() % (countRows - 2);
        int col = 1 + rand() % (countCols - 2);

        if(map[row][col] != BombermanTypes::None)
            continue;

        map[row][col] = BombermanTypes::EnemyObject;
        countEnemy++;
    }
}

void BombermanWidget::paintMap()
{
    for(int row = 0; row < countRows; row++)
        for(int col = 0; col < countCols; col++)
        {
            if(map[row][col] == BombermanTypes::StoneNoDestroy)
            {
                StoneNoDestroy *stoneNoDestroy = new StoneNoDestroy(QPointF(sizeCellWidth * col, sizeCellHeight * row));
                scene->addItem(stoneNoDestroy);
            }
            if(map[row][col] == BombermanTypes::StoneDestroy)
            {
                StoneDestroy *stoneDestroy = new StoneDestroy(QPointF(sizeCellWidth * col, sizeCellHeight * row));
                scene->addItem(stoneDestroy);
            }
            if(map[row][col] == BombermanTypes::EnemyObject)
            {
                EnemyNFS *enemy = new EnemyNFS(QPointF(sizeCellWidth * col, sizeCellHeight * row), "coin");
                scene->addItem(enemy);
            }
        }
}
