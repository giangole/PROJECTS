#include"Plane.h"

Plane::Plane()
{
	Normal = vector3D(1, 0, 0);
	Distance = 0;
	color = Color(0.5, 0.5, 0.5, 0);
}
Plane::Plane(vector3D normal, double distance, Color c) : Normal(normal), Distance(distance), color(c){}
Plane::~Plane(){}
vector3D Plane::GetNormal(){ return Normal; }
double Plane::GetDistance(){ return Distance; }
Color Plane::GetColor(){ return color; }


vector3D Plane::GetNormalAt (vector3D point){ return Normal; }
double Plane::findIntersection(Ray ray)

{ vector3D raydirection = ray.GetDirection();
double a = raydirection.DotProduct(Normal);
if (a == 0)
{
	//ray is parallel and no intersection is going to happen
	return -1;
}
else {
	// b is the dotproduct between the vector Normal (of the plane)  and the Ray (vector origin = starting point) 
	//added to the distance and then inverted 
	double b = Normal.DotProduct(ray.GetOrigin().Add(Normal.Multiply(Distance).Negate())); 
	//distance betweem te given ray and the point of intersection
	return -1 * b / a; 
}
}