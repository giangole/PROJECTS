#include "Quaternion.h"


Quaternion::Quaternion(){}
Quaternion::Quaternion(GLfloat sw, GLfloat vx, GLfloat vy, GLfloat vz) : w(sw), x(vx), y(vy), z(vz)  {}


Quaternion Quaternion::QuatRotate(Quaternion previous, GLfloat angle, GLfloat tx, GLfloat ty, GLfloat tz)
{	
		previous.w = cos(angle* 0.5);
		previous.x = tx* sin(angle *0.5);
		previous.y = ty* sin(angle *0.5);
		previous.z = tz* sin(angle *0.5);
		return previous;
}

GLfloat Quaternion::GetX(){ return x; }
GLfloat Quaternion::GetY(){ return y; }
GLfloat Quaternion::GetZ(){ return z; }
GLfloat Quaternion::GetW(){ return w; }

void Quaternion::SetX(GLfloat X){ x = X; }
void Quaternion::SetY(GLfloat Y){ y = Y; }
void Quaternion::SetZ(GLfloat Z){ z = Z; }
void Quaternion::SetW(GLfloat W){ w = W; }



Quaternion Quaternion::MakeQuaternion(GLfloat w, GLfloat x, GLfloat y, GLfloat z)
{

	Quaternion quat(w, x, y, z);
	return quat;
}
Quaternion Quaternion::QuatMultiply(Quaternion a, Quaternion b)
{

	Quaternion quat(a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
		a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
		a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
		a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w);
	return quat;
}
Quaternion Quaternion::Conjugate(Quaternion q)
{
	q.w = q.w;
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	return q;
}
Quaternion Quaternion::QuatRotateVector(Quaternion& result, GLfloat x, GLfloat y, GLfloat z)
{
	Quaternion quat;
	quat = MakeQuaternion(0, x, y, z);
	quat = QuatMultiply(result, quat);
	quat = QuatMultiply(quat, Conjugate(result));
	return quat;
}
void Quaternion::QuatToMatrix(Quaternion& a, GLfloat* matrix)

{
	// First row
	matrix[0] = 1.0f - 2.0f * (a.y * a.y + a.z * a.z); // dotproduct 
	matrix[1] = 2.0f * (a.x * a.y - a.w * a.z); // dot product
	matrix[2] = 2.0f * (a.x * a.z + a.w * a.y); // dot product 
	matrix[3] = 0.0f;
	// Second row
	matrix[4] = 2.0f * (a.x * a.y + a.w * a.z); // dot product 
	matrix[5] = 1.0f - 2.0f * (a.x * a.x + a.z * a.z); // dot product 
	matrix[6] = 2.0f * (a.y * a.z - a.w * a.x); // dot product 
	matrix[7] = 0.0f;

	// Third row
	matrix[8] = 2.0f * (a.x * a.z - a.w * a.y); // dot product 
	matrix[9] = 2.0f * (a.y * a.z + a.w * a.x); // dot product 
	matrix[10] = 1.0f - 2.0f * (a.x * a.x + a.y * a.y); // dot product 
	matrix[11] = 0.0f; // dot product 

	// Fourth row
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1.0f;


}