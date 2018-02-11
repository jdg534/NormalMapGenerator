#ifndef MAPGENERATORWINDOW_H
#define MAPGENERATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class MapGeneratorWindow;
}

class MapGeneratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapGeneratorWindow(QWidget *parent = 0);
    ~MapGeneratorWindow();

	void init();

private:
	void onOpenMap();
	void onSaveOutputMap();
	void onGenerateMapButtonPressed();

	// validation methods
	bool validateInputs();
	bool validateInputMapCorrectForOutput();

	// actualy generation methods
	void generateEdgeMap(int sensitivity);
	void generateNormalMap(float amplertude);

	inline unsigned int difference(const QRgb a, const QRgb b);


    Ui::MapGeneratorWindow *ui;
};

#endif // MAPGENERATORWINDOW_H
