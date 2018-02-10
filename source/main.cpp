#include "mapgeneratorwindow.h"
#include <QApplication>

int main(int argCount, char ** args)
{
	QApplication app(argCount, args);

	MapGeneratorWindow mapGeneratorWindow;

	mapGeneratorWindow.init();

	mapGeneratorWindow.show();

	return app.exec();
}