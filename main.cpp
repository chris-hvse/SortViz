#include <QApplication>
#include <QGraphicsScene>
#include "mainview.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGraphicsScene mainScene;
    MainView mainView(&mainScene);

    return app.exec();
}

