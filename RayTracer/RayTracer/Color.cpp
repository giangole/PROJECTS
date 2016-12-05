#include "Color.h"
	Color::Color()
	{
		red = 0.5;
		green = 0.5;
		blue = 0.5;
	}
	Color::Color(double r, double g, double b, double s) : red(r), green(g), blue(b), special(s){}
		Color::~Color()
	{
	}
	double Color::GetRed(){return red; }
	double Color::GetGreen(){ return green; }
	double Color::GetBlue(){ return blue; }
	double Color::GetSpecial(){ return special; }

	void Color::SetRed(double Rvalue){ red = Rvalue; }
	void Color::SetGreen(double Gvalue){ green = Gvalue; }
	void Color::SetBlue(double Bvalue){ blue = Bvalue; }
	void Color::SetSpecial(double Svalue){ special = Svalue; }


	double Color::Brightness()
	{
		return (red + green + blue) / 3;
	}
	Color Color::ColorScalar(double scalar)
	{
		return Color(red*scalar, green*scalar, blue*scalar, special);
	}
	Color Color::ColorAdd(Color color)
	{
		return Color(red + color.GetRed(), green + color.GetGreen(), blue + color.GetBlue(), special);
	}
	Color Color::ColorMultiply(Color color)
	{
		return Color(red * color.GetRed(), green *color.GetGreen(), blue * color.GetBlue(), special);
	}
	Color Color::ColorAvarage(Color color)
	{
	
		return Color((red + color.GetRed()) / 2, (green + color.GetGreen()) / 2, (blue + color.GetBlue()) / 2, special);
	}
	Color Color::clip() {
		double AllLight = red + green + blue;
		double excesslight = AllLight - 3;
		if (excesslight > 0) 
		{
			red = red + excesslight *(red / AllLight);
			green = green + excesslight *(green / AllLight);
			blue = blue + excesslight *(blue / AllLight);
		}
		if (red > 1) {red = 1;}
		if (green > 1) { green = 1;}
		if (blue > 1) { blue = 1;}

		if (red < 0) { red = 0;}
		if (green < 0) { green = 0;}
		if (blue < 0) { blue = 0;}
		return Color (red, green, blue, special);
		}