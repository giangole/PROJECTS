#ifndef _RAY_H
#define _RAY_H

#include "vector3D.h"
class Ray
{
	vector3D Origin; // the starting point
	vector3D Direction; // the ending point
				 
public:
	Ray();
	Ray(vector3D x, vector3D y );
	~Ray();
	vector3D GetOrigin();
	vector3D GetDirection();
};
#endif 