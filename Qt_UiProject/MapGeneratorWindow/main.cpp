#include "mapgeneratorwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapGeneratorWindow w;
    w.show();

    return a.exec();
}
