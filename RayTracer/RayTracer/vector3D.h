#ifndef _VECTOR3D_H
#define _VECTOR3D_H
#include "math.h"
class vector3D
{
	double x;
	double y;
	double z;
public:
	vector3D();
	vector3D(double x, double y, double z);
	~vector3D();
	double GetX();
	double GetY();
	double GetZ();
	vector3D Normalize();
	double Lenght(); //also called "Magnitude"
	vector3D Negate();
	double DotProduct(vector3D v);
	vector3D CrossProduct(vector3D v);
	vector3D Add(vector3D v);
	vector3D Multiply(double scalar);
};
#endif 