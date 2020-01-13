#include <QApplication>

#include "mainwindow.h"

int main(int ac, char** av)
{
    QApplication* app = new QApplication(ac, av);

    MainWindow* w = new MainWindow();
    w->move(100, 100);
    w->show();

    return app->exec();
}
