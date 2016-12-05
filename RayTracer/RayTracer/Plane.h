#ifndef _PLANE_H
#define _PLANE_H
#include "Shape.h"
#include "math.h"
#include "Color.h"
#include "vector3D.h"
class Plane : public Shape
{
	vector3D Normal; //vector normal
	double Distance; //to the origin
	Color color;
public:
	Plane();
	Plane(vector3D normal, double distance, Color c);
	~Plane();
	vector3D GetNormal();
	double GetDistance();
	Color GetColor();
	vector3D GetNormalAt(vector3D point); //get normal vector at that point
	double findIntersection(Ray ray);
};
#endif 