#include <QApplication>

#include "mainwindow.h"


int main(int ac, char** av)
{
//    // not modifying value
//    bool ok = false;
//    QPoint a1(40, 40);
//    QPoint a2( 0,  0);
//    QPoint b1(20,  0);
//    QPoint b2(20, 40);

//      QPoint a1(195,275);
//      QPoint a2(275,295);
//      QPoint b1(0, 285);
//      QPoint b2(600, 285);

//    QPoint a1(40, 40);
//    QPoint a2( 0,  0);
//    QPoint b1( 0, 20);
//    QPoint b2(40, 20);

//    exit(123);
    QApplication* app = new QApplication(ac, av);

    MainWindow* w = new MainWindow();
    w->move(100, 100);
    w->show();

    return app->exec();
}
