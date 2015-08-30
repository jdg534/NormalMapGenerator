#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#include <vector>

struct px24Bit
{
	unsigned char b,g,r;
	static px24Bit white()
	{
		px24Bit rv;
		rv.b = 255;
		rv.g = 255;
		rv.r = 255;
		return rv;
	}
	static px24Bit black()
	{
		px24Bit rv;
		rv.b = 0;
		rv.g = 0;
		rv.r = 0;
		return rv;
	}
};

struct px32Bit
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
	static px32Bit white()
	{
		px32Bit rv;
		rv.alpha = 255;
		rv.red = 255;
		rv.green = 255;
		rv.blue = 255;
		return rv;
	}
	static px32Bit black()
	{
		px32Bit rv;
		rv.alpha = 0;
		rv.red = 0;
		rv.green = 0;
		rv.blue = 0;
		return rv; 
	}
};

struct image
{
	// figure it out see slate2 form the .bmp loader
	unsigned int nRows;
	unsigned int nColumns;
	int bitsPerPixel;
	unsigned char * imageData;
	~image()
	{
		delete[] imageData;
	}
};

// bmp file stuff
struct BmpMagicNumber
{
	char magic[2]; // BM only, other values were for versions of windows before 3.1
};

struct BmpMk5FileHeader
{
	unsigned __int32 fileSize;
	unsigned __int16 creator1;
	unsigned __int16 creator2;
	unsigned __int32 bmpOffset; // offset to the actual image data
};

struct BmpInfoHeader
{
	unsigned __int32 headerSize;
	signed __int32 width;
	signed __int32 height;
	unsigned __int16 numberOfImagePlanes;
	unsigned __int16 bitsPerPixel;
	unsigned __int32 compressionType;
	unsigned __int32 sizeInBytes;
	signed __int32 imageWidth;
	signed __int32 imageHeight;
	unsigned __int32 numColours;
	unsigned __int32 numImportedColour;
};

struct BmpStartingBitAllInOne
{
	BmpMagicNumber magic;
	BmpMk5FileHeader head;
	BmpInfoHeader info;
};

enum BmpCompresionTypes
{
	BMP_RGB = 0,
	BMP_RLE8,
	BMP_RLE4,
	BMP_BITFIELDS,
	BMP_JPEG,
	BMP_PNG,
	BMP_ALPHABITFIELDS,
};




#endif