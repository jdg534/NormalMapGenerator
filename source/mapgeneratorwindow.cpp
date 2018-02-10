#include "mapgeneratorwindow.h"
#include "ui_mapgeneratorwindow.h"

#include <QFileDialog>

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

void MapGeneratorWindow::init()
{
	// popupate the selectable input map combo box (this might be refactored out later)

	// connect the on load 
	connect(ui->actionSet_Input_Map, &QAction::triggered, this, &MapGeneratorWindow::onOpenMap);
}

void MapGeneratorWindow::onOpenMap()
{
	// just deal with image files
	QString inputFileName = QFileDialog::getOpenFileName(this, tr("Select an Image file"), QString(""), tr("Image files (*.bmp;*.jpg;*.png)"));

	if (inputFileName == QString())
	{
		// no file has been selected
		return;
	}

	QPixmap imagePixelMap(inputFileName);

	ui->label_inputMap->setPixmap(imagePixelMap);
}