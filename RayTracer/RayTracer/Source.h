#ifndef _SOURCE_H
#define _SOURCE_H
#include "vector3D.h"
#include "Color.h"
class Source
{
public:
	Source();
	virtual vector3D GetLight();
	virtual Color GetColor();

};
#endif 