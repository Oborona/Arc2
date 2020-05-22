#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QKeyEvent>

#include "arcitem.h"
#include "itemmanager.h"

// making refresh rate slowly and speed higher
#define TIME_LATENCY 1

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QRect sceneBorders;

    // For Debug
    int appTime = 0;

    QGridLayout* layout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QTimer* timer;
    QList<ArcItem*> items;

    ItemManager* manager;

    void setupEnviroment();
    void keyPressEvent(QKeyEvent* event);

signals:

public slots:
    void updateEnviroment();
};

#endif // MAINWINDOW_H
