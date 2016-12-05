#include "vector3D.h"

vector3D::vector3D()
{
x = 0;
y = 0;
z = 0;
}
vector3D::vector3D(double xx, double xy, double xz) : x(xx), y(xy), z(xz){}
vector3D::~vector3D(){}

double vector3D::GetX(){ return x; }
double vector3D::GetY(){ return y; }
double vector3D:: GetZ(){ return z; }
//* 	Lenght = Magnitude return sqrt((x*x) + (y*y) + (z*z));*//
double vector3D::Lenght()
{
	return sqrt((x*x) + (y*y) + (z*z));
}


// normalize a vector aka the perpendicular vector of the given vector
//	double lenght = ((x*x) + (y*y) + (z*z));
//return vector3D(x / lenght, y / lenght, z / lenght);

vector3D vector3D::Normalize()
{
	double lenght = sqrt((x*x) + (y*y) + (z*z));
	return vector3D(x / lenght, y / lenght, z / lenght);
}

// inverses a vector: return vector3D (-x, -y, -z);
vector3D vector3D::Negate()
{
	return vector3D (-x, -y, -z);
}
// return: (x*v.GetX() + y*v.GetY() + z*v.GetZ()) (formula)
double vector3D::DotProduct(vector3D v)
{
	return (x*v.GetX() + y*v.GetY() + z*v.GetZ());
}
// cross product between 2 vectors
vector3D vector3D::CrossProduct(vector3D v)
{
	return vector3D(y*v.GetZ() - z*v.GetY(), z*v.GetX() - x*v.GetZ(), x*v.GetY()- y*v.GetX()); 
}
// add 2 vectors
vector3D vector3D::Add(vector3D v)
{
	return vector3D(x + v.GetX(), y + v.GetY(), z + v.GetZ());

}
//multiply  a vector to a scalar: return vector3D(x*scalar, y*scalar, z*scalar)
vector3D vector3D::Multiply(double scalar)
{
	return vector3D(x*scalar, y*scalar, z*scalar);
}