#ifdef _WIN32 
#define _CRT_SECURE_NO_DEPRECATE 
#endif 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "Source.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include "bitmap.h"
#include "vector3D.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
// This function pass through every intersection by index and find the closes intersections "winning" and return in , to know what goes on the camera

struct RGBType {
	double r;
	double g;
	double b;
};
Color GetColorAt1(vector3D intersectionPosition, vector3D intersectingRayDirection, std::vector <Shape*> ShapesScene, int IndexCloserShape, std::vector <Source*> LightSources, double accuracy, double ambientlight);
Color GetColorAt(vector3D intersectionPosition, vector3D intersectingRayDirection, std::vector <Shape*> ShapesScene, int IndexCloserShape, std::vector <Source*> LightSources, double accuracy, double ambientlight);
int GetIndexCloserShape(std::vector <double> ShapeIntersections);
void savebmp1(const char *filename, int w, int h, int dpi, RGBType *data);
int winningObjectIndex(std::vector<double> object_intersections);


int main(int argc, char * argv[])
{


	///////////////////      SCREEN      \\\\\\\\\\\\\\\\\\\\\\\\\\\
		////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/// WIDTH and HEIGHT of the image
	clock_t timestart, timeend;
	timestart = clock();
	int width = 1920;
	int height = 1080;
	double aspectratio = (double)width / (double)height;
	double ambientlight = 0.2;
	double accuracy = 0.000000001; // sometimes the intersections are on the edge of a sphere and might cause a bug, msubstractin this value nullify the intersection
	int dpi = 72;
	int n = width * height;
	char imagename[20] = { "image.bmp" };
	RGBType *pixels = new RGBType[n];
	char *ptr = &imagename[0];
	int pixelindex = 0;
	int pixelindex1 = 0;
	double aathreshold = 0.1;
	const int aadepth = 4;
	 // avarage between 4 close pixels
	//  BMP::RGB*firstimagepixels = new BMP::RGB;
	//	BMP firstimage(ptr, width, height,dpi,firstimagepixels);

	///////////////////     VECTORS      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		
	vector3D Origin(0, 0, 0);
	vector3D Xaxis(1, 0, 0);
	vector3D Yaxis(0, 1, 0);
	vector3D Zaxis(0, 0, 1);


	/////CAMERA\\\\\\\
	///////\\\\\\\\\\\
		//Where the camera is looking at
	vector3D CamLookingAt(0, 0, 0);
	vector3D CamPosition(3, 1.5, -3);
	vector3D CamPosminusDir(CamPosition.GetX() - CamLookingAt.GetX(), CamPosition.GetY() - CamLookingAt.GetY(), CamPosition.GetZ() - CamLookingAt.GetZ());
	// the opposite  of the normalized vector "CamPosminusDir" that basically is the differene between the camera position and whe is looking at
	vector3D CamDirection = (CamPosminusDir.Negate().Normalize());
	vector3D CamRight = Yaxis.CrossProduct(CamDirection).Normalize();
	vector3D CamDown = CamRight.CrossProduct(CamDirection);
	Camera CamScene(CamPosition, CamDirection, CamRight, CamDown);




	///////////////////    COLORS      \\\\\\\\\\\\\\\\\\\\\\\\\\\
		////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	// special Values changes the behaviour of
	Color ColWhiteLight(1.0, 1.0, 1.0, 0.0);
	Color ColGreen(0.5, 1.0, 0.5, 0.3);
	Color ColYellow(0, 0.044, 0.742, 0.3);
	Color ColYellowLight(0, 0.044, 0.742, 0);
	Color ColGray(0.5, 0.5, 0.5, 2);
	Color Colfloorblackwhite(1, 1, 1, 2);
	Color ColBlack(0.0, 0.0, 0.0, 0.0);
	Color ColMaroon(0.5, 0.25, 0.25, 0.3);
	Color ColBlue(0.667, 0.333, 0, 0.3);
	Color ColOrange(0, 0.4, 1, 0.3);
	///////////////////    Lights      \\\\\\\\\\\\\\\\\\\\\\\\\\\
		////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	vector3D LightPos(-7, 10, -10);
	Light LightScene(LightPos, ColWhiteLight);
	std::vector<Source*> LightSources;
	//  ADDS THE SCENE LIGHT TO THE VECTOR OD ALL THE LIGHTS IN THE SCENE is possible to add multiple lights
	LightSources.push_back(dynamic_cast<Source*>(&LightScene));
	///////////////////   SHAPES      \\\\\\\\\\\\\\\\\\\\\\\\\\\
			////////////////////           \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	vector3D SphereCentre(0.0, 0.0, 0.0);
	vector3D SphereCentre1(2.25, 0, 0);
	Sphere SphereScene(SphereCentre, 1, ColOrange);
	Sphere SphereScene1(SphereCentre1, 0.75, ColBlue);

	vector3D PlaneNormal(0, 1, 0);
	Plane PlaneScene(PlaneNormal, -1, Colfloorblackwhite);

	//Vector of shapes that holds all the shapes in the scene

	std::vector<Shape*> ShapesScene;
	ShapesScene.push_back(dynamic_cast<Shape*>(&SphereScene));
	ShapesScene.push_back(dynamic_cast<Shape*>(&PlaneScene));
	ShapesScene.push_back(dynamic_cast<Shape*>(&SphereScene1));

	// Values useful for antialising purposes, slight on right from the camera slight on left from the camera


	///////////////////    CREATE THE IMAGE     \\\\\\\\\\\\\\\\\\\\\\\\\\\
		////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	// The  image output is different depending on the Aspectratio.  offset objects  in order to create rays from left to right,
	// there is an image plane in front of the camera the rays have to go beyond the camera to cover that image.
	int aaindex;
	double XslightCamera, YslightCamera;
	double tempRed;
	double tempGreen;
	double tempBlue;

	for (int x = 0; x < width; x++)
{
		for (int y = 0; y < height; y++)
{
			pixelindex = y*width + x;
			pixelindex1 = y*width + x;

			
			double tempRed[aadepth*aadepth];
			double tempGreen[aadepth*aadepth];
			 double tempBlue[aadepth*aadepth];

			for (int aax = 0; aax < aadepth;aax++)
{
				for (int aay = 0; aay < aadepth;aay++)
				{
					aaindex = aay*aadepth + aax;
					srand(time(0));
					//no aa
					if (aadepth == 1)
					{
						//create the ray from the camera to this pixel
						// for aa purposes!
						// if the image is wider than tall
						if (width > height)
						{
							XslightCamera = ((x + 0.5) / width)*aspectratio - (((width - height) / (double)height) / 2);
							YslightCamera = ((height - y) + 0.5) / height;
						}
						else if (height > width)
						{
							// if the image is taller than wide
							XslightCamera = (x + 0.5) / width;
							YslightCamera = (((height - y) + 0.5) / height) / aspectratio - (((height - width) / (double)width) / 2);
						}
						else // the image has width = height
						{
							XslightCamera = (x + 0.5) / width;
							YslightCamera = ((height - y) + 0.5) / height;
						}
					}
					else 
					{
						if (width > height)
						{
							XslightCamera = (((x + (double)aax/(double)aadepth - 1)) / width)*aspectratio - (((width - height) / (double)height) / 2);
							YslightCamera = ((height - y) + (double)aax / (double)aadepth - 1) / height;
						}
						else if (height > width)
						{
							// if the image is taller than wide
							XslightCamera = ((x + (double)aax / (double)aadepth - 1)) / width;
							YslightCamera = (((height - y) + (double)aax / (double)aadepth - 1) / height) / aspectratio - (((height - width) / (double)width) / 2);
						}
						else // the image has width = height
						{
							XslightCamera = ((x + (double)aax / (double)aadepth - 1)) / width;
							YslightCamera = ((height - y) + ((double)aax / (double)aadepth - 1)) / height;
						}
					}
			// same position as the camera
			vector3D CamRayOrigin = CamScene.GetPosition();
			// the camera Ray Direction depends on the camera direction +( the right position of the camera ,ultiplied by the offset position on the right - 0.5 + the same thing with leftCAM and LEFTSlight ) 
			//everything normalized
			vector3D CamRayDirection = CamDirection.Add(CamRight.Multiply(XslightCamera - 0.5).Add(CamDown.Multiply(YslightCamera - 0.5))).Normalize();
			Ray CamRay(CamRayOrigin, CamRayDirection);

			std::vector<double> intersections;

			for (int index = 0; index < ShapesScene.size(); index++)
			{
				// Put the intersection into the INTERSECTIONS vector.
				//intersections between the ray and shapes
				intersections.push_back(ShapesScene.at(index)->findIntersection(CamRay)); //with planes and spheres.


				//Getintersection is a virtual Function for the base class Shapes and changes it's application depending on the shape (planes spheres cubes etc)

				// closest object

			}
			int IndexCloserShape = winningObjectIndex(intersections);
			//std::cout << IndexCloserShape;
			if (IndexCloserShape == -1) // if no intersections black color
			{
				//firstimagepixels->r[pixelindex] = 0;
				//firstimagepixels->g[pixelindex] = 0;
				//firstimagepixels->b[pixelindex] = 0;
				// no aa
				//pixels[pixelindex].r = 0;
				//pixels[pixelindex].g = 0;
				//pixels[pixelindex].b = 0;
				// with aa
				tempRed[aaindex]= 0;
				tempBlue[aaindex] = 0;
				tempGreen[aaindex]= 0;
			}
			else
			{
				if (intersections.at(IndexCloserShape) > accuracy)
				{

					// calculate the vectors (direction and position) at the point of intersections

					vector3D intersectionPosition = CamRayOrigin.Add(CamRayDirection.Multiply(intersections.at(IndexCloserShape)));
					vector3D intersectingRayDirection = CamRayDirection;

					Color IntersectionColor = GetColorAt(intersectionPosition, intersectingRayDirection, ShapesScene, IndexCloserShape, LightSources, accuracy, ambientlight); // light + color
					//Color IntersectionColor = ShapesScene.at(IndexCloserShape)->GetColor(); //USE THIS TO HAVE THE REAL COLOR WITHOUTH INTERACTIONS color
					// draws the right color for the right object 




					//	firstimagepixels->r[pixelindex] = IntersectionColor.GetRed();
					//	firstimagepixels->g[pixelindex] = IntersectionColor.GetGreen();
					//	firstimagepixels->b[pixelindex] = IntersectionColor.GetBlue();
					//no aa
					//pixels[pixelindex].r = IntersectionColor.GetRed();
					//pixels[pixelindex].g = IntersectionColor.GetGreen();
					//pixels[pixelindex].b = IntersectionColor.GetBlue();
					//with aa
					tempRed[aaindex]= IntersectionColor.GetRed();
					tempGreen[aaindex]= IntersectionColor.GetGreen();
					tempBlue[aaindex] = IntersectionColor.GetBlue();
				}
			}
			//first for loop aa
				}	
				//second for loop aa
	}
			//third for loop 
	double Totalred = 0;
	double Totalgreen = 0;
	double Totalblue = 0;
	for (int iRed = 0; iRed < aadepth*aadepth; iRed++)
	{
		Totalred = Totalred + tempRed[iRed];

	}
	for (int iGreen = 0; iGreen < aadepth*aadepth; iGreen++)
	{
		Totalgreen= Totalgreen+ tempGreen[iGreen];

	}
	for (int iBlue = 0; iBlue < aadepth*aadepth; iBlue++)
	{

		Totalblue = Totalblue + tempBlue[iBlue];
	}

	double Avgred = Totalred / (aadepth*aadepth);
	double Avgreen = Totalgreen / (aadepth*aadepth);
	double Avgblue= Totalblue / (aadepth*aadepth);

	pixels[pixelindex].r = Avgred;
	pixels[pixelindex].g = Avgreen;
	pixels[pixelindex].b = Avgblue;

		}
		//fourth for loop

}
	savebmp1(imagename, width, height, dpi, pixels);
	//firstimage.saveBMP();
	delete pixels;
	timeend = clock();
		float deltatime = ((float)timeend - (float)timestart) / 1000;
		std::cout << deltatime << "seconds /n";
		std::cin.get();
		std::cin.get();
	return 0;
}
// GetColoract: Gets the color of the Closest shape,gets the normal at the location of the intersection, loops through the lightsources determines the direction of the light and create Rays in the toward direction of each lights, and we get the shadow at the first intersection
Color GetColorAt(vector3D intersectionPosition, vector3D intersectingRayDirection, std::vector <Shape*> ShapesScene, int IndexCloserShape, std::vector <Source*> LightSources, double accuracy, double ambientlight)
{
	
	Color IndexCloserShapeColor = ShapesScene.at(IndexCloserShape)->GetColor(); // polymorphism
	vector3D IndexCloserShapeNormal = ShapesScene.at(IndexCloserShape)->GetNormalAt(intersectionPosition); //polymorphism
	Color FinalColor = IndexCloserShapeColor.ColorScalar(ambientlight); // the color modified by the ambientlight

	if (IndexCloserShapeColor.GetSpecial() == 2) 
	{
		// does a check for the floor pattern
		int square = (int)floor(intersectionPosition.GetX()) + (int)floor(intersectionPosition.GetZ());
		if (square % 2 == 0)
		{
			IndexCloserShapeColor.SetRed(0); //black square
			IndexCloserShapeColor.SetBlue(0);
			IndexCloserShapeColor.SetGreen(0);
		}
		else
		{

			IndexCloserShapeColor.SetRed(1); //black square
			IndexCloserShapeColor.SetBlue(1);
			IndexCloserShapeColor.SetGreen(1);
		}


	}
	/// adds reflections to the game WITH SPECULAR INTENSITY
	if (IndexCloserShapeColor.GetSpecial() > 0 && IndexCloserShapeColor.GetSpecial() <= 1)
	{
		double dota1 = IndexCloserShapeNormal.DotProduct(intersectingRayDirection.Negate());
		vector3D scalar1 = IndexCloserShapeNormal.Multiply(dota1);
		vector3D addition1 = scalar1.Add(intersectingRayDirection);
		vector3D  scalar2 = addition1.Multiply(2);
		vector3D addition2 = intersectingRayDirection.Negate().Add(scalar2);
		vector3D reflectiondirection = addition2.Normalize();

		Ray reflectionray(intersectionPosition, reflectiondirection);
		// determine what the ray intersects
		std::vector<double> reflectionintersections;
		for (int reflectionindex = 0; reflectionindex < ShapesScene.size(); reflectionindex++)
		{


			reflectionintersections.push_back(ShapesScene.at(reflectionindex)->findIntersection(reflectionray));

		}


		int indexCloserShapewithReflection = winningObjectIndex(reflectionintersections);
		// -1 missed no reflections, no need for this part of code to run
		if (indexCloserShapewithReflection != -1)
		{
			if (reflectionintersections.at(indexCloserShapewithReflection) > accuracy)
			{
				//prevent endless calculations and bugs, the value must be over accuracy or it doesnt reflect
				vector3D ReflectionIntersectionPosition = intersectionPosition.Add(reflectiondirection.Multiply(reflectionintersections.at(indexCloserShapewithReflection)));
				vector3D ReflectionIntersectionRayDirection = reflectiondirection;
				// Recursive itslef to get the color of the reflections
				Color ReflectionIntersectionColor = GetColorAt(ReflectionIntersectionPosition, ReflectionIntersectionRayDirection, ShapesScene, indexCloserShapewithReflection, LightSources,accuracy, ambientlight);
				//Final color now includes the reflection calculation if it is there
				FinalColor = FinalColor.ColorAdd(ReflectionIntersectionColor.ColorScalar(IndexCloserShapeColor.GetSpecial()));
			}
		}
	}
	for (int lightindex = 0; lightindex< LightSources.size(); lightindex++)
	{

	vector3D lightdirection = LightSources.at(lightindex)->GetLight().Add(intersectionPosition.Negate()).Normalize();

		float  CosAngle = IndexCloserShapeNormal.DotProduct(lightdirection);
		if (CosAngle > 0)
		{
			//test for shadows
			bool Shadow = false;
			vector3D DistanceToLight = LightSources.at(lightindex)->GetLight().Add(intersectionPosition.Negate()).Normalize(); // point of intersection from light to object
			float DistanceToLightLenght = DistanceToLight.Lenght(); // distance from light to intersections
			// this ray to see if there are shadows goes in the drection of the light
			Ray ShadowRay(intersectionPosition, LightSources.at(lightindex)->GetLight().Add(intersectionPosition.Negate()).Normalize()); 
			std::vector<double> secondaryintersections;
			for (int shapeindex = 0; shapeindex < ShapesScene.size() &&Shadow == false; shapeindex++)
			{
				secondaryintersections.push_back(ShapesScene.at(shapeindex)->findIntersection(ShadowRay));
			}
			for (int c = 0; c < secondaryintersections.size(); c++)
			{
				if (secondaryintersections.at(c) > accuracy)
					{

					if (secondaryintersections.at(c) <= DistanceToLightLenght)
					{
						Shadow = true;	
					}
					//second if
					break;
					}
			//inside for loop
			}
			if (Shadow == false)
			{
				// the final color is: the color of the object multiplied by the light sources 
				FinalColor = FinalColor.ColorAdd(IndexCloserShapeColor.ColorMultiply(LightSources.at(lightindex)->GetColor()).ColorScalar(CosAngle));
					if (IndexCloserShapeColor.GetSpecial() > 0 && IndexCloserShapeColor.GetSpecial() <=1)
					{
					//shyniness between 0 ad 1
						double Dot1 = IndexCloserShapeNormal.DotProduct(intersectingRayDirection.Negate());
						vector3D Scalar1 = IndexCloserShapeNormal.Multiply(Dot1);
						vector3D Add1 = Scalar1.Add(intersectingRayDirection);
						vector3D Scalar2 = Add1.Multiply(2);
						vector3D Add2 = intersectingRayDirection.Negate().Add(Scalar2);
						vector3D ReflectionDirection = Add2.Normalize();

						double specular = ReflectionDirection.DotProduct(lightdirection);
						if (specular > 0)
						{
							specular = pow(specular, 10);
							FinalColor = FinalColor.ColorAdd(LightSources.at(lightindex)->GetColor().ColorScalar(specular*IndexCloserShapeColor.GetSpecial()));
						}
					}
			}
		}
	}

	return FinalColor.clip();
}
int GetIndexCloserShape(std::vector <double> ShapeIntersections)
{	//return the index of the closer shape
	int IndexMinimum;
	if (ShapeIntersections.size() == 0)
	{
		return -1;
		// to prevent not necessaty calculations, when there arent intersections
	}
	else if (ShapeIntersections.size() == 1)
	{
		if (ShapeIntersections.at(0)> 0) //the value at index 0 bigger than 0 
		{
		// if the intersection is greater than 1 means is the closer and is the right one
			return 0; //this is the INDEX NOT THE VALUES,the closer shape get the position 0 in the array vector
		}
		else 
		{
			return -1; //no intersections;
		}
	}
	else // if there are more than 1 intersections
	{
		double max = 0;
		for (int i = 0; i < ShapeIntersections.size(); i++)
		{
		
			if (max < ShapeIntersections.at(i))
			{
				max = ShapeIntersections.at(i);
			}
		
		}
		// from the maximum value to the minimum
		if (max > 0)
		{
			for (int index = 0; index < ShapeIntersections.size(); index++)
			{
				if (ShapeIntersections.at(index)> 0 && ShapeIntersections.at(index) <= max)
				{
					max = ShapeIntersections.at(index);
					IndexMinimum = index;
				}
			
			}
			return IndexMinimum;
		}
		else{
			return -1;
			// all the intersections are negative
			}
	}
}
void savebmp1(const char *filename, int w, int h, int dpi, RGBType *data) {
	FILE *f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };

		fwrite(color, 1, 3, f);
	}

	fclose(f);
}
int winningObjectIndex(std::vector<double> object_intersections) {
	// return the index of the winning intersection
	int index_of_minimum_value;

	// prevent unnessary calculations
	if (object_intersections.size() == 0) {
		// if there are no intersections
		return -1;
	}
	else if (object_intersections.size() == 1) {
		if (object_intersections.at(0) > 0) {
			// if that intersection is greater than zero then its our index of minimum value
			return 0;
		}
		else {
			// otherwise the only intersection value is negative
			return -1;
		}
	}
	else {
		// otherwise there is more than one intersection
		// first find the maximum value

		double max = 0;
		for (int i = 0; i < object_intersections.size(); i++) {
			if (max < object_intersections.at(i)) {
				max = object_intersections.at(i);
			}
		}

		// then starting from the maximum value find the minimum positive value
		if (max > 0) {
			// we only want positive intersections
			for (int index = 0; index < object_intersections.size(); index++) {
				if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
					max = object_intersections.at(index);
					index_of_minimum_value = index;
				}
			}

			return index_of_minimum_value;
		}
		else {
			// all the intersections were negative
			return -1;
		}
	}
}

