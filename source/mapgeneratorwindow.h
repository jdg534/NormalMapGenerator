#ifndef MAPGENERATORWINDOW_H
#define MAPGENERATORWINDOW_H

#include <QMainWindow>

#include <JoshMath.h>

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

	// pick colour button press handlers
	void onEdgeMapPrimaryColour();
	void onEdgeMapEdgeColour();


	// validation methods
	bool validateInputs();
	bool validateInputMapCorrectForOutput();

	// generation methods
	void generateEdgeMap(int sensitivity);
	void generateNormalMap(float amplertude);

	inline unsigned int difference(const QRgb a, const QRgb b);
	inline float calcHeightMapPx(const QRgb in);
	inline QRgb vectorToPixel(const Vector3D & in);

    Ui::MapGeneratorWindow *ui;
};

#endif // MAPGENERATORWINDOW_H
