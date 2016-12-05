#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include "MathHelper.h"		
#include "Quaternion.h"
#include "phlegm_small.h"	// model converted from .obj to .h there other models stored as .h feel free to change it if you want! 
#include "iostream"
	
#define USING_INDEX_BUFFER 1

#ifdef USING_INDEX_BUFFER
	#define NUM_VERTICES num_vertices	
	#define NUM_INDICES num_indices	
#else
	#define NUM_VERTICES num_vertices
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// general opengl initialisation varaibles
GLfloat light[] = {0.0f, 1.0f, 1.0f, 1.0f};

GLuint shaderProgramID;
GLuint vao = 0;
GLuint vbo;
GLuint positionID, normalID; 
GLuint indexBufferID; 

GLuint	perspectiveMatrixID, viewMatrixID, modelMatrixID;	// IDs of variables mP, mV and mM in the shader
GLuint	allRotsMatrixID; 
GLuint	lightID;		

GLfloat* rotXMatrix;	// Matrix for rotations about the X axis
GLfloat* rotYMatrix;	// Matrix for rotations about the Y axis
GLfloat* rotZMatrix;	// Matrix for rotations about the Z axis
GLfloat* rotXYZMatrix;  // Temporary 1 Matrix for rotations about the XYZ axis
GLfloat* rotXYZ1Matrix; // Temporary 2 for rotations about the XYZ axis
GLfloat* allRotsMatrix;	// Matrix for all the rotations (X, Y Z) combined

GLfloat* transMatrix;	// Matrix for changing the position of the object
GLfloat* scaleMatrix;	// Matrix for changing the position of the object
GLfloat* tempMatrix1;	// A temporary matrix for holding intermediate multiplications

GLfloat* M;				// The final model matrix M to change into world coordinates

GLfloat* V;				// The camera matrix (for position/rotation) to change into camera coordinates
GLfloat* P;				// The perspective matrix for the camera (to give the scene depth); initialize this ONLY ONCE!


GLfloat alpha;			// Angle Matrix rotation on  X (in radiants)
GLfloat theta;			// Matrix rotation on  Y (in radiants)
GLfloat gamma;          // Angle Matrix rotation on  Z (in radiants)


GLfloat  beta;			// angle Quaternion rotation X
GLfloat  omega;			//  angle Quaternion rotation Y
GLfloat  delta;			//  angle Quaternion rotation Z

GLfloat	 scaleAmount;	// In case the object is too big or small

GLfloat camX, camY, camZ;	//  simple camera position coordinates
GLfloat yaw, pitch, roll;	// simple camera rotation coordinates

Quaternion QuatRotation, QuatresultX, QuatresultY, QuatresultXYZ, QuatresultZ, QuatresultXY; // quaternions on X Y Z XY XYZ axis
 // switches to go between manual auto and matrix quat
bool toggleQuatMatrix = true;
bool switchrotation = true;
bool automanualtoggle = false;

//Initialisation of the matrices and relative variables
void initMatrices() {


	alpha = 0.0f;
	theta = 0.0f;
	gamma = 0.0f;

	beta = 0.0f;
	omega = 0.0f;
	scaleAmount = 1.0f;

	QuatRotation = Quaternion::MakeQuaternion(0, 0, 0, 0);
	QuatresultX = Quaternion::MakeQuaternion(0, 0, 0, 0);
	QuatresultXYZ = Quaternion::MakeQuaternion(0, 0, 0, 0);
	QuatresultY = Quaternion::MakeQuaternion(0, 0, 0, 0);
	QuatresultZ = Quaternion::MakeQuaternion(0, 0, 0, 0);
	QuatresultXY = Quaternion::MakeQuaternion(0, 0, 0, 0);

	// Allocate memory for the matrices and initialize them to the Identity matrix
	rotXMatrix = new GLfloat[16];	MathHelper::makeIdentity(rotXMatrix);
	rotYMatrix = new GLfloat[16];	MathHelper::makeIdentity(rotYMatrix);
	rotZMatrix = new GLfloat[16];	MathHelper::makeIdentity(rotZMatrix);
	
	rotXYZMatrix = new GLfloat[16]; MathHelper::makeIdentity(rotXYZMatrix);
	rotXYZ1Matrix = new GLfloat[16]; MathHelper::makeIdentity(rotXYZ1Matrix);
	allRotsMatrix = new GLfloat[16]; MathHelper::makeIdentity(allRotsMatrix);
	
	
	transMatrix = new GLfloat[16];	MathHelper::makeIdentity(transMatrix);
	scaleMatrix = new GLfloat[16];	MathHelper::makeIdentity(scaleMatrix);
	tempMatrix1 = new GLfloat[16];	MathHelper::makeIdentity(tempMatrix1);
	
	
	// these are the Model View and Perspective matrix
	M = new GLfloat[16];			MathHelper::makeIdentity(M);
	V = new GLfloat[16];			MathHelper::makeIdentity(V);
	P = new GLfloat[16];			MathHelper::makeIdentity(P);

	// Set up the (P)erspective matrix only once! Arguments are 1) the resulting matrix, 2) FoV, 3) aspect ratio, 4) near plane 5) far plane
	MathHelper::makePerspectiveMatrix(P, 80.0f, 1.0f, 1.0f, 1000.0f);
}
//here we have various methods to generate/compile and initialise the fragment and vertex shaders
#pragma region SHADER_FUNCTIONS
static char* readFile(const char* filename) {
	// Open the file
	FILE* fp = fopen (filename, "r");
	// Move the file pointer to the end of the file and determing the length
	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[file_length+1];
	// zero out memory
	for (int i = 0; i < file_length+1; i++) {
		contents[i] = 0;
	}
	// Here's the actual read
	fread (contents, 1, file_length, fp);
	// This is how you denote the end of a string in C
	contents[file_length+1] = '\0';
	fclose(fp);
	return contents;
}

