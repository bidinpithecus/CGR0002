#ifndef _utils_h_
#define _utils_h_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 0
#define Y 1
#define Z 2

typedef struct Cylinder {
	GLUquadric* quad;
	GLdouble base;
	GLdouble top;
	GLdouble height;
	GLint slices;
	GLint stacks;
} Cylinder;

typedef struct Disk {
	GLUquadric* quad;
	GLdouble inner;
	GLdouble outer;
	GLint slices;
	GLint loops;
} Disk;

typedef struct Position {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Position;

typedef struct Rgb {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
} Rgb;

typedef struct Rotation {
	GLfloat angle;
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Rotation;

typedef struct Sphere {
	GLUquadric* quad;
	GLdouble radius;
	GLint slices;
	GLint stacks;
} Sphere;

Rgb hexTo3f(int);

double generateAnotherCoordinateOnSurface(double r, double y0, double c1, double c2, int xyz);
GLfloat generateCoordinateInsideSphere(GLfloat r, double y0, GLfloat c1, GLfloat c2);
float calculateYAxisOfIntersection(float r0, float r1, float y0, float y1);
float calculateXAxisOfIntersection(float r, float y, float y0);

int randomNum(int min, int max);
float randomFloat(float min, float max);

void drawCylinder(int, Cylinder, Rotation, Position);
void drawDisk(int, Disk, Rotation, Position);
void drawSphere(int, Sphere, Position);

Cylinder newCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
Disk newDisk(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops);
Sphere newSphere(GLUquadric*, GLdouble, GLint, GLint);
Position newPosition(GLfloat x, GLfloat y, GLfloat z);
Rotation newRotation(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

#endif
