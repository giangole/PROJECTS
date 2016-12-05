#ifndef _SPHERE_H
#define _SPHERE_H
#include "Shape.h"
#include "math.h"
#include "Color.h"
#include "vector3D.h"
class Sphere : public Shape 
{
	vector3D Centre;
	double Radius;
	Color color;
public:
	Sphere();
	Sphere(vector3D v,double d, Color c);
	~Sphere();
	vector3D GetCentre();
	double GetRadius();
	Color GetColor();
	double GetIntersections(Ray ray); //find intersections between a sphere and a ray, this returns a scalar value not a vector (point!)
	vector3D GetNormalAt(vector3D point); // get the normal at the point for example (the scalar of intersections) and the Center of the Sphere (vector3D)
	double Sphere::findIntersection(Ray ray);
};
#endif 