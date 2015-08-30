#include "dataTypes.h"

#include "MathDataTypes.h"
#include "Math.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// import Josh's Maths Librarys

int main();
image * loadImageFromFile(std::string fileName); // must be a height map
image * generateBumpMap(image * originalHeightMap, float bumpAmplertude);
float zVal(px24Bit a);
px24Bit encodeUnitVectorAs24BitPixel(Vector3D vec);
std::string outputFileName(std::string originalFileName);
void writeImageToFile(image * toWrite, BmpStartingBitAllInOne startingHeader, std::string outFileName);
BmpStartingBitAllInOne getFileInto(std::string fileName);
std::vector<std::vector<px24Bit>> convertTo2dVector(image * toConv);
px24Bit get24BitPxAt(int rowsDown, int columnsAccross, image * imageMap);

int main()
{
	std::cout << "Welcome to Josh's bump map generator" << std::endl;
	std::string file;
	std::cout << "File name with extention: ";
	
	std::cin >> file;

	image * original;
	original = loadImageFromFile(file);

	if (original == nullptr)
	{
		return 1;
	}

	BmpStartingBitAllInOne header = getFileInto(file);

	image * bumpMap;

	float bumpAmplertude;
	std::cout << "bump amplertude (float): ";
	std::cin >> bumpAmplertude;

	bumpMap = generateBumpMap(original, bumpAmplertude);
	std::string outFileName = outputFileName(file);

	writeImageToFile(bumpMap, header, outFileName); 

	std::cout << "Done: ";
	delete original;
	delete bumpMap;
	char e;
	std::cin >> e;

	return 0;
}

image * loadImageFromFile(std::string fileName)
{
	image * rv;
	std::ifstream readInFile(fileName, std::ios::binary);
	if (!readInFile.good())
	{
		return nullptr;
	}
	BmpMagicNumber magic;
	BmpMk5FileHeader header;
	BmpInfoHeader info;
	readInFile.read(reinterpret_cast<char *>(&magic), sizeof(BmpMagicNumber));
	readInFile.read(reinterpret_cast<char *>(&header), sizeof(BmpMk5FileHeader));
	readInFile.read(reinterpret_cast<char *>(&info), sizeof(BmpInfoHeader));
	// if its got 32 bit data will return null ptr
	if (info.bitsPerPixel != 24)
	{
		return nullptr;
	}
	rv = new image();
	rv->bitsPerPixel = info.bitsPerPixel;
	rv->nColumns = info.width;
	rv->nRows = info.height;
	rv->imageData = new unsigned char[(rv->bitsPerPixel / 8) * rv->nColumns * rv->nRows];
	readInFile.read(reinterpret_cast<char *>(rv->imageData), (rv->bitsPerPixel / 8)* rv->nColumns * rv->nRows);
	readInFile.close();
	return rv;
}

