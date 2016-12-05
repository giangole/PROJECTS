#include "Camera.h"

Camera::Camera()
{
	Position = vector3D(0, 0, 0);
	Direction = vector3D(0, 0, 1);
	Right = vector3D(0, 0, 0);
	Right = vector3D(0, 0, 0);
}
Camera::Camera(vector3D a, vector3D b, vector3D c, vector3D d) : Position(a), Direction(b), Right(c), Down(d){}
Camera::~Camera(){}
vector3D Camera::GetDirection(){ return Direction; }
vector3D Camera::GetRight(){ return Right; }
vector3D Camera::GetDown(){ return Down; }
vector3D Camera::GetPosition(){ return Position; }