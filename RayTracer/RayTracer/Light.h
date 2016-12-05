#ifndef _LIGHT_H
#define _LIGHT_H
#include "math.h"
#include "Color.h"
#include "vector3D.h"
#include "Source.h"
#include "Ray.h"
class Light : public Source
{
	vector3D Position;
	Color color;
public:
	Light();
	Light(vector3D v, Color c);
	~Light();
	virtual vector3D GetLight();
	virtual Color GetColor();
};
#endif 