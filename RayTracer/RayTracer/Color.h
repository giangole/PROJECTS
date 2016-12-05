#ifndef _COLOR_H
#define _COLOR_H
#include "math.h"
#include "vector3D.h"
class Color
{
	double red;
	double green;
	double blue;
	double special;
public:
	Color();
	Color(double r, double g, double b, double s);
	~Color();
	double GetRed();
	double GetGreen();
	double GetBlue();
	double GetSpecial();


	void SetRed(double Rvalue);
	void SetGreen(double Gvalue);
	void SetBlue(double Bvalue);
	void SetSpecial(double Svalue);
	double Color::Brightness();
	Color ColorScalar(double scalar);
	Color ColorAdd(Color color);
	Color ColorMultiply(Color color);
	Color ColorAvarage(Color color);
	Color clip();
};
#endif 