#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    sceneBorders = QRect(0, 0, 600, 600);
    layout = new QGridLayout(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(sceneBorders);
    view = new QGraphicsView(this);
    view->setScene(scene);

    layout->addWidget(view, 0, 0);

    manager = new ItemManager();
    manager->setBorders(sceneBorders);
    setupEnviroment();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEnviroment()));
    timer->start(100);
}

void MainWindow::setupEnviroment()
{
    // Scene border items
    int offset = 50;
    ArcItem* i = new ArcItem();
    i->setSize(offset, sceneBorders.height());
    i->setPos(-offset, 0);
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setSize(offset, sceneBorders.height());
    i->setPos(sceneBorders.width(), 0);
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setSize(sceneBorders.width(), offset);
    i->setPos(0, -offset);
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setSize(sceneBorders.width(), offset);
    i->setPos(0, sceneBorders.height());
    scene->addItem(i);
    manager->addActor(i);




    i = new ArcItem();
    i->setPos(100, 100);
    i->setSize(20, 20);
    i->setKinematic(true);
    i->setName("First ball");
    i->setSpeed(QPoint(3, 8));
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setPos(250, 180);
    i->setSize(30, 30);
    i->setKinematic(true);
    i->setName("Second ball");
    i->setSpeed(QPoint(-5, 1));
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setPos(100, 200);
    i->setSize(100, 30);
    i->setName("First rect");
    i->setSpeed(QPoint(0, 0));
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setPos(100, 300);
    i->setSize(100, 30);
    i->setName("Second rect");
    i->setSpeed(QPoint(0, 0));
    scene->addItem(i);
    manager->addActor(i);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
}

void MainWindow::updateEnviroment()
{
    manager->checkCollisions();
    manager->advance();
    scene->update(scene->sceneRect());
}