bool compiledStatus(GLint shaderID){
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		return true;
	}
	else {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
		printf ("%s\n", msgBuffer);
		delete (msgBuffer);
		return false;
	}
}

GLuint makeVertexShader(const char* shaderSource) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource (vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vertexShaderID);
	bool compiledCorrectly = compiledStatus(vertexShaderID);
	if (compiledCorrectly) {
		return vertexShaderID;
	}
	return -1;
}

GLuint makeFragmentShader(const char* shaderSource) {
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(fragmentShaderID);
	bool compiledCorrectly = compiledStatus(fragmentShaderID);
	if (compiledCorrectly) {
		return fragmentShaderID;
	}
	return -1;
}

GLuint makeShaderProgram (GLuint vertexShaderID, GLuint fragmentShaderID) {
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);
	return shaderID;
}
#pragma endregion SHADER_FUNCTIONS

// convert a float into a char to be printed with Glprintbitmap
char* concat(const char *s1, const char *s2)
{
	char* result = (char*) malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
	//in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}


// automatically resize the scene if the window is modified
void changeViewport(int w, int h){
	glViewport(0, 0, w, h);
}

// inputs function
void keyboardFunc (unsigned char key, int x, int y) {
	switch (key) {
		case 033:
		case 'esc':
			exit(1);
			break;
		case 'w': camZ += 0.15f; break;
		case 's': camZ -= 0.15f; break;
		case 'a': camX += 0.15f; break;
		case 'd': camX -= 0.15f; break;
		case 'q': camY += 0.15f; break;
		case 'e': camY -= 0.15f; break;
		case 'r': yaw += 0.05f; break;
		case 't': yaw -= 0.05f; break;
		case 'f': pitch += 0.05f; break;
		case 'g': pitch -= 0.05f; break;
		case 'v': roll += 0.05f; break;
		case 'b': roll -= 0.05f; break;



		case 'y': 
			if (automanualtoggle == false)
			{
				if (toggleQuatMatrix == true)
				{
					alpha += 0.03f;
				}

				if (toggleQuatMatrix == false)
				{
					beta += 0.03f;
				}
			}
			break;
		case 'u': 	
			if (automanualtoggle == false)
			{
				if (toggleQuatMatrix == true)
				{
					alpha -= 0.03f;
				}

				if (toggleQuatMatrix == false)
				{
					beta -= 0.03f;
				}
			}
			break;
		case 'h': 	
			if (automanualtoggle == false)
		{
			if (toggleQuatMatrix == true)
			{
				theta += 0.03f;
			}

			if (toggleQuatMatrix == false)
			{
				omega += 0.03f;
			}
		} break;


		case 'j': if (automanualtoggle == false)
		{
			if (toggleQuatMatrix == true)
			{
				theta -= 0.03f;
			}

			if (toggleQuatMatrix == false)
			{
				omega -= 0.03f;
			}
		}
				  break;
		case 'n': if (automanualtoggle == false)
		{
			if (toggleQuatMatrix == true)
			{
				gamma += 0.03f;
			}

			if (toggleQuatMatrix == false)
			{
				delta += 0.03f;
			}
		} break;
		case 'm': if (automanualtoggle == false)
		{
			if (toggleQuatMatrix == true)
			{
				gamma -= 0.03f;
			}

			if (toggleQuatMatrix == false)
			{
				delta -= 0.03f;
			}
		} break;
			// switch between matrices and quats
		case 'p' : 
			if (toggleQuatMatrix == false)
			{

				toggleQuatMatrix = true;
			}
			else if (toggleQuatMatrix == true)
			{
			
				toggleQuatMatrix = false;
			}

			break;

// switch between auto and manual
		case 'o':
			if (automanualtoggle == false)
			{

				automanualtoggle = true;
			}
			else if (automanualtoggle == true)
			{

				automanualtoggle = false;
			}

			break;



	}
}

// rendering function, everything that needs to be updated regurlarly and redrawn go in here.
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);
	// if automatic the values get updated
	if (automanualtoggle == true )
	{

		if (toggleQuatMatrix == true)
		{

			theta += 0.02f;
			gamma += 0.015f;
			alpha += 0.01f;

		}
		if (toggleQuatMatrix == false)
		{

			beta += 0.011f; //X
			delta += 0.013f; // Z
			omega += 0.017f; // Y

		}

	}


	scaleAmount = 1.0f; //scale amount for the model, 1.0 means no particular change
	
	// Set the (M)odel matrix

	// using Matrices for the Rotation, 
	if (toggleQuatMatrix == true)
	{
		// calcualtion for the matrices in order Scale Rotation Translation
		//scale
	MathHelper::makeScale(scaleMatrix, scaleAmount, scaleAmount, scaleAmount);	
	// single rotations
	MathHelper::makeRotateX(rotXMatrix, alpha);
	MathHelper::makeRotateY(rotYMatrix, theta);
	MathHelper::makeRotateZ(rotZMatrix, gamma);
	// obtaining the final rotation around all 3 axis using the multiplicatino between 4X4 matrices function
	MathHelper::matrixMult4x4(rotXYZMatrix, rotXMatrix, rotYMatrix);
	MathHelper::matrixMult4x4(rotXYZ1Matrix, rotXYZMatrix, rotZMatrix);
	MathHelper::matrixMult4x4(tempMatrix1, rotXYZ1Matrix, scaleMatrix);
	// a copy of the rotation matrix, useful to give data to the shaders
	MathHelper::copyMatrix(rotXYZ1Matrix, allRotsMatrix);

	}

	// At last translation 
	MathHelper::makeTranslate(transMatrix, 0.0f, -6.0f, -12.0f);	// slightly back.

	//Using Quaternions for the rotation
	if (toggleQuatMatrix == false)
	{
		// rotation on the single axis
		QuatresultX = Quaternion::QuatRotate(QuatRotation, omega, 0, 1, 0);
		QuatresultY = Quaternion::QuatRotate(QuatRotation, delta, 1, 0, 0);
		QuatresultZ = Quaternion::QuatRotate(QuatRotation, beta, 0, 0, 1);


		// multiplication of the 3 rotation in one quaternion
		QuatresultXY = Quaternion::QuatMultiply(QuatresultX, QuatresultY);
		QuatresultXYZ = Quaternion::QuatMultiply(QuatresultXY, QuatresultZ);

		//quaternion gets transformed into a Matrix ready to be given to the shaders
		Quaternion::QuatToMatrix(QuatresultXYZ, rotXYZMatrix);
		
		// lets scale everything and copy the matrix just in case
		MathHelper::matrixMult4x4(tempMatrix1, rotXYZMatrix, scaleMatrix);
		MathHelper::copyMatrix(rotXYZMatrix, allRotsMatrix);
	}

	// calculation of the MODEL matrix (M)
	MathHelper::matrixMult4x4(M, transMatrix, tempMatrix1);				// ... then multiply THAT by the translate


	// VIEW matrix gets updated in case the camera is moved around
	MathHelper::makeRotateY(rotYMatrix, yaw);
	MathHelper::makeTranslate(transMatrix, camX, camY, camZ);
	MathHelper::matrixMult4x4(V, rotYMatrix, transMatrix);
	
	// pass that data to the shader variables
	glUniformMatrix4fv(modelMatrixID, 1, GL_TRUE, M);
	glUniformMatrix4fv(viewMatrixID, 1, GL_TRUE, V);
	glUniformMatrix4fv(perspectiveMatrixID, 1, GL_TRUE, P);
	glUniformMatrix4fv(allRotsMatrixID, 1, GL_TRUE, allRotsMatrix);
	glUniform4fv(lightID, 1, light);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // cool effect
