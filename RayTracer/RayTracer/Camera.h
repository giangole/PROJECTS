#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector3D.h"
class Camera
{
	vector3D Position;
	vector3D Direction;
	vector3D Right;
	vector3D Down;

public:
	Camera();
	Camera(vector3D a, vector3D b, vector3D c, vector3D d);
	~Camera();
	vector3D GetPosition();
	vector3D GetDirection();
	vector3D GetRight();
	vector3D GetDown();
};
#endif 