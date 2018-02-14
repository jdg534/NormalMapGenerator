#include "mapgeneratorwindow.h"
#include "ui_mapgeneratorwindow.h"

#include <QFileDialog>
#include <QValidator>

MapGeneratorWindow::MapGeneratorWindow(QWidget *parent) 
	: QMainWindow(parent)
	, ui(new Ui::MapGeneratorWindow)
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
	QStringList inputMapTypes;
	inputMapTypes.push_back("Diffuse Map");
	inputMapTypes.push_back("Height Map");


	ui->comboBox_inputMapType->addItems(inputMapTypes);

	ui->comboBox_inputMapType->setCurrentIndex(0);

	QStringList outputMapTypes;
	outputMapTypes.push_back("Normal Map");
	outputMapTypes.push_back("Edge Map");

	ui->comboBox_outputMapType->addItems(outputMapTypes);
	ui->comboBox_outputMapType->setCurrentIndex(1);

	// connect ui object to correct methods
	connect(ui->actionSet_Input_Map, &QAction::triggered, this, &MapGeneratorWindow::onOpenMap);
	connect(ui->pushButton_generateMap, &QPushButton::pressed, this, &MapGeneratorWindow::onGenerateMapButtonPressed);
	connect(ui->actionSave_Output_Map, &QAction::triggered, this, &MapGeneratorWindow::onSaveOutputMap);

	// disable the generate button (gets re enabled once an input map is provided)
	ui->pushButton_generateMap->setDisabled(true);

	// add QValidator objects for the
	ui->lineEdit_bumpAmp->setValidator(new QDoubleValidator());
	ui->lineEdit_edgeMapSensivity->setValidator(new QIntValidator(0, 255 * 3));
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

	// enable the generate button
	ui->pushButton_generateMap->setDisabled(false);
}

void MapGeneratorWindow::onSaveOutputMap()
{
	// make sure that theres a map to save, if not return

	const QPixmap * outputImage = ui->label_outputMap->pixmap();

	if (outputImage)
	{
		QString saveFileStr = QFileDialog::getSaveFileName(this, tr("Save output"), "", tr("Images (*.png)"));
		if (saveFileStr != QString())
		{
			// save the file
			outputImage->save(saveFileStr, "png");
		}
	}
}

void MapGeneratorWindow::onGenerateMapButtonPressed()
{
	/* 
	1. check the input and output combo boxes are for the correct map type
	2. check that the map generation controls aren't values that will crash the program
	3. once validation has been passed call the correct generation method
	*/

	if (!validateInputs())
	{
		return;
	}

	// clear the output label pixel map
	QPixmap defaultMap(10, 10);
	ui->label_outputMap->setPixmap(defaultMap);

	if (ui->comboBox_outputMapType->currentText().toStdString() == "Normal Map")
	{
		float ampVal = 1.0f;
		if (ui->lineEdit_bumpAmp->text().toStdString() != "")
		{
			ampVal = ui->lineEdit_bumpAmp->text().toFloat();
		}
		generateNormalMap(ampVal);
	}
	else if (ui->comboBox_outputMapType->currentText().toStdString() == "Edge Map")
	{
		int sensitivityVal = 50;
		if (ui->lineEdit_edgeMapSensivity->text().toStdString() != "")
		{
			sensitivityVal = ui->lineEdit_edgeMapSensivity->text().toInt();
		}
		generateEdgeMap(sensitivityVal);
	}
}

bool MapGeneratorWindow::validateInputs()
{
	if (!validateInputMapCorrectForOutput())
	{
		return false;
	}

	// add additional validation here if needed
	
	return true;
}

bool MapGeneratorWindow::validateInputMapCorrectForOutput()
{
	// if diffuse map, then edge map
	// if height map, then normal map

	if (ui->comboBox_inputMapType->currentText().toStdString() == "Diffuse Map")
	{
		if (ui->comboBox_outputMapType->currentText().toStdString() == "Edge Map")
		{
			return true;
		}
	}
	else if (ui->comboBox_inputMapType->currentText().toStdString() == "Height Map")
	{

		if (ui->comboBox_outputMapType->currentText().toStdString() == "Normal Map")
		{
			return true;
		}
		else if (ui->comboBox_outputMapType->currentText().toStdString() == "Edge Map")
		{
			return true;
		}
	}

	return false;
}

void MapGeneratorWindow::generateEdgeMap(int sensitivity)
{
	// clear the current output map
	ui->label_outputMap->clear();

	const QPixmap * inputPixelMap = ui->label_inputMap->pixmap();
	
	const QImage originalImage = inputPixelMap->toImage();

	QImage generatedMap(originalImage);

	size_t originalImageWidth = originalImage.width(),
		originalImageHeight = originalImage.height();

	
	QRgb primaryColour = qRgb(0, 0, 0);
	QRgb edgeColour = qRgb(255, 255, 255);

	for (size_t i = 0; i < originalImageWidth; ++i)
	{
		for (size_t j = 0; j < originalImageHeight; ++j)
		{
			generatedMap.setPixelColor(i, j, primaryColour);
		}
	}

	
	// refactor to use the matrix approach later
	
	// now run the edge detection step
	
	// vertical scan
	for (size_t x = 0; x < originalImageWidth; ++x)
	{
		for (size_t y = 1; y < originalImageHeight; ++y)
		{
			// if it's an edge set the pixel to the edge colour
			const QRgb lastPx = originalImage.pixel(x, y - 1);
			const QRgb currentPx = originalImage.pixel(x, y);

			int diff = difference(lastPx, currentPx);

			if (diff > sensitivity)
			{
				generatedMap.setPixelColor(x, y, edgeColour);
			}
		}
	}

	// horisontal scan
	for (size_t y = 0; y < originalImageHeight; ++y)
	{
		for (size_t x = 1; x < originalImageWidth; ++x)
		{
			// if it's an edge set the pixel to the edge colour
			const QRgb lastPx = originalImage.pixel(x - 1, y);
			const QRgb currentPx = originalImage.pixel(x, y);

			int diff = difference(lastPx, currentPx);

			if (diff > sensitivity)
			{
				generatedMap.setPixelColor(x, y, edgeColour);
			}
		}
	}

	QPixmap outputPixelMap = QPixmap::fromImage(generatedMap);
	ui->label_outputMap->setPixmap(outputPixelMap);
}

