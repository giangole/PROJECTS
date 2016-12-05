#ifndef QUATERNION
#define QUATERNION

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
class Quaternion
{
public:
	Quaternion(); //default constructor
	Quaternion(GLfloat w, GLfloat x, GLfloat y, GLfloat z);
	static Quaternion QuatRotate(Quaternion previous,GLfloat angle, GLfloat tx, GLfloat ty, GLfloat tz); //rotation around axis
	static void QuatToMatrix(Quaternion& result, GLfloat* matrix); //transform a qua into a matrix
	static Quaternion MakeQuaternion(GLfloat w, GLfloat x, GLfloat y, GLfloat z); //generates a quaternion
	static Quaternion QuatRotateVector(Quaternion& result, GLfloat x, GLfloat y, GLfloat z); // rotates a vector by a quaternion
	static Quaternion QuatMultiply(Quaternion a, Quaternion b); // multiplies 2 quats
	static Quaternion Conjugate(Quaternion q); // conjugate a quaternuion and returns it
	//getters and setters
	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	GLfloat GetW();
	void SetX(GLfloat X);
	void SetY(GLfloat Y);
	void SetZ(GLfloat Z);
	void SetW(GLfloat W);
public:
	// the 4 values of a quaternion
	GLfloat w;
	GLfloat x;
	GLfloat y;
	GLfloat z;
};
#endif