#ifdef USING_INDEX_BUFFER
	glDrawElements (GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, NULL);
#else
	glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
#endif
	
	// necessary to write on screen the results of the rotation, LIGHTING needs to be disabled or the color is the same as the background...
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glColor3f(0.5f, 1.0f, 1.0f);

	float sinbeta = sin(beta);
	float sindelta = sin(delta);
	float sinomega = sin(omega);
	float sinalpha = sin(alpha);
	float sintheta = sin(theta);
	float singamma = sin(gamma);


	char output[50];


		glWindowPos2f(20, 580);
		_snprintf(output, 50, "%f", sinbeta);
		char Cfinal[50] = "Quat x rotation (sin): ";
		char* display = concat(Cfinal, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display);

		glWindowPos2f(20, 560);
		_snprintf(output, 50, "%f", sinomega);
		char Cfinal1[50] = "Quat y rotation (sin): ";
		char* display1 = concat(Cfinal1, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display1);

		glWindowPos2f(20, 540);
		_snprintf(output, 50, "%f", sindelta);
		char Cfinal2[50] = "Quat z rotation (sin): ";
		char* display2 = concat(Cfinal2, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display2);



		glWindowPos2f(300, 580);
		_snprintf(output, 50, "%f", sinalpha);
		char Cfinal3[50] = "Matrix x rotation (sin): ";
		char* display3 = concat(Cfinal3, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display3);

		glWindowPos2f(300, 560);
		_snprintf(output, 50, "%f", sintheta);
		char Cfinal4[50] = "Matrix y rotation (sin): ";
		char* display4 = concat(Cfinal4, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display4);

		glWindowPos2f(300, 540);
		_snprintf(output, 50, "%f", singamma);
		char Cfinal5[50] = "Matrix z rotation (sin): ";
		char* display5 = concat(Cfinal5, output);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)display5);

	glEnable(GL_LIGHTING);		
	glutSwapBuffers();
	glutPostRedisplay();		
}

