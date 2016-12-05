#include "Light.h"

Light::Light(){
	Position = vector3D(0, 0, 0);
	color = Color (1, 1, 1, 0);
}
Light::Light(vector3D v, Color c) : Position(v), color(c) {}
Light::~Light(){}
vector3D Light::GetLight(){ return Position; }
Color Light::GetColor(){ return color; }