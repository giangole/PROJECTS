#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

class BMP
{
public :
	struct RGB 
	{
		double r[1];
		double g[1];
		double b[1];
		RGB() : r(), g(),b(){}

	};
	int w;
	int h;
	int dpi;
	const char*filename;
	BMP();
	BMP(const char *filename, int w, int h, int dpi, BMP::RGB *xcolor);
	~BMP();
	void saveBMP();
	RGB *color;
	RGB *getRGB();

};
	