int main (int argc, char** argv) {
	// GLUT initialisation and matrices
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GCP Assignment");
	glutReshapeFunc(changeViewport);
	glutKeyboardFunc(keyboardFunc);
	glutDisplayFunc(render);
	glewInit();

	initMatrices(); 

	// Make shaders
	char* vertexShaderSourceCode = readFile("vertexShader.vsh");
	char* fragmentShaderSourceCode = readFile("fragmentShader.fsh");
	GLuint vertShaderID = makeVertexShader(vertexShaderSourceCode);
	GLuint fragShaderID = makeFragmentShader(fragmentShaderSourceCode);
	shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID);

	// create and bind the VBO toi the VAO"
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Create the buffer of the size necessary to store the model  3 flaots for RGB 3 for the vertices XYZ
	glBufferData(GL_ARRAY_BUFFER, 6*NUM_VERTICES*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	
	// Load the vertex points
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3*NUM_VERTICES*sizeof(GLfloat), vertices);
	// Load the colors right after that
	glBufferSubData(GL_ARRAY_BUFFER, 3*NUM_VERTICES*sizeof(GLfloat),3*NUM_VERTICES*sizeof(GLfloat), normals);
	
	
#ifdef USING_INDEX_BUFFER
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES*sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif
	

	// the console output
	std::cout << "Giannandrea Grone Assignment \n";
	std::cout << "Simple demonstration of rotating a model around itself with Quaternions or Matrices\n ";
	std::cout << "The results seem similar but the maths behind it is significantly different\n ";
	std::cout << "How to use: \n ";
	std::cout << "Press P to toggle between Matrices and Quaternions \n ";
	std::cout << "Press O to toggle between Automatic and Manual \n ";
	std::cout << "WASD to move the camera (left, right, forward, backward \n ";
	std::cout << "QE  to move the camera upward downward \n ";
	std::cout << "RT FG CV to rotate the camera on XYZ \n ";
	std::cout << "(Manual only) YU HJ NM to rotate the model on XYZ \n";




	// bind the data with the shaders
	positionID = glGetAttribLocation(shaderProgramID, "s_vPosition");
	normalID = glGetAttribLocation(shaderProgramID, "s_vNormal");
	lightID = glGetUniformLocation(shaderProgramID, "vLight");	// NEW
	
	// gives the data to the shaders
	perspectiveMatrixID = glGetUniformLocation(shaderProgramID, "mP");
	viewMatrixID = glGetUniformLocation(shaderProgramID, "mV");
	modelMatrixID = glGetUniformLocation(shaderProgramID, "mM");
	allRotsMatrixID = glGetUniformLocation(shaderProgramID, "mRotations");
	

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	
	glUseProgram(shaderProgramID);
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(normalID);
	
	// Turn on depth cullint
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	
	return 0;
}
