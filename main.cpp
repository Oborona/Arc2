#include <QApplication>

#include "mainwindow.h"

//bool af(bool &a)
//{
//    return true;
//}

//void switchNum(int &a, int &b)
//{
//    int rem = a;
//    a = b;
//    b = rem;
//}

int main(int ac, char** av)
{
//    // not modifying value
    bool ok = false;
//    QPoint a1(40, 40);
//    QPoint a2( 0,  0);
//    QPoint b1(20,  0);
//    QPoint b2(20, 40);

      QPoint a1(20, 180);
      QPoint a2(-30, 180);
      QPoint b1(0, 0);
      QPoint b2(0, 600);

//    QPoint a1(40, 40);
//    QPoint a2( 0,  0);
//    QPoint b1( 0, 20);
//    QPoint b2(40, 20);
    qDebug() << "Points a1, a2:" << a1 << a2;
    qDebug() << "Points b1, b2:" << b1 << b2;
    qDebug() << "Result 1:" << linesCross(a1, a2, b1, b2, ok);
    qDebug() << "Result 2:" << linesCross(b1, b2, a1, a2, ok);
    qDebug() << ok;
    qDebug() << "===================================";


//    exit(123);
    QApplication* app = new QApplication(ac, av);

    MainWindow* w = new MainWindow();
    w->move(100, 100);
    w->show();

    return app->exec();
}
