#include "mapgeneratorwindow.h"
#include "ui_mapgeneratorwindow.h"

MapGeneratorWindow::MapGeneratorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapGeneratorWindow)
{
    ui->setupUi(this);
}

MapGeneratorWindow::~MapGeneratorWindow()
{
    delete ui;
}
