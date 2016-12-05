#include "Ray.h"
#include "vector3D.h"
Ray::Ray()
{
	Origin = vector3D(0, 0, 0);
	Direction = vector3D (1, 0, 0);
	
}
Ray::Ray(vector3D x, vector3D y) : Origin(x), Direction(y){}
Ray::~Ray(){}
vector3D Ray::GetOrigin(){ return Origin; }
vector3D Ray::GetDirection(){ return Direction; }