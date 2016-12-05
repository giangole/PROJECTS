#ifdef _WIN32 
#define _CRT_SECURE_NO_DEPRECATE 
#endif 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "bitmap.h"
BMP::BMP()
{	 w = 0;
	 h = 0;
	dpi = 0;
	filename = 0;
}
BMP::BMP(const char *xfilename, int xw, int xh, int xdpi, BMP::RGB *xcolor) : filename(xfilename), w(xw), h(xh), dpi(xdpi), color(xcolor)
{	
}
BMP::~BMP()
{
	delete color;
}

BMP::RGB *BMP::getRGB()
{	
	return color;
}
void BMP::saveBMP()
{
	FILE *f;

	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;
	double factor = 39.975;
	int m = static_cast <int>(factor);

	int ppm = dpi*m;

	unsigned char BMPfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char BMPinfoheader[40] {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24};

	BMPfileheader[2] = (unsigned char)(filesize);
	BMPfileheader[3] = (unsigned char)(filesize >> 8);
	BMPfileheader[4] = (unsigned char)(filesize >> 16);
	BMPfileheader[5] = (unsigned char)(filesize >> 24);

	BMPinfoheader[4] = (unsigned char)(w);
	BMPinfoheader[5] = (unsigned char)(w >> 8);
	BMPinfoheader[6] = (unsigned char)(w >> 16);
	BMPinfoheader[7] = (unsigned char)(w >> 24);

	BMPinfoheader[8] = (unsigned char)(h);
	BMPinfoheader[9] = (unsigned char)(h >> 8);
	BMPinfoheader[10] = (unsigned char)(h >> 16);
	BMPinfoheader[11] = (unsigned char)(h >> 24);

	BMPinfoheader[21] = (unsigned char)(s);
	BMPinfoheader[22] = (unsigned char)(s >> 8);
	BMPinfoheader[23] = (unsigned char)(s >> 16);
	BMPinfoheader[24] = (unsigned char)(s >> 24);

	BMPinfoheader[25] = (unsigned char)(ppm);
	BMPinfoheader[26] = (unsigned char)(ppm >> 8);
	BMPinfoheader[27] = (unsigned char)(ppm >> 16);
	BMPinfoheader[28] = (unsigned char)(ppm >> 24);

	BMPinfoheader[29] = (unsigned char)(ppm);
	BMPinfoheader[30] = (unsigned char)(ppm >> 8);
	BMPinfoheader[31] = (unsigned char)(ppm >> 16);
	BMPinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");
	fwrite(BMPfileheader, 1, 14, f);
	fwrite(BMPinfoheader, 1, 40, f);
	for (int i = 0; i < k; i++)
	{	//BMP::RGB rgb = color;

	double blue = (color->b[i]) * 255;
	double red = (color->r[i]) * 255;
	double green = (color->g[i]) * 255;
	unsigned char pixelcolor[3] = { (int)floor(blue), (int)floor(red), (int)floor(green) };
	fwrite(pixelcolor, 1, 3, f);
	}
	fclose(f);
	 }
