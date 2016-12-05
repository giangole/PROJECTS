#include "Sphere.h"

Sphere::Sphere()
{
	Centre = vector3D (0, 0, 0);
	color = Color (0.5, 0.5, 0.5, 0);
	Radius = 1;
}
Sphere::Sphere(vector3D v, double d, Color c) : Centre(v), Radius(d), color(c){}
Sphere::~Sphere(){}
vector3D Sphere::GetCentre() { return Centre; }
double Sphere::GetRadius(){ return Radius; }
Color Sphere::GetColor(){ return color; }

double Sphere::GetIntersections(Ray ray)
{
	vector3D RayOrigin = ray.GetOrigin();
	double RayOriginX = RayOrigin.GetX();
	double RayOriginY = RayOrigin.GetY();
	double RayOriginZ = RayOrigin.GetZ();

	vector3D RayDirection = ray.GetDirection();
	double RayDirectionX = RayDirection.GetX();
	double RayDirectionY = RayDirection.GetY();
	double RayDirectionZ = RayDirection.GetZ();

	vector3D SphereCentre = Centre;
	double SphereCentreX = SphereCentre.GetX();
	double SphereCentreY = SphereCentre.GetY();
	double SphereCentreZ = SphereCentre.GetZ();
	double a = 1.0; //normalized

	double b = (2*(RayOriginX - SphereCentreX)*RayDirectionX) + (2 * (RayOriginY - SphereCentreY)*RayDirectionY)+(2 * (RayOriginZ - SphereCentreZ)*RayDirectionZ);
	double c = pow(RayOriginX - SphereCentreX, 2) + pow(RayOriginY - SphereCentreY, 2) + pow(RayOriginZ - SphereCentreZ, 2) -(Radius*Radius);


	double Discriminant = b*b - 4*c;

	if (Discriminant > 0) //there is an intersection cause delta positive
	{
		//however 2 roots cause second degree function
		double Root1 = (((-1*b - sqrt(Discriminant)) / 2) - 0.000001); // The 0.00001 helps in compuitation
		if (Root1 > 0)
		{
			return Root1; //tHIS IS THE SMALLEST positive root, MEANS THISI IS AN INTERSACTION WITH THE SPHERE!!!
		}
		else 
		{
			double Root2 = ((sqrt(Discriminant) - b) / 2) - 0.000001;
			return Root2;
		}//ROOT2 is the positive smallest ROOT = INTERSATION
	}
	else { return -1;
	} //no intersection The ray missed the Sphere
}
vector3D Sphere::GetNormalAt(vector3D point)
{
	vector3D normal = point.Add(Centre.Negate()).Normalize(); 
	return normal;
}




double Sphere::findIntersection (Ray ray) {
	vector3D ray_origin = ray.GetOrigin();
	double ray_origin_x = ray_origin.GetX();
	double ray_origin_y = ray_origin.GetY();
	double ray_origin_z = ray_origin.GetZ();

	vector3D ray_direction = ray.GetDirection();
	double ray_direction_x = ray_direction.GetX();
	double ray_direction_y = ray_direction.GetY();
	double ray_direction_z = ray_direction.GetZ();

	vector3D sphere_center = Centre;
	double sphere_center_x = sphere_center.GetX();
	double sphere_center_y = sphere_center.GetY();
	double sphere_center_z = sphere_center.GetY();

	double a = 1; // normalized
	double b = (2 * (ray_origin_x - sphere_center_x)*ray_direction_x) + (2 * (ray_origin_y - sphere_center_y)*ray_direction_y) + (2 * (ray_origin_z - sphere_center_z)*ray_direction_z);
	double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (Radius*Radius);

	double discriminant = b*b - 4 * c;

	if (discriminant > 0) {
		/// the ray intersects the sphere

		// the first root
		double root_1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;

		if (root_1 > 0) {
			// the first root is the smallest positive root
			return root_1;
		}
		else {
			// the second root is the smallest positive root
			double root_2 = ((sqrt(discriminant) - b) / 2) - 0.000001;
			return root_2;
		}
	}
	else {return -1;}
		// the ray missed the sphere		
}