void MapGeneratorWindow::generateNormalMap(float amplertude)
{
	const QPixmap * inputPixelMap = ui->label_inputMap->pixmap();

	const QImage originalImage = inputPixelMap->toImage();

	QImage generatedMap(originalImage);

	int originalImageWidth = originalImage.width(),
		originalImageHeight = originalImage.height();

	const float imageAspectRatio = (float)originalImageWidth / (float)originalImageHeight;


	float heightPxLeftOfCurrent = 0.0f;
	float heightPxRightOfCurrent = 0.0f;
	float heightPxUpOfCurrent = 0.0f;
	float heightPxDownOfCurrent = 0.0f;

	for (int pxPosX = 0; pxPosX < originalImageWidth; ++pxPosX)
	{
		for (int pxPosY = 0; pxPosY < originalImageHeight; ++pxPosY)
		{
			// 0 everything, the edges will assume 0.0
			float heightPxLeftOfCurrent = 0.0f;
			float heightPxRightOfCurrent = 0.0f;
			float heightPxUpOfCurrent = 0.0f;
			float heightPxDownOfCurrent = 0.0f;

			// px left
			if (pxPosX > 0)
			{
				heightPxLeftOfCurrent = calcHeightMapPx(originalImage.pixel(pxPosX - 1, pxPosY));
			}

			// px right
			if (pxPosX < originalImageWidth - 2)
			{
				heightPxRightOfCurrent = calcHeightMapPx(originalImage.pixel(pxPosX + 1, pxPosY));
			}

			// px up
			if (pxPosY > 0)
			{
				heightPxUpOfCurrent = calcHeightMapPx(originalImage.pixel(pxPosX, pxPosY - 1));
			}

			// px down
			if (pxPosY < originalImageHeight- 2)
			{
				heightPxRightOfCurrent = calcHeightMapPx(originalImage.pixel(pxPosX, pxPosY + 1));
			}

			Vector3D s, t;
			s.x = 1.0f;
			s.y = 0.0f;
			// s.z equasion here
			s.z = amplertude * heightPxRightOfCurrent - amplertude * heightPxLeftOfCurrent;


			t.x = 0.0f;
			t.y = 1.0f;
			// t.z equasion here
			t.z = amplertude * heightPxUpOfCurrent - amplertude * heightPxDownOfCurrent;

			Vector3D sCrossT = Math::VectorMath::crossProduct(s, t);
			sCrossT = Math::VectorMath::unitVector(sCrossT);


			QRgb valueToStore = vectorToPixel(sCrossT);
			
			generatedMap.setPixel(pxPosX, pxPosY, valueToStore);
		}
	}

	QPixmap outputPixelMap = QPixmap::fromImage(generatedMap);
	ui->label_outputMap->setPixmap(outputPixelMap);
}

inline unsigned int MapGeneratorWindow::difference(const QRgb a, const QRgb b)
{
	int aRed = qRed(a);
	int aGreen = qGreen(a);
	int aBlue = qBlue(a);

	int bRed = qRed(b);
	int bGreen = qGreen(b);
	int bBlue = qBlue(b);

	int diff = 0;
	diff += abs(aRed - bRed);
	diff += abs(aGreen - bGreen);
	diff += abs(aBlue- bBlue);
	return diff;
}

inline float MapGeneratorWindow::calcHeightMapPx(const QRgb in)
{
	float height = 0.0f;

	const int max = 255 * 3;
	float scale = 1.0f / static_cast<float>(max);

	height += static_cast<float>(qRed(in)) * scale;
	height += static_cast<float>(qGreen(in)) * scale;
	height += static_cast<float>(qBlue(in)) * scale;

	return height;
}

inline QRgb MapGeneratorWindow::vectorToPixel(const Vector3D & in)
{
	float rF, gF, bF;
	rF = (in.x + 1.0f) / 2.0f;
	gF = (in.y + 1.0f) / 2.0f;
	bF = (in.z + 1.0f) / 2.0f;

	// now to convert to range 0-255
	float finRedComponent, finGreenComponent, finBlueComponent;
	finRedComponent = rF * 255.0f;
	finGreenComponent = gF * 255.0f;
	finBlueComponent = bF * 255.0f;

	// store as int
	int intRedComp = static_cast<int>(finRedComponent);
	int intGreenComp = static_cast<int>(finGreenComponent);
	int intBlueComp = static_cast<int>(finBlueComponent);

	QRgb finalPx = qRgb(intRedComp, intGreenComp, intBlueComp);
	
	return finalPx;
}