image * generateBumpMap(image * originalHeightMap, float bumpAmplertude)
{
	if (originalHeightMap->bitsPerPixel != 24)
	{
		return nullptr;
	}
	std::vector<std::vector<px24Bit>> converted;

	
	for (int i = 0; i < originalHeightMap->nRows; i++)
	{
		std::vector<px24Bit> tmpRow;
		tmpRow.clear();
		for (int j = 0; j < originalHeightMap->nColumns; j++)
		{
			px24Bit tmp = get24BitPxAt(i, j, originalHeightMap);
			tmpRow.push_back(tmp);
		}
		converted.push_back(tmpRow);
		tmpRow.clear();
	}

	std::vector<std::vector<px24Bit>> bumpMapVectorForm;
	for (int i = 0; i < originalHeightMap->nRows; i++)
	{
		std::vector<px24Bit> tmpRow;
		tmpRow.clear();
		for (int i = 0; i < originalHeightMap->nColumns; i++)
		{
			px24Bit tmpPx;
			tmpPx = px24Bit::white();
			tmpRow.push_back(tmpPx);
		}
		bumpMapVectorForm.push_back(tmpRow);
		tmpRow.clear();
	}

	
	float aspectRatio = originalHeightMap->nRows / originalHeightMap->nColumns;

	for (int i = 0; i < originalHeightMap->nRows; i++)
	{
		for (int j = 0; j < originalHeightMap->nColumns; j++)
		{
			
			
			float heightLeftPx;
			float heightRightPx;
			float heightUpPx;
			float heightDownPx;
			

			if (j == 0)
			{
				heightLeftPx = 0.0f;
			}
			else
			{
				heightLeftPx = zVal(converted[i][j-1]);
			}
			
			if (j == originalHeightMap->nColumns - 1)
			{
				heightRightPx = 0.0f;
			}
			else
			{
				heightRightPx = zVal(converted[i][j+1]);
			}
			
			if (i == 0)
			{
				heightUpPx = 0.0f;
			}
			else
			{
				heightUpPx = zVal(converted[i-1][j]);
			}
			
			
			if (i == originalHeightMap->nRows - 1)
			{
				heightDownPx = 0.0f;
			}
			else
			{
				heightDownPx = zVal(converted[i+1][j]);
			}		
			
			


			Vector3D s, t;
			s.x = 1.0f;
			s.y = 0.0f;
			// s.z equasion here
			s.z = bumpAmplertude * heightRightPx - bumpAmplertude * heightLeftPx;


			t.x = 0.0f;
			t.y = 1.0f;
			// t.z equasion here
			t.z = bumpAmplertude * heightUpPx - bumpAmplertude * heightDownPx;

			Vector3D sCrossT = Math::VectorMath::crossProduct(s, t);
			sCrossT = Math::VectorMath::unitVector(sCrossT);

			// now to encode the unit vector as a 24 bit pixel
			// float (0 to 1) to uchar (0 to 255)
			px24Bit bumpMapVal;
			bumpMapVal = encodeUnitVectorAs24BitPixel(sCrossT);
			bumpMapVectorForm[i][j] = bumpMapVal;
		}
	}

	// convert back to right form then return the value
	std::vector<px24Bit> bumpmap1DVectorForm;
	for (int i = 0; i < bumpMapVectorForm.size(); i++)
	{
		for (int j = 0; j < bumpMapVectorForm[i].size(); j++)
		{
			bumpmap1DVectorForm.push_back(bumpMapVectorForm[i][j]);
		}
	}

	image * rv;
	rv = new image();

	rv->bitsPerPixel = originalHeightMap->bitsPerPixel;
	rv->nRows = originalHeightMap->nRows;
	rv->nColumns = originalHeightMap->nColumns;
	rv->imageData = new unsigned char[(rv->bitsPerPixel / 8) * rv->nRows * rv->nColumns];

	for (int i = 0; i < bumpmap1DVectorForm.size(); i++)
	{
		int posInImageData = i * 3;
		rv->imageData[posInImageData] = bumpmap1DVectorForm[i].b;
		rv->imageData[posInImageData + 1] = bumpmap1DVectorForm[i].g;
		rv->imageData[posInImageData + 2] = bumpmap1DVectorForm[i].r;
	}

	
	return rv;
}

float zVal(px24Bit a)
{
	float rv = 0.0f;
	int max = 255 * 3;
	float scale = 1.0f / static_cast<float>(max);
	rv += static_cast<float>(a.b) * scale;
	rv += static_cast<float>(a.g) * scale;
	rv += static_cast<float>(a.r) * scale;
	return rv;
}

px24Bit encodeUnitVectorAs24BitPixel(Vector3D vec)
{
	float rF, gF, bF;
	rF = (vec.x + 1.0f) / 2.0f;
	gF = (vec.y + 1.0f) / 2.0f;
	bF = (vec.z + 1.0f) / 2.0f;

	// now to convert to range 0-255
	float finRedComponent, finGreenComponent, finBlueComponent;
	finRedComponent = rF * 255.0f;
	finGreenComponent = gF * 255.0f;
	finBlueComponent = bF * 255.0f;

	px24Bit rv;
	rv.r = static_cast<unsigned char>(finRedComponent);
	rv.g = static_cast<unsigned char>(finGreenComponent);
	rv.b = static_cast<unsigned char>(finBlueComponent);
	return rv;
}

std::string outputFileName(std::string originalFileName)
{
	int startOfExtention = originalFileName.find_last_of(".");
	std::string fileNameSubExt = originalFileName.substr(0, startOfExtention);
	std::string ext = originalFileName.substr(startOfExtention, originalFileName.size() - 1);
	std::string bumpMap = "_bumpMap";
	fileNameSubExt.append(bumpMap);
	fileNameSubExt.append(ext);
	return fileNameSubExt;
}

BmpStartingBitAllInOne getFileInto(std::string fileName)
{
	std::ifstream theFile(fileName.c_str(), std::ios::binary);
	if (!theFile.good())
	{
		return BmpStartingBitAllInOne();
	}
	BmpStartingBitAllInOne rv;
	theFile.read(reinterpret_cast<char *>(&rv.magic), sizeof(BmpMagicNumber));
	theFile.read(reinterpret_cast<char *>(&rv.head), sizeof(BmpMk5FileHeader));
	theFile.read(reinterpret_cast<char *>(&rv.info), sizeof(BmpInfoHeader));
	theFile.close();
	return rv;
}

void writeImageToFile(image * toWrite, BmpStartingBitAllInOne startingHeader, std::string outFileName)
{
	std::ofstream output(outFileName, std::ios::binary);
	output.write(reinterpret_cast<char *>(&startingHeader.magic), sizeof(BmpMagicNumber));
	output.write(reinterpret_cast<char *>(&startingHeader.head), sizeof(BmpMk5FileHeader));
	output.write(reinterpret_cast<char *>(&startingHeader.info), sizeof(BmpInfoHeader));

	// write the data
	output.write(reinterpret_cast<char *>(toWrite->imageData), (toWrite->bitsPerPixel / 8) * toWrite->nColumns * toWrite->nColumns);
	output.close();
}

std::vector<std::vector<px24Bit>> convertTo2dVector(image * toConv)
{
	std::vector<std::vector<px24Bit>> rv;
	rv.clear();
	for (int i = 0; i < toConv->nRows; i++)
	{
		std::vector<px24Bit> tmpRow;
		tmpRow.clear();
		int offset = i * toConv->nColumns;
		for (int j = 0; j < toConv->nColumns; j++)
		{
			int columnOffset = j * 3;
			px24Bit tmp;
			tmp.b = toConv->imageData[offset + columnOffset];
			tmp.g = toConv->imageData[offset + columnOffset + 1];
			tmp.r = toConv->imageData[offset + columnOffset + 2];
			tmpRow.push_back(tmp);
		}
		rv.push_back(tmpRow);
	}
	return rv;
}

px24Bit get24BitPxAt(int rowsDown, int columnsAccross, image * imageMap)
{
	px24Bit rv = px24Bit::black();

	if (imageMap->bitsPerPixel != 24)
	{
		return rv;
	}

	if (rowsDown > imageMap->nRows)
	{
		return rv;
	}

	if (columnsAccross > imageMap->nColumns)
	{
		return rv;
	}

	// it's work able

	int offsetToRow = rowsDown * (imageMap->nColumns * (imageMap->bitsPerPixel / 8));
	int columnOffset = columnsAccross * (imageMap->bitsPerPixel / 8);
	int readPos = offsetToRow + columnOffset;
	rv.b = imageMap->imageData[readPos];
	rv.g = imageMap->imageData[readPos + 1];
	rv.r = imageMap->imageData[readPos + 2];
	return rv;
}