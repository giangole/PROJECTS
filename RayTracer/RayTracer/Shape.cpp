#include"Shape.h"

Shape::Shape(){}
Color Shape::GetColor(){ return Color(0.0,0.0,0.0,0); }
double Shape::GetIntersection(Ray ray){ return 0; }
double Shape::findIntersection(Ray ray){ return 0; }
vector3D Shape::GetNormalAt(vector3D Intersection) {return vector3D(0, 0, 0); }