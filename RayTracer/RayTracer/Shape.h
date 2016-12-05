#ifndef _SHAPE_H
#define _SHAPE_H
#include "math.h"
#include "Ray.h"
#include "Color.h"
#include "vector3D.h"
class Shape
{
public:
	Shape();
	virtual Color GetColor();
	virtual double GetIntersection(Ray ray);
	virtual double findIntersection(Ray ray);
	virtual vector3D GetNormalAt(vector3D Intersection);
};
#endif 