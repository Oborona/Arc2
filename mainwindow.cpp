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
//    manager->setBorders(sceneBorders);
    setupEnviroment();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEnviroment()));
    timer->start(50*TIME_LATENCY);
}

void MainWindow::setupEnviroment()
{
    // Scene border items
    int offset = 50;
    ArcItem* i = new ArcItem();
    i->setName("Left border");
    i->setSize(offset, sceneBorders.height());
    i->setPos(10, 0);
    i->addSetting("Indestructible");
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setName("Right border");
    i->setSize(offset, sceneBorders.height());
    i->setPos(sceneBorders.width()-200, 0);
    i->addSetting("Indestructible");
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setName("Top border");
    i->setSize(sceneBorders.width(), offset);
    i->setPos(0, 40-offset);
    i->addSetting("Indestructible");
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setName("Bottom border");
    i->setSize(sceneBorders.width(), offset);
    i->setPos(0, sceneBorders.height()-300);
    i->addSetting("Indestructible");
    scene->addItem(i);
    manager->addActor(i);


    i = new ArcItem();
    i->setPos(100, 80);
    i->setSize(20, 20);
    i->setName("First ball");
    i->setSpeed(QPoint(3*TIME_LATENCY, 8*TIME_LATENCY));
    i->addSetting("Kinematic");
    scene->addItem(i);
    manager->addActor(i);

    i = new ArcItem();
    i->setPos(230, 170);
    i->setSize(20, 20);
    i->setName("Second ball");
    i->setSpeed(QPoint(8*TIME_LATENCY, -4*TIME_LATENCY));
    i->addSetting("Kinematic");
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
    i->setPos(200, 250);
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
    if (event->key() == Qt::Key_Space)
    {
        if (timer->isActive())
            timer->stop();
        else
            timer->start(50*TIME_LATENCY);
    }
    if (event->key() == Qt::Key_Enter)
    {
        scene->clear();
        setupEnviroment();
    }

}

void MainWindow::updateEnviroment()
{
//    manager->update();
    qDebug() << "Time:" << appTime++;
    manager->advance();
    scene->update(scene->sceneRect());
